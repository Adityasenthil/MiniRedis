#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <store.h>
#include <queue>
#include <mutex>
#include <optional>


using boost::asio::ip::tcp;

void handle(tcp::socket socket, KeyValueStore &kv){
    
    while (true){
        boost::asio::streambuf buf;
        boost::asio::read_until(socket, buf, '\n');
        std::istream stream(&buf);
        std::string message;
        std::getline(stream, message);

        std::cout << "Received: " << message << std::endl;

        auto output = processInput(message, kv);
        if (output == "EXIT"){
            exit(0);
        }
        std::cout << "Output: " << output;

        boost::asio::write(socket, boost::asio::buffer(output));
        
    }

}



void server(KeyValueStore &kv){
    int PORT = 12345;
    int NUMTHREADS = 10;


   
    boost::asio::io_context ioContext;

    boost::asio::executor_work_guard<boost::asio::io_context::executor_type> workGuard =
    boost::asio::make_work_guard(ioContext);


    auto endpoint = tcp::endpoint(tcp::v4(), PORT);

    tcp::acceptor acceptor(ioContext, endpoint);

    std::vector<std::thread> arr;

    for (int i = 0; i < NUMTHREADS; i++){
        arr.emplace_back([&ioContext]() {
            ioContext.run();
        });
    }


    for (;;){


        std::cout << "Listening ... " << std::endl;
        tcp::socket socket(ioContext);
        acceptor.accept(socket);
        std::cout << "Client connected" << std::endl;

        boost::asio::post(ioContext, [s = std::move(socket), &kv] mutable {
            handle(std::move(s), kv);
        });
    }

       

}


        


    
        // std::thread t(handle, std::move(socket), std::ref(kv));
        // t.detach();
