#include<bits/stdc++.h>

/* Require -std=c++17 */
template<typename K, typename V> class LRUCache {
  private:
    int capacity = 0;
    std::list<std::pair<K, V>> list;
    std::map<K, typename std::list<std::pair<K, V>>::iterator> map;
  public:
    LRUCache(int capacity): capacity(capacity) {}
    std::optional<V> get(K key) {
        auto iter = map.find(key); if(iter == map.end()) { return std::nullopt; }
        list.push_front(*iter->second); list.erase(iter->second);
        map[key] = list.begin();
        return map[key]->second;
    }
    void put(K key, V value) {
        while(map.size() >= capacity) { map.erase(list.back().first); list.pop_back(); }
        auto iter = map.find(key); if(iter != map.end()) { list.erase(iter->second); }
        list.push_front({key, value});
        map[key] = list.begin();
    }
};

int main() {
    LRUCache<std::string, std::string> cache(3);
    cache.put("a", "1");
    cache.put("b", "2");
    cache.put("c", "3");
    std::cout << cache.get("c").value() << '\n';
    std::cout << cache.get("b").value() << '\n';
    std::cout << cache.get("a").value() << '\n';
    cache.put("d", "4");
    std::cout << cache.get("a").value() << '\n';
    std::cout << cache.get("b").value() << '\n';
    std::cout << cache.get("c").has_value() << '\n';
}