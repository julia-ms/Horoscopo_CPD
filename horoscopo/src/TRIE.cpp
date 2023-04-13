#include "../include/bib.h"

using namespace std;

const int ALPHABET_SIZE = 26;

/*struct TrieNode {
    TrieNode *children[26];
    Entry *entry;
};*/

TrieNode *createTrieNode() {
    TrieNode *node = new TrieNode;
    node->entry = nullptr;
    for (int i = 0; i < 26; i++) {
        node->children[i] = nullptr;
    }
    return node;
}

int trie(){

    ifstream bfile("../invertidos/preposicoes.bin", ios::binary);

    Entry entryAux; 

    int ID; 
    //verifica se o arquivo abriu ou não 
    if (!bfile.is_open()) {
        cout << "deu ruim";
        return 1;  
    }

    // Obter o tamanho do arquivo
    bfile.seekg(0, bfile.end);
    std::streampos fileSize = bfile.tellg();
    bfile.seekg(0, bfile.beg);

    // Ler as structs do arquivo binário e armazenar as palavras em um vetor de strings
    int numEntries = fileSize / sizeof(Entry);
    Entry *entries = new Entry[numEntries];
    bfile.read(reinterpret_cast<char *>(entries), fileSize);
    std::vector<std::string> words(numEntries);
    for (int i = 0; i < numEntries; i++) {
        string aux = entries[i].entryWord.toString();
        words[i] = aux;
    }

    TrieNode *root = createTrieNode();

    for (int i = 0; i < numEntries; i++) {
        string aux2 = entries[i].entryWord.toString(); 
        insertWord(root, aux2, entries[i].pos, entries[i].ID);
    }

    
    // Inserir palavras
    insertWord(root, "hello", 0, 1);
    insertWord(root, "world", 1, 2);
    
    // Imprimir todas as palavras da árvore
    printTrie(root);

    return 0;
}

    void insertWord(TrieNode *root, const std::string &word, std::streampos pos, int id) {
    TrieNode *current = root;
    int len = word.size();
    for (int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if (current->children[index] == nullptr) {
            current->children[index] = createTrieNode();
        }
        current = current->children[index];
    }
    if (current->entry == nullptr) {
        current->entry = new Entry;
        string aux3 = current->entry->entryWord.toString();

        current->entry->entryWord.fromString(aux3);
        current->entry->pos = pos;
        current->entry->ID = id;
    }
}

void printTrie(TrieNode *root) {
    if (root == nullptr) {
        return;
    }
    if (root->entry != nullptr) {
        string aux4 = root->entry->entryWord.toString();
        std::cout << aux4 << " ";
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        printTrie(root->children[i]);
    }
}