#include <iostream>
#include <vector>
#include <list>

using namespace std;

// Class for the dictionary
class Dictionary {
private:
    static const int TABLE_SIZE = 10;
    vector<list<pair<int, string>>> table;

    // Hash function
    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

public:
    // Constructor
    Dictionary() {
        table.resize(TABLE_SIZE);
    }

    // Function to insert a key-value pair
    void insert(int key, const string& value) {
        int index = hashFunction(key);
        table[index].push_back(make_pair(key, value));
    }

    // Function to search for a value given a key
    string search(int key) {
        int index = hashFunction(key);
        for (auto& entry : table[index]) {
            if (entry.first == key) {
                return entry.second;
            }
        }
        return "Key not found";
    }
};

int main() {
    Dictionary dictionary;

    // Insert some key-value pairs
    dictionary.insert(1, "Apple");
    dictionary.insert(11, "Banana");
    dictionary.insert(21, "Orange");

    // Search for some keys
    cout << "Value for key 1: " << dictionary.search(1) << endl;
    cout << "Value for key 11: " << dictionary.search(11) << endl;
    cout << "Value for key 21: " << dictionary.search(21) << endl;
    cout << "Value for key 2: " << dictionary.search(2) << endl;

    return 0;
}
