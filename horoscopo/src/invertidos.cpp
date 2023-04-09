#include "../include/bib.h"
#include "../include/wordkey.h"

using namespace std;



//gera um binario invertido de acordo com a classe e o nome de arquivo que recebe
int generateInverted(string classe, string nomeArq){

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

    //lendo numero de entradas pra nao me atrapalhar
    int numEntrys = 0; 
    dic_binary.read((char*)&numEntrys, sizeof(int));

    while(dic_binary.read((char*)&wordAux.ID, sizeof(int))){
        getline(dic_binary, wordAux.palavra, '\0');
        getline(dic_binary, wordAux.classe, '\0');
        getline(dic_binary, wordAux.genero, '\0');
        getline(dic_binary, wordAux.numero, '\0');
        getline(dic_binary, wordAux.significado, '\0');  
        dic_binary.read((char*)&wordAux.deleted, sizeof(bool)); 

        
        endLegal = dic_binary.tellg();
        endLegal = endLegal - sizeof(Entry);
        if (classe == wordAux.classe) {
            auxEntry.entryWord.clear();
            auxEntry.entryWord.fromString(wordAux.palavra); 
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

//escrevo o numero de entradas no inicio do arquivo
    fstream inverted_entrys(nomeArq, ios_base::binary | ios::in | ios::out);
    inverted_entrys.seekp(0, ios::beg ); 
    inverted_entrys.write((char*)&numEntrysWrite, sizeof(int));
    cout << "escrevi assim: " << numEntrysWrite; 


    inverted_entrys.close(); 
    return 0; 
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
    int numEntrys = 0; 
    inverted_read.read((char*)&numEntrys, sizeof(int));

    cout << "num entradas: " << numEntrys << endl << endl; 

    while(inverted_read.read((char*)&entryAux, sizeof(Entry))){
        //e aqui vou printar a struct pra mostrar que deu certo
       // cout << "ID:" << entryAux.ID<< endl; 
       // entryAux.entryWord.wPrint();
       // cout << endl;
       // cout << "endereco:"  << entryAux.pos << endl <<endl;
    }

    inverted_read.close();

    return 0; 
}