#include <iostream>
#include <unordered_map>
#include <memory>

class Node {
public:
    Node(int key, int value): key(key), value(value) {}
    void remove() {
        std::shared_ptr<Node> prev = this->prev;
        std::shared_ptr<Node> next = this->next;
        this->prev = nullptr;
        this->next = nullptr;

        if (prev != nullptr) {
            prev->next = next;
        }
        if (next != nullptr) {
            next->prev = prev;
        }
    }

    int key;
    int value;

    std::shared_ptr<Node> prev { nullptr };
    std::shared_ptr<Node> next { nullptr };
};

class LRUCache {
public:
    LRUCache(int capacity): capacity(capacity) {}

    int get(int key) {
        auto it = this->map.find(key);
        if (it == this->map.end()) {
            return -1;
        }

        std::shared_ptr<Node> node = it->second;

        if (node == this->tail && this->size() > 1) {
            this->tail = node->prev;
        }

        if (node != this->head) {
            // move node to the head
            node->remove();
            node->next = this->head;
            this->head->prev = node;
            this->head = node;
        }

        return node->value;
    }

    void put(int key, int value) {
        if (this->head == nullptr || this->tail == nullptr) {
            auto new_node = std::make_shared<Node>(key, value);
            this->head = new_node;
            this->tail = new_node;
            this->map.insert(std::pair<int, std::shared_ptr<Node>>(key, new_node));
            return;
        }

        auto it = this->map.find(key);
        if (it == this->map.end()) {
            auto new_node = std::make_shared<Node>(key, value);
            this->map.insert(std::pair<int, std::shared_ptr<Node>>(key, new_node));
            this->head->prev = new_node;
            new_node->next = this->head;
            this->head = new_node;
        } else {
            std::shared_ptr<Node> node = it->second;
            node->value = value;

            if (node == this->tail && this->size() > 1) {
                this->tail = node->prev;
            }

            if (node != this->head) {
                // move node to the head
                node->remove();
                node->next = this->head;
                this->head->prev = node;
                this->head = node;
            }
        }

        if (this->size() > this->capacity) {
            std::shared_ptr<Node> removed = this->tail;
            this->tail = removed->prev;
            removed->remove();

            this->map.erase(removed->key);
        }
    }

    void print() {
        int index = 0;
        auto node = this->head;
        while (node != nullptr) {
            std::cout << index << ": " << node->key << ' ' << node->value << '\n';
            node = node->next;
            index += 1;
        }
    }

    void map_print() {
        int index = 0;
        for (auto it: this->map) {
            std::cout << index << ": " << it.first << ' ' << it.second->key << ' ' << it.second->value << '\n';
            index += 1;
        }
    }

    int size() {
        return this->map.size();
    }

private:
    int capacity;
    std::shared_ptr<Node> head { nullptr };
    std::shared_ptr<Node> tail { nullptr };
    std::unordered_map<int, std::shared_ptr<Node>> map;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main() {
    LRUCache* obj = new LRUCache(2);

    obj->put(2, 1);
    obj->put(3, 2);
    std::cout << obj->get(3) << '\n';
    std::cout << obj->get(2) << '\n';
    obj->put(4, 3);
    std::cout << obj->get(2) << '\n';
    std::cout << obj->get(3) << '\n';
    std::cout << obj->get(4) << '\n';
    return 0;
}