#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

const int ALPHABET_SIZE = 26;

class Trie {
private:
    struct Node {
        bool isEndOfWord;
        Node *children[ALPHABET_SIZE];

        Node() {
            isEndOfWord = false;
            memset(children, 0, sizeof(children));
        }

        ~Node() {
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                delete children[i];
            }
        }
    };

    Node *root;

    void insert(Node *node, const string &key, int index) {
        if (index == key.size()) {
            node->isEndOfWord = true;
            return;
        }

        int charIndex = key[index] - 'a';
        if (!node->children[charIndex]) {
            node->children[charIndex] = new Node();
        }

        insert(node->children[charIndex], key, index + 1);
    }

    bool search(Node *node, const string &key, int index) const {
        if (index == key.size()) {
            return node->isEndOfWord;
        }

        int charIndex = key[index] - 'a';
        if (!node->children[charIndex]) {
            return false;
        }

        return search(node->children[charIndex], key, index + 1);
    }

public:
    Trie() {
        root = new Node();
    }

    ~Trie() {
        delete root;
    }

    void insert(const string &key) {
        insert(root, key, 0);
    }

    bool search(const string &key) const {
        return search(root, key, 0);
    }

    void saveToFile(const char *fileName) const {
        ofstream file(fileName, ios::binary);
        saveToFile(root, file);
    }

    void loadFromFile(const char *fileName) {
        ifstream file(fileName, ios::binary);
        loadFromFile(root, file);
    }

    void clear() {
        if (root) {
            delete root;
            root = nullptr;
        }

    }

private:
    void saveToFile(const Node *node, ofstream &file) const {
        file.write((char*)&node->isEndOfWord, sizeof(node->isEndOfWord));
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (node->children[i]) {
                file.write((char*)&i, sizeof(i));
                saveToFile(node->children[i], file);
            }
        }
        int nullChar = -1;
        file.write((char*)&nullChar, sizeof(nullChar));
    }

    void loadFromFile(Node *&node, ifstream &file) {
        node = new Node();
        file.read((char*)&node->isEndOfWord, sizeof(node->isEndOfWord));
        int charIndex;
        file.read((char*)&charIndex, sizeof(charIndex));
        while (charIndex != -1) {
            loadFromFile(node->children[charIndex], file);
            file.read((char*)&charIndex, sizeof(charIndex));
        }
    }
};

int main() {
    // Create a new Trie
    Trie trie;

    // Insert some words
    trie.insert("apple");
    trie.insert("banana");
    trie.insert("cherry");
    trie.insert("dog");
    trie.insert("cat");
    trie.insert("sk");
 /*   // Insert 100 random words
    std::srand(std::time(nullptr)); // Seed the random number generator with the current time
    const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < 100000; i++) {
        std::string word;
        int length = std::rand() % 10 + 1; // Random word length between 1 and 10
        for (int j = 0; j < length; j++) {
            int index = std::rand() % alphabet.size(); // Random index in the alphabet string
            word += alphabet[index]; // Add a random letter to the word
        }
        trie.insert(word);
        if(i == 20000){
            //cout << word << endl;
            cout << "oi" << endl;
        }
    }
*/

    // Save the trie to a binary file
    trie.saveToFile("trie.bin");

    // Clear the trie to make sure we can load it back in correctly
    trie.clear();

    // Load the trie from the binary file
    Trie loadedTrie;
    loadedTrie.loadFromFile("trie.bin");

    // Search for some words in the loaded trie
    std::cout << loadedTrie.search("apple") << std::endl;  // true
    std::cout << loadedTrie.search("banana") << std::endl; // true
    std::cout << loadedTrie.search("cherry") << std::endl; // true
    std::cout << loadedTrie.search("dog") << std::endl;    // true
    std::cout << loadedTrie.search("cat") << std::endl;    // true
    std::cout << loadedTrie.search("sk") << std::endl;    // true
    std::cout << loadedTrie.search("bultdvmzkd") << std::endl;    // true
    std::cout << loadedTrie.search("zebra") << std::endl;  // false

    return 0;
}

