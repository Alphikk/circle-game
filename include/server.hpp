#include <websocketpp/server.hpp>
#include <websocketpp/config/asio.hpp>

using Server = websocketpp::server<websocketpp::config::asio_tls>;
using SslContext = websocketpp::lib::asio::ssl::context;

namespace ns_Server
{

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;

// class utilityServer {

// public:

//     utilityServer() {
//          // Set logging settings
//         mEndpoint.set_error_channels(websocketpp::log::elevel::all);
//         mEndpoint.set_access_channels(websocketpp::log::alevel::all ^ websocketpp::log::alevel::frame_payload);
 
//         // Initialize Asio
//         mEndpoint.init_asio();
//     }
 
//     void
//     run() {
//         // Listen on port 9002
//         mEndpoint.listen(9002);
 
//         // Queues a connection accept operation
//         mEndpoint.start_accept();
 
//         // Start the Asio io_service run loop
//         mEndpoint.run();
//     }

// private:
//     Server mEndpoint;
// };


// 
void
onMessage( Server* server,
            websocketpp::connection_hdl handler,
            websocketpp::config::asio::message_type::ptr msg);

// 
websocketpp::lib::shared_ptr<SslContext>
onTlsInit(websocketpp::connection_hdl handler);


void
turnOffLogging(Server& server);


void
turnOnLogging(Server& server);

void
setMessageHandler(Server& server);

void
setTlsInitHandler(Server& server);

}

