#include <iostream>
#include <boost/asio.hpp>
#include <store.h>


using boost::asio::ip::tcp;



std::string processInput(std::string input, KeyValueStore& store){


    std::string key;
    std::string value;


    auto it = input.find(" ");

    if (input.substr(0,3) == "SET"){
        auto it1 = input.find(" ", it + 1);
        key = input.substr(it + 1, it1 - it - 1);
        value = input.substr(it1 + 1);

        store.set(key, value);
        return "OK\n";
    }
    
    else if (input.substr(0,3) == "GET"){
        key = input.substr(it + 1);
        auto res = store.get(key);
        if (res.has_value()){
            return res.value() + "\n";
        }
        return "NOT FOUND\n";
    }
    
    else if (input.substr(0,3) == "DEL"){
        key = input.substr(it + 1);
        store.del(key);
        return "OK\n";
    }

    else if (input.substr(0,3) == "END"){
        return "END\n";
    }

    return "ERROR\n";
    
}
