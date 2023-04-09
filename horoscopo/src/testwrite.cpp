#include "../include/wordkey.h"

//escrever duas structs, gravar em um arquivo binário e ler de volta

using namespace std; 

const int t = 3; 

struct Key {
    int ID; 
    WordKey word;  
    streampos address;       //endereço de uma struct dentro do arquivo //
};

//node declaration
struct Node {    
    Key keys[t];              //array de keys 
    streampos children[t+1];    //array de posicoes em arquivo
    streampos parent; 
    bool isLeaf; 
    int numChildren; 
}; 

int main() {
    Key key1, key2, key3;
    Node node1, node2, node3;
    Node node1Aux, node2Aux;  
    streampos pos;

    pos = -1; 

//preenchendo teste ------------------------------------------------------------------------------------------
    key1.word.fromString("dicionario"); 
    key2.word.fromString("abajour"); 
    key3.word.fromString("frogarm"); 

    key1.ID = 20;
    key2.ID = 30;
    key3.ID = 40;

    node1.keys[0] = key1; 
    node2.keys[0] = key2; 
    node2.keys[1] = key3; 


//escrevendo teste ------------------------------------------------------------------------------------------
    ofstream BTree("Btree.bin", ios::binary);
    BTree.write((char*)&node1, sizeof(Node));
    BTree.close();

//lendo teste ------------------------------------------------------------------------------------------
    ifstream BTree2("Btree.bin", ios::binary);
    BTree2.read((char*)&node1Aux, sizeof(Node)); 
    BTree2.close(); 

//printando teste ------------------------------------------------------------------------------------------
    node1Aux.keys[0].word.wPrint();
    cout << endl;

//escrevendo teste de novo ------------------------------------------------------------------------------------------
    ofstream BTree3("Btree.bin", ios::binary | ios::app);
    
    BTree3.write((char*)&node2, sizeof(Node));
    pos = BTree3.tellp();                   //depois de escrever ele posiciona onde comeceu a escrever

    BTree3.close();

//lendo com endereco ------------------------------------------------------------------------------------------
    ifstream BTree4("Btree.bin", ios::binary);

    BTree4.seekg(pos); 
    BTree4.read((char*)&node2Aux, sizeof(Node)); 
    BTree4.close(); 

//printando teste ------------------------------------------------------------------------------------------
    
    node2Aux.keys[0].word.wPrint();
    node2Aux.keys[1].word.wPrint();

    return 0; 
}

