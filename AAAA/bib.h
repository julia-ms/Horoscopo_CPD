#ifndef BIB_H
#define BIB_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <locale>
#include <vector>

using namespace std; 


//structs 
struct Word {
    int ID; 
    string palavra; 
    string classe;
    string genero;
    string numero;  
    string significado; 
}; 

struct Node {    
    //pensar melhor nessas estruturas
    vector<Key> keys;
    vector<Node*> children; 
    Node* parent; 
    bool isLeaf; 
    int numKeys; 
}; 

struct Key {
    int ID; 
    string word; 
    int adress;         //endereço de uma struct dentro do arquivo 
};

//funcoes
int fillFile(string arq_data_is, string arq_binary_is);
int readFile(string arq_binary_is);
Word construct(string line, int ID); 

int createBTree(string arq_binary_is);
int newUserWord();
string doStringWord(); 
int insertWord(string line, string arq_binary_is, string arq_Btree_is);
int deleteWord(string word, string arq_binary_is, string arq_Btree_is);
int createBTree(string arq_binary_is, Word word); 
int insertInBTree(Node* &root, Key key, int t);
int deleteInBTree(string arq_binary_is, Word word);


#endif // BIB_H