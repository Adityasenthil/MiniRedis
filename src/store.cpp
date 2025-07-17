#include <unordered_map>
#include <mutex>
#include <optional>
#include <store.h>


void KeyValueStore::set(std::string& key, std::string& value){
    std::lock_guard<std::mutex> lock(m);
    store[key] = value;
}

std::optional<std::string> KeyValueStore::get(const std::string& key){
    std::lock_guard<std::mutex> lock(m);
    auto it = store.find(key);
    if (it == store.end()){
        return std::nullopt;
    }        
    return it->second;
}

void KeyValueStore::del(std::string& key){
    std::lock_guard<std::mutex> lock(m);
    store.erase(key);
}
