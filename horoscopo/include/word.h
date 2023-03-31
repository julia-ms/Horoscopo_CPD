#ifndef WORD_H
#define WORD_H

#include <iostream>
#include <cstring>
#include <fstream>

// criando uma classe word, que seja um array de tamanho fixo, e que deve ter as seguintes funções
    // fromString  = recebo uma string e devolvo uma word com os caracteres dela
    // toString    = recebo uma word e passo para uma string 
    // compare     = comparo uma word com uma string
    // Clear       = recebo uma word e preencho tudo com NUll
    // wPrint      = recebo uma word e printo na tela

using namespace std; 

const int tamStr = 50 + 1;

class Word {
    private: 
        char word[50] = {'\0'}; 

    public:
        int fromString(string str);
        string toString();
        void clear();
        void wPrint();
        int compareW(string str);
};

#endif