#ifndef BIB_H
#define BIB_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <locale>
#include <vector>
#include <string>
#include <sstream>
#include <unistd.h>
#include <algorithm>

#include "wordkey.h"

using namespace std; 

const int t = 6; 



#define CHAR_SIZE 128


//structs 

struct Word {
    int ID; 
    string palavra; 
    string classe;
    string genero;
    string numero;  
    string significado; 
    bool deleted; 
}; 


struct Key {
    int ID; 
    WordKey word;
    streampos address;       //endereço de uma struct dentro do arquivo //
};

//node declaration
struct Node {    
    Key keys[t];              
    streampos children[t+1];  
    bool isLeaf; 
    int numChildren; 
}; 

struct Entry {
    WordKey entryWord;
    streampos pos; 
    int ID; 
};

//Trie declarationn
struct Trie {
    bool isLeaf;
    streampos character[CHAR_SIZE];
    streampos pos;
};

//FUNCOES

//preencher/ler arquivo dicionario
int fillFile(string arq_data_is, string arq_binary_is);
int readFile(string arq_binary_is);
Word construct(string line, int ID); 


//pesquisar no arquivo dicionario 
Word searchWordID(int id); 
Word searchWordAdress(streampos pos); 
Word searchWord(string word); 


//inserir no arquivo dicionario
streampos insertWordFinal(Word word);
Word doUserWord();  

//deletar geral
void deleteWord (streampos posInverted, string name_Arq);

//atualizar palavra no dicionario
int updateWord (streampos pos, Word updated); 


//arquivos de ints importantes
void saveInt(int a, int b, int c, int d); 
void lerInteiros(int& a, int& b, int& c, int& d);
int updateNumEntrys(int actualID);
int readNumEntry(); 

//FUNCTIONS TRIE
Trie initT();
streampos putInArqT(Trie trie);
Trie readInArqT(streampos pos);
int swapStructT(streampos posi, Trie trie); 
void insertT(string key, streampos pos);
streampos searchT(string key); 
int criaTrie(); 

//FUNCTIONS BTREE
Node init(); 
streampos putInArq(Node node); 
Node readInArq (streampos pos);
int swapStruct(streampos pos, Node node);  
void traverse(streampos p); 
void sort(Key *keys, int numKeys); 
Key split_child(streampos x, int i); 
void insert(Key key);

//emotional breakdown -- FUNCTIONS INVERTIDO
int generateInverted(string classe, string nomeArq);
int readInverted(string arq, string arqTxt); 
int generateInvertedVerb(string nomeArq);
int insertInverted(Entry entryToInsert , string nomeArq);
Entry findInverted(streampos pos, string nomeArq); 
int updateEntry (Entry newEntryValue, string nomeArq, streampos pos);
Entry binarySearchWord(string nomeArq, string targetWord);
streampos binarySearchPos(string nomeArq, string targetWord); 
void writeEntryPosition(string filename, Entry newEntry, streampos pos); 


//FUNCTIONS HOROSCOPO
int horoscopo();
int generateRandom(int fator, int tam); 
tuple<streampos, streampos, streampos, streampos, string> generateFrase(int fator, int op); 


//FUNCTIONS ADM
//int adm();
int includeWord();
int excludeWord();
int listWords();
int writeList(int op);
int writeListReverse(int op);
void buscaSignificado(); 

//functions index
//int invertido();    
//int classeInt(string auxclasse);
//int lerIndex(string classe, int id);



#endif // BIB_H