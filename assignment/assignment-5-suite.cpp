#include <chrono>
#include <random>
#include <algorithm>
#include <iostream>
#include <vector>
#include <list>
#include <map>


template <typename K, typename V>
class HashMap {
private:
    std::vector<std::list<std::pair<K, V>>> table;
    std::hash<K> hasher;

public:
    HashMap(size_t capacity = 100) {
        table.resize(capacity);
    }

    void insert(const K& key, const V& value) {
        size_t bucket = hasher(key) % table.size();
        for (auto& kv : table[bucket]) {
            if (kv.first == key) {
                kv.second = value;
                return;
            }
        }
        table[bucket].push_back({key, value});
    }

    bool contains(const K& key) const {
        size_t bucket = hasher(key) % table.size();
        for (const auto& kv : table[bucket]) {
            if (kv.first == key) {
                return true;
            }
        }
        return false;
    }

    V& operator[](const K& key) {
        size_t bucket = hasher(key) % table.size();
        for (auto& kv : table[bucket]) {
            if (kv.first == key) {
                return kv.second;
            }
        }
        table[bucket].push_back({key, V()});
        return table[bucket].back().second;
    }

    void erase(const K& key) {
        size_t bucket = hasher(key) % table.size();
        table[bucket].remove_if([&key](const std::pair<K, V>& kv){return kv.first == key;});
        //table[bucket].remove_if([&key](const auto& kv){return kv.first == key;});
    }

    typename std::list<std::pair<K, V>>::iterator find(const K& key) {
        size_t bucket = hasher(key) % table.size();
        for (auto it = table[bucket].begin(); it != table[bucket].end(); ++it) {
            if (it->first == key) {
                return it;
            }
        }
        return table[bucket].end();
    }

    size_t size() const {
        size_t s = 0;
        for (const auto& bucket : table) {
            s += bucket.size();
        }
        return s;
    }

    void clear() {
        for (auto& bucket : table) {
            bucket.clear();
        }
    }

    size_t count(const K& key) const {
        size_t c = 0;
        size_t bucket = hasher(key) % table.size();
        for (const auto& kv : table[bucket]) {
            if (kv.first == key) {
                c++;
            }
        }
        return c;
    }

    bool empty() const {
        return size() == 0;
    }
};



template <typename V>
void runExperiment(const std::string& name) {
    std::default_random_engine gen;
    std::uniform_int_distribution<int> dist(1, 1000000);
    std::uniform_real_distribution<float> valueDist(0.0, 1.0);

    std::map<std::string, V> rbtree;

    // Insert elements
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; i++) {
        std::string key = std::to_string(dist(gen));
        V value = valueDist(gen);
        rbtree[key] = value;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << name << " insert took " << duration.count() << " microseconds." << std::endl;

    // Find elements
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; i++) {
        std::string key = std::to_string(dist(gen));
        V value = rbtree[key];
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << name << " operator[] took " << duration.count() << " microseconds." << std::endl;

    // Erase elements
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++) {
        std::string key = std::to_string(dist(gen));
        rbtree.erase(key);
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << name << " erase took " << duration.count() << " microseconds." << std::endl;
}

int main() {
    runExperiment<float>("Red-black tree (int keys)");
    runExperiment<float>("Red-black tree (string keys)");

    return 0;
}






