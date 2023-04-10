#include "../include/bib.h"
#include "../include/wordkey.h"

using namespace std;



//GERANDO INVERTIDO COM BINARIO ***********************************************************************************************************
int generateInverted(string classe, string nomeArq){

    Entry auxEntry;
    Word wordAux; 

    int ID; 
    streampos endLegal; 

    int numEntrysWrite = 0; 

    ifstream dic_binarya("../data/dictionary.bin", ios::binary);

    //verifica se o arquivo abriu ou não 
    if (!dic_binarya.is_open()) {
        cout << "deu ruim";
        return 1;  
    }

    ofstream inverted(nomeArq, ios::binary);

    //lendo numero de entradas pra nao me atrapalhar
    // int numEntrys = 0; 
    // dic_binary.read((char*)&numEntrys, sizeof(int));

    while(dic_binarya.read((char*)&wordAux.ID, sizeof(int))){
        getline(dic_binarya, wordAux.palavra, '\0');
        getline(dic_binarya, wordAux.classe, '\0');
        getline(dic_binarya, wordAux.genero, '\0');
        getline(dic_binarya, wordAux.numero, '\0');
        getline(dic_binarya, wordAux.significado, '\0');  
        dic_binarya.read((char*)&wordAux.deleted, sizeof(bool)); 

        int endChato; 
        endLegal = dic_binarya.tellg();
        endChato = endLegal; 
        endChato = endChato - sizeof(wordAux.palavra);
        endChato = endChato - sizeof(wordAux.classe);
        endChato = endChato - sizeof(wordAux.genero);
        endChato = endChato - sizeof(wordAux.numero);
        endChato = endChato - sizeof(wordAux.palavra);
        endChato = endChato - sizeof(wordAux.significado);
        endChato = endChato - sizeof(int);
        endChato = endChato - sizeof(bool);
        //endChato = endChato - sizeof(wordAux);
        endLegal = endChato; 
        

        if (classe == wordAux.classe) {
            auxEntry.entryWord.clear();
            auxEntry.entryWord.fromString(wordAux.palavra);
            //cout << "escrevi: "; 
            //auxEntry.entryWord.wPrint(); 
            auxEntry.ID = wordAux.ID; 
            auxEntry.pos = endLegal;

            inverted.write((char*)&auxEntry, sizeof(Entry));
            numEntrysWrite++; 
        }
    }
    
    if (!dic_binarya.eof()) {
        cout << "Não foi possível ler todo o arquivo.\n";
        return 1;
    }

    dic_binarya.close(); 

    return numEntrysWrite; 
}

int readInverted(string arq) {
    ifstream inverted_read(arq, ios::binary);

    Entry entryAux; 

    int ID; 
    //verifica se o arquivo abriu ou não 
    if (!inverted_read.is_open()) {
        cout << "deu ruim";
        return 1;  
    }

    //lendo numero de entradas pra nao me atrapalhar
    //int numEntrys = 0; 
    //inverted_read.read((char*)&numEntrys, sizeof(int));

    //cout << "num entradas: " << numEntrys << endl << endl; 

    while(inverted_read.read((char*)&entryAux, sizeof(Entry))){
        //e aqui vou printar a struct pra mostrar que deu certo
        cout << entryAux.ID << endl;
        entryAux.entryWord.wPrint();
        cout << endl; 
        cout << entryAux.pos << endl << endl;
    }


    inverted_read.close();

    return 0; 
}

//especial------------------------------------------------------------------------------------------------------------
int generateInvertedVerb(string nomeArq){

    Entry auxEntry;
    Word wordAux; 

    int ID; 
    streampos endLegal; 

    int numEntrysWrite = 0; 

    ifstream dic_binary("../data/dictionary.bin", ios::binary);

    //verifica se o arquivo abriu ou não 
    if (!dic_binary.is_open()) {
        cout << "deu ruim";
        return 1;  
    }

    ofstream inverted(nomeArq, ios::binary);

    // //lendo numero de entradas pra nao me atrapalhar
    // int numEntrys = 0; 
    // dic_binary.read((char*)&numEntrys, sizeof(int));

    while(dic_binary.read((char*)&wordAux.ID, sizeof(int))){
        getline(dic_binary, wordAux.palavra, '\0');
        getline(dic_binary, wordAux.classe, '\0');
        getline(dic_binary, wordAux.genero, '\0');
        getline(dic_binary, wordAux.numero, '\0');
        getline(dic_binary, wordAux.significado, '\0');  
        dic_binary.read((char*)&wordAux.deleted, sizeof(bool)); 

        int endChato; 
        endLegal = dic_binary.tellg();
        endChato = endLegal; 
        endChato = endChato - sizeof(wordAux);
        endLegal = endChato; 

        if (wordAux.classe == "v." |wordAux.classe == "v.,intr."|wordAux.classe =="v.,tr.,intr."|wordAux.classe =="v.,tr.") {
            auxEntry.entryWord.clear();
            auxEntry.entryWord.fromString(wordAux.palavra);
            //cout << "escrevi: "; 
            //auxEntry.entryWord.wPrint(); 
            auxEntry.ID = wordAux.ID; 
            auxEntry.pos = endLegal;

            inverted.write((char*)&auxEntry, sizeof(Entry));
            numEntrysWrite++; 
        }
    }
    
    if (!dic_binary.eof()) {
        cout << "Não foi possível ler todo o arquivo.\n";
        return 1;
    }

    dic_binary.close(); 

    return numEntrysWrite; 
}

//INSERINDO EM INVERTIDO ********************************************************************************************************************
int insertInverted(Entry entryToInsert , string nomeArq){
    //fazer busca binaria pra inserir em ordem alfabetica
    Entry auxEntry;

    ofstream inverted(nomeArq, ios::binary | ios::app);
    inverted.write((char*)&auxEntry, sizeof(Entry));
        
    inverted.close(); 

    return  0; 
}

//LENDO EM INVERTIDO ********************************************************************************************************************
Entry findInverted(streampos pos, string nomeArq){
    Entry auxEntry;

    ifstream invertedRead(nomeArq, ios::binary);

    invertedRead.seekg(pos); 
    invertedRead.read((char*)&auxEntry, sizeof(Entry));
    invertedRead.close(); 

    return auxEntry; 
}