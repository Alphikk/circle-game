#include "server.hpp"


void
ns_Server::onMessage(Server* server,
                      websocketpp::connection_hdl handler,
                      websocketpp::config::asio::message_type::ptr msg)
{

  std::cout << "onMessage: " << msg->get_payload() << std::endl;

  server->send(handler, msg->get_payload(), websocketpp::frame::opcode::text);

}

websocketpp::lib::shared_ptr<SslContext>
ns_Server::onTlsInit(websocketpp::connection_hdl handler)
{
    
  std::shared_ptr<SslContext> ctx = websocketpp::lib::make_shared<SslContext>(SslContext::sslv23);

  ctx->use_certificate_chain_file("cert.pem");
  ctx->use_private_key_file("key.pem", SslContext::pem);
  return ctx;
}

void
ns_Server::turnOffLogging(Server& server)
{

  server.clear_access_channels(websocketpp::log::alevel::all);
  server.clear_error_channels(websocketpp::log::elevel::all);
}

void
ns_Server::turnOnLogging(Server& server)
{

  server.set_error_channels(websocketpp::log::elevel::all);
  server.set_access_channels(websocketpp::log::alevel::all ^ websocketpp::log::alevel::frame_payload);
}



void
ns_Server::setMessageHandler(Server& server) 
{
  server.set_message_handler(websocketpp::lib::bind(&onMessage, 
                                                    &server,
                                                    ns_Server::_1,
                                                    ns_Server::_2) );
}


void
ns_Server::setTlsInitHandler(Server& server)
{
  server.set_tls_init_handler(websocketpp::lib::bind(ns_Server::onTlsInit, ns_Server::_1));
}



int main() {

    Server server;

    ns_Server::turnOffLogging(server);

    server.init_asio();

    ns_Server::setMessageHandler(server);
    ns_Server::setTlsInitHandler(server);

    server.listen(30001);
    server.start_accept();
    server.run();

    return 0;
}

