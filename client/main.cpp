#include <iostream>
#include <boost/asio.hpp>
using boost::asio::ip::tcp;

int main(int argc, char* argv[]){
  
  boost::asio::io_context ioContext;
  tcp::resolver resolver(ioContext);
  tcp::socket socket(ioContext);
  auto endpoint = resolver.resolve(argv[1], "12345");

  boost::asio::connect(socket, endpoint);
  std::cout << "Connected to " << argv[1] << std::endl;

  while (true){
    std::array<char, 128> buf;
  
    std::cout << "Enter Command: " << std::endl;
    std::string command;
    std::getline(std::cin, command);
    if (command == "END"){
      break;
    }
    command += "\n";
    boost::asio::write(socket, boost::asio::buffer(command));

    auto len = socket.read_some(boost::asio::buffer(buf));
    std::cout << "Response: " << std::string(buf.data(), len) << std::endl;

  }
}
