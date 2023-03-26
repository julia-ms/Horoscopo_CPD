#ifndef BIB_H
#define BIB_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <locale>

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

//functions
int fillArchive(string arq_data_is, string arq_binary_is);
int readArchive(string arq_binary_is);
Word construct(string line, int ID); 


#endif // BIB_H