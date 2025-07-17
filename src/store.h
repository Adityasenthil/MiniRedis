#include <unordered_map>
#include <mutex>
#include <optional>

class KeyValueStore{
    public:

    std::mutex m;
    std::unordered_map<std::string, std::string> store;

    void set(std::string& key, std::string& value);
    
    std::optional<std::string> get(const std::string& key);
    
    void del(std::string& key);

};


std::string processInput(std::string input, KeyValueStore& kv);