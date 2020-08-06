//#include <boost/beast/core.hpp>
//#include <boost/beast/websocket.hpp>
//#include <boost/asio/connect.hpp>
//#include <boost/asio/ip/tcp.hpp>
//#include <boost/beast/websocket/ssl.hpp>
//#include <boost/asio/ssl/stream.hpp>
//#include <boost/array.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <ClientToSocket.h>



//namespace beast = boost::beast;         // from <boost/beast.hpp>
//namespace http = beast::http;           // from <boost/beast/http.hpp>
//namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
//namespace net = boost::asio;            // from <boost/asio.hpp>
//namespace ssl = boost::asio::ssl;       // from <boost/asio/ssl.hpp>
//using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>


// Sends a WebSocket message and prints the response
//bool ClientToSocket::sendMessage(char const* message)
//{
//    try
//    {
//        net::io_context ioc;
//        tcp::resolver resolver{ ioc };
//        websocket::stream<tcp::socket> ws{ ioc };
//        ws.write(net::buffer(std::string(message)));
//    }
//    catch (std::exception const& e)
//    {
//        std::cerr << "Error: " << e.what() << std::endl;
//        return EXIT_FAILURE;
//    }
//
//    return EXIT_SUCCESS;
//}
//Connect
//bool ClientToSocket::Connect()
//{
//   
//
// 
//    std::string text = "hi";
//    std::string host = "localhost";
//    const int port = 10000;
//
//    boost::asio::io_context ios;
//
//    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(host), port);
//
//    boost::asio::ip::tcp::socket socket(ios);
//
//    socket.connect(endpoint);
//
//    boost::array<char, 128> buf;
//    std::copy(text.begin(), text.end(), buf.begin());
//    //boost::system::error_code error;
//    socket.write_some(boost::asio::buffer(buf, text.size()));
//    socket.close();
//
//
//
//
//
//    //try
//    //{
//
//    //    //boost::system::error_code error;
//    //    std::string text = "hi";
//    //    char const* host = "localhost";
//    //    char const* port = "10000";
//    //    // The io_context is required for all I/O
//    //    net::io_context ioc;
//    //    net::io_context::work wrk(ioc);
//    //    //ssl::context ctx{ ssl::context::tlsv12_client };
//
//    //    // These objects perform our I/O
//    //    tcp::resolver resolver(ioc);
//    //    net::ip::tcp::socket sock(ioc);
//    //    net::connect(sock, resolver.resolve(net::ip::tcp::resolver::query{ host, port }));
//    //    websocket::stream<tcp::socket> ws{ ioc };
//
//    //    // Look up the domain name
//    //    //auto const results = resolver.resolve(host, port);
//    //    //tcp::resolver::results_type endpoints = resolver.resolve(host, port);
//    //    
//    //    // Make the connection on the IP address we get from a lookup
//    //    //net::connect(ws.next_layer(), endpoints.begin(), endpoints.end());
//    //    
//    //    // Set a decorator to change the User-Agent of the handshake
//    //  /*  ws.set_option(websocket::stream_base::decorator(
//    //        [](websocket::request_type& req)
//    //        {
//    //            req.set(http::field::user_agent,
//    //                std::string(BOOST_BEAST_VERSION_STRING) +
//    //                " websocket-client-coro");
//    //        }));*/
//
//    //    
//    //    
//    //    // Perform the websocket handshake
//    //    ws.handshake(host, "/");
//    //    ws.write(net::buffer(text));
//    //    
//    //    //ws.write(net::buffer("hi"));
//    //    // Send the message
//    //    //ws.write(boost::asio::buffer(text.data(),text.size()), error);
//    //   // ws.async_write(boost::asio::buffer(text.data(), text.size()), ERROR);
//
//    //    // This buffer will hold the incoming message
//    //    beast::flat_buffer buffer;
//
//    //    // Read a message into our buffer
//    //    ws.read(buffer);
//
//    //    // Close the WebSocket connection
//    //    ws.close(websocket::close_code::normal);
//
//    //    // If we get here then the connection is closed gracefully
//
//    //    // The make_printable() function helps print a ConstBufferSequence
//    //    std::cout << beast::make_printable(buffer.data()) << std::endl;
//    //}
//    //try
//    //{
//    //    boost::system::error_code ec;
//    //    // Check command line arguments.
//    //    std::string text = "hi";
//    //    std::string host = "localhost";
//    //    char const* port = "10000";
//
//    //    // The io_context is required for all I/O
//    //    net::io_context ioc;
//
//    //    // These objects perform our I/O
//    //    tcp::resolver resolver{ ioc };
//    //    websocket::stream<tcp::socket> ws{ ioc };
//
//    //    // Look up the domain name
//    //    auto const results = resolver.resolve(host, port);
//
//    //    // Make the connection on the IP address we get from a lookup
//    //    auto ep = net::connect(ws.next_layer(), results);
//
//    //    // Update the host_ string. This will provide the value of the
//    //    // Host HTTP header during the WebSocket handshake.
//    //    // See https://tools.ietf.org/html/rfc7230#section-5.4
//    //    host += ':' + std::to_string(ep.port());
//
//    //    // Set a decorator to change the User-Agent of the handshake
//    //    ws.set_option(websocket::stream_base::decorator(
//    //        [](websocket::request_type& req)
//    //        {
//    //            req.set(http::field::user_agent,
//    //                std::string(BOOST_BEAST_VERSION_STRING) +
//    //                " websocket-client-coro");
//    //        }));
//    //    ioc.run(ec);
//    //    // Perform the websocket handshake
//    //    ws.handshake(host, "/");
//
//    //    // Send the message
//    //    ws.write(net::buffer(std::string(text)));
//    //    if (ec == boost::asio::error::operation_aborted)
//    //    {
//    //        std::cout << ec.message() << std::endl;
//    //    }
//    //    // This buffer will hold the incoming message
//    //    beast::flat_buffer buffer;
//
//    //    // Read a message into our buffer
//    //    ws.read(buffer);
//
//    //    // Close the WebSocket connection
//    //    ws.close(websocket::close_code::normal);
//
//    //    // If we get here then the connection is closed gracefully
//
//    //    // The make_printable() function helps print a ConstBufferSequence
//    //    std::cout << beast::make_printable(buffer.data()) << std::endl;
//    //
//    
//       return EXIT_SUCCESS;
//}
