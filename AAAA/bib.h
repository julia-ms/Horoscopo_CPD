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


struct Key {
    int ID; 
    string word;            //talvez isso aqui prejudique no tamanho, se prejudicar usaremos char word[50]
    streampos adress;       //endereço de uma struct dentro do arquivo 
};

//node declaration
struct Node {    
    //pensar melhor nessas estruturas
    Key* keys;              //array de keys 
    streampos* children;    //array de posicoes em arquivo
    streampos parent; 
    bool isLeaf; 
    int numChildren; 
}; 



//functions
int fillFile(string arq_data_is, string arq_binary_is);
int readFile(string arq_binary_is);
Word construct(string line, int ID); 

//functions Btree
Node init(); 
streampos putInArq(Node node); 
Node readInArq (streampos pos);
int swapStruct(streampos pos, Node node);  
void traverse(streampos p); 
void sort(Key *keys, int numKeys); 
Key split_child(streampos x, int i); 
void insert(Key key); 

#endif // BIB_H