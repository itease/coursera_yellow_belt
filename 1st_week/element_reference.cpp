#include <iostream>
#include <map>
#include <string>

using namespace std;

template<typename Key, typename Value>
Value& GetRefStrict(map<Key, Value>& init_map, const Key& key_value) {
    if (init_map.find(key_value) == init_map.end()) {
        throw runtime_error("the key doesn't exist");
    } else {
        return init_map.at(key_value);
    }
}

int main() {
    map<int, string> m = {{0, "value"}};
    string& item = GetRefStrict(m, 0);
    item = "new value";
    cout << m[0] << endl; // выведет new value

    return 0;
}
