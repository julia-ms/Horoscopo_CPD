#include "bib.h"

using namespace std;

const int t = 250;

int createBTree(string arq_binary_is) {
    ifstream dic_binary(arq_binary_is, ios::binary);
    ofstream B_tree("btree.bin", ios::binary);
    

    dic_binary.close();
    B_tree.close();
    return 0; 
}

struct Node* createNode (Word wordAux) {
    Node auxNode; 
}

int insertInBTree(Node* &root, Key key, int t){

    return 0; 
}

int deleteInBTree(string arq_binary_is, Word word){

    return 0; 
}

