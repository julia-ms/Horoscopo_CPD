#include  "../include/wordkey.h"


using namespace std; 

int WordKey::fromString(string str) {
    int tam = str.length(); 
    if (tam>tamStr) {
        return -1;  
    }
    for (auto i = 0; i < tam; i++){
        word[i] = str[i]; 
    }
    return 0; 
}

string WordKey::toString() {
    string str; 
    
    int i = 0; 
    while (word[i] != '\0' && i<tamStr){
        str = str + word[i];
        i++;
    }
    return str;
}

void WordKey::clear(){
    int i = 0; 
    while (i<tamStr){
        word[i] = '\0'; 
        i++;
    }
}

void WordKey::wPrint() {
    int i = 0; 
    while (word[i] != '\0' && i<tamStr){
        cout << word[i];
        i++;
    }
}

int WordKey::compareW(string str){
    int comp; 
    string wordStr; 

    wordStr = toString();               //porque ja sei que estou lidando com a word
    comp = wordStr.compare(str); 

    //valores de comp: 
    // 0 -> string iguais
    // > 0 -> wordStr eh maior, vem depois
    // < 0 -> wordStr eh menor, vem antes
    return comp; 
}
