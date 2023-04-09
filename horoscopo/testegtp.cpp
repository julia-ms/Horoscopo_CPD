#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>
#include "bib.h"

using namespace std;

const int MAX_WORD_LENGTH = 100;

struct Entry {
    char word[MAX_WORD_LENGTH];
    streampos position;
    int id;
};

struct Class {
    char name[MAX_WORD_LENGTH];
    vector<Entry> entries;
};

struct InvertedIndex {
    vector<Class> classes;
};

void addEntry(InvertedIndex& index, const char* className, const Entry& entry) {
    auto it = find_if(index.classes.begin(), index.classes.end(), [&](const Class& c) {
        return strcmp(c.name, className) == 0;
    });
    if (it == index.classes.end()) {
        Class newClass;
        strcpy(newClass.name, className);
        newClass.entries.push_back(entry);
        index.classes.push_back(newClass);
    } else {
        it->entries.push_back(entry);
    }
}

void writeIndex(const InvertedIndex& index, const char* filename) {
    ofstream out(filename, ios::binary);
    for (const auto& c : index.classes) {
        out.write(reinterpret_cast<const char*>(&c.name), sizeof(c.name));
        int count = c.entries.size();
        out.write(reinterpret_cast<const char*>(&count), sizeof(count));
        for (const auto& e : c.entries) {
            out.write(reinterpret_cast<const char*>(&e.position), sizeof(e.position));
            out.write(reinterpret_cast<const char*>(&e.id), sizeof(e.id));
        }
    }
    out.close();
}

class BinarySearch {
public:
    BinarySearch(const vector<Entry>& entries) : entries(entries) {}

    streampos getPosition(int id) const {
        int l = 0, r = entries.size() - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (entries[mid].id == id) {
                return entries[mid].position;
            } else if (entries[mid].id < id) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return -1;
    }

private:
    const vector<Entry>& entries;
};

BinarySearch createSearch(const InvertedIndex& index, const char* className) {
    auto it = find_if(index.classes.begin(), index.classes.end(), [&](const Class& c) {
        return strcmp(c.name, className) == 0;
    });
    if (it != index.classes.end()) {
        return BinarySearch(it->entries);
    } else {
        return BinarySearch(vector<Entry>());
    }
}

int main() {
    InvertedIndex index;
    streampos addressWord = -1; 
    Word pWord;
    int ID;
    Entry e1; 
    fstream arquivo_dicionario("../data/dictionary.bin", ios::in | ios::binary);
    

    if (!arquivo_dicionario.is_open()) {
        cout << "deu ruimmm";
        return 1;  
    }


    int numEntrys = 0; 
    arquivo_dicionario.read((char*)&numEntrys, sizeof(int));

    cout << "entradas sao" << numEntrys; 

    while (arquivo_dicionario.read((char*)&pWord.ID, sizeof(int))){  

        getline(arquivo_dicionario, pWord.palavra, '\0');
        getline(arquivo_dicionario, pWord.classe, '\0');
        getline(arquivo_dicionario, pWord.genero, '\0');
        getline(arquivo_dicionario, pWord.numero, '\0');
        getline(arquivo_dicionario, pWord.significado, '\0');
        arquivo_dicionario.read((char*)&pWord.deleted, sizeof(bool)); 


        //pega endereco ao final da leitura e salva 
        addressWord = arquivo_dicionario.tellg();
        addressWord = addressWord - sizeof(Word); 


        const char* chars = pWord.genero.c_str();

        char word[100]; 
        int tam = pWord.palavra.length(); 
        if (tam>100) {
            return -1;  
        }
        for (auto i = 0; i < tam; i++){
            word[i] = pWord.palavra[i]; 
        }
    
        Entry e1; 
        e1.word = "word"; 

        addEntry(index, chars, e1);

    }
    arquivo_dicionario.close();

    // Entry e1 = {"foo", 100, 1};
    // addEntry(index, "class1", e1);
    // Entry e2 = {"bar", 200, 2};
    // addEntry(index, "class2", e2);
    // Entry e3 = {"baz", 300, 3};
    // addEntry(index, "class1", e3);
    // Entry e4 = {"qux", 400, 4};
    // addEntry(index, "class2", e4);

    writeIndex(index, "index.bin");

    BinarySearch search1 = createSearch(index, "class1");
    BinarySearch search2 = createSearch(index, "class2");

    cout << search1.getPosition(1) << endl; // should output 100
    cout << search1.getPosition(3) << endl; // should output 300
    cout << search1.getPosition(2) << endl;
    cout << search1.getPosition(2) << endl; // should output -1

    cout << search2.getPosition(2) << endl; // should output 200
    cout << search2.getPosition(4) << endl; // should output 400
    cout << search2.getPosition(1) << endl; // should output -1

    return 0;
}