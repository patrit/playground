#include <string>
#include <unordered_map>

class LargeMap {
public:
    typedef std::unordered_map<std::string, std::unordered_map<std::string, int>> Map;
    static Map const&getMap() { return _map; }
private:
    static Map _map;
};