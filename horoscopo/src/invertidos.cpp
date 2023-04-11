#include "../include/bib.h"
#include "../include/wordkey.h"

using namespace std;



//GERANDO INVERTIDO COM BINARIO ***********************************************************************************************************
int generateInverted(string classe, string nomeArq){

    Entry auxEntry;
    Word wordAux; 
    int numEntrysWrite = 0; 
    int ID;

    ifstream dic_binarya("../data/dictionary.bin", ios::binary);

    //verifica se o arquivo abriu ou não 
    if (!dic_binarya.is_open()) {
        cout << "deu ruim";
        return 1;  
    }

    // Posicionar o ponteiro de leitura no final do arquivo
    dic_binarya.seekg(0, std::ios::end);

    // Obter o tamanho do arquivo em bytes
    std::streampos fileSize = dic_binarya.tellg();

    // Voltar ao início do arquivo
    dic_binarya.seekg(0, std::ios::beg);

    ofstream inverted(nomeArq, ios::binary);
    
    streampos enderecoInicio;
    streampos enderecoFim;
    int tamanho; 

    //todo um role pra ler e pegar os enderecos  
    while(dic_binarya.tellg() < fileSize){
        // Obter o endereço do início da estrutura
        enderecoInicio = dic_binarya.tellg();

        // Ler a estrutura
        dic_binarya.read((char*)&wordAux.ID, sizeof(int));
        getline(dic_binarya, wordAux.palavra, '\0');
        getline(dic_binarya, wordAux.classe, '\0');
        getline(dic_binarya, wordAux.genero, '\0');
        getline(dic_binarya, wordAux.numero, '\0');
        getline(dic_binarya, wordAux.significado, '\0');  
        dic_binarya.read((char*)&wordAux.deleted, sizeof(bool));

        // Obter o endereço do final da estrutura
        enderecoFim = dic_binarya.tellg();

        // Calcular o tamanho da estrutura em bytes
        tamanho = enderecoFim - enderecoInicio;

        if (classe == wordAux.classe) {
            auxEntry.entryWord.clear();
            auxEntry.entryWord.fromString(wordAux.palavra);
            auxEntry.ID = wordAux.ID; 
            auxEntry.pos = enderecoInicio;

            inverted.write((char*)&auxEntry, sizeof(Entry));
            numEntrysWrite++; 
        }
    }
    
    dic_binarya.close(); 
    return numEntrysWrite; 
}

int readInverted(string arq, string arqTxt) {
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

    string aux; 
    ofstream inverted_read_teste(arqTxt);
    while(inverted_read.read((char*)&entryAux, sizeof(Entry))){
        //e aqui vou printar a struct pra mostrar que deu certo
        inverted_read_teste << entryAux.ID << endl;
        aux = entryAux.entryWord.toString(); 
        inverted_read_teste << aux << endl;         
        inverted_read_teste << entryAux.pos << endl << endl;
    }

    inverted_read_teste.close(); 
    inverted_read.close();

    return 0; 
}

//especial------------------------------------------------------------------------------------------------------------
int generateInvertedVerb(string nomeArq){

    Entry auxEntry;
    Word wordAux; 
    int ID; 
    int numEntrysWrite = 0; 

    ifstream dic_binary("../data/dictionary.bin", ios::binary);

    //verifica se o arquivo abriu ou não 
    if (!dic_binary.is_open()) {
        cout << "deu ruim";
        return 1;  
    }

    ofstream inverted(nomeArq, ios::binary);

    // Posicionar o ponteiro de leitura no final do arquivo
    dic_binary.seekg(0, std::ios::end);

    // Obter o tamanho do arquivo em bytes
    streampos fileSize = dic_binary.tellg();

    // Voltar ao início do arquivo
    dic_binary.seekg(0, std::ios::beg);
    
    streampos enderecoInicio;
    streampos enderecoFim;
    int tamanho; 

    //todo um role pra ler e pegar os enderecos  
    while(dic_binary.tellg() < fileSize){
        // Obter o endereço do início da estrutura
        enderecoInicio = dic_binary.tellg();

        // Ler a estrutura
        dic_binary.read((char*)&wordAux.ID, sizeof(int));
        getline(dic_binary, wordAux.palavra, '\0');
        getline(dic_binary, wordAux.classe, '\0');
        getline(dic_binary, wordAux.genero, '\0');
        getline(dic_binary, wordAux.numero, '\0');
        getline(dic_binary, wordAux.significado, '\0');  
        dic_binary.read((char*)&wordAux.deleted, sizeof(bool));

        // Obter o endereço do final da estrutura
        enderecoFim = dic_binary.tellg();

        // Calcular o tamanho da estrutura em bytes
        tamanho = enderecoFim - enderecoInicio;
        
        if (wordAux.classe == "v." |wordAux.classe == "v.,intr."|wordAux.classe =="v.,tr.,intr."|wordAux.classe =="v.,tr.") {
            auxEntry.entryWord.clear();
            auxEntry.entryWord.fromString(wordAux.palavra);
            auxEntry.ID = wordAux.ID; 
            auxEntry.pos = enderecoInicio;

            inverted.write((char*)&auxEntry, sizeof(Entry));
            numEntrysWrite++; 
        }
    }
    dic_binary.close(); 

    return numEntrysWrite; 
}

//INSERINDO EM INVERTIDO ********************************************************************************************************************

//aqui insiro um NOVO registro
int insertInverted(Entry entryToInsert , string nomeArq){
    //fazer busca binaria pra inserir em ordem alfabetica
    //aí usa um seekg combinado com ter aumentando a funcao em size of antes e insere com appende
    Entry auxEntry;

    ofstream inverted(nomeArq, ios::binary | ios::app);
    inverted.write((char*)&auxEntry, sizeof(Entry));
        
    inverted.close(); 

    return  0; 
}

//diferente do append, escreve em cima
int updateEntry (Entry newEntryValue, string nomeArq, streampos pos)  {
    Entry auxEntry;
    Entry readEntry; 

    auxEntry = newEntryValue; 

    fstream invertedUpdate(nomeArq, ios::binary | ios::in | ios::out) ;

    //lendo o que ta dentro só pra teste
    invertedUpdate.seekg(pos); 
    invertedUpdate.read((char*)&readEntry, sizeof(Entry));
    readEntry.entryWord.wPrint(); 


    //agora sim escrevendo em cima
    invertedUpdate.seekp(pos); 
    invertedUpdate.write((char*)&auxEntry, sizeof(Entry));
    invertedUpdate.close(); 
    return  0; 
}

//LENDO EM INVERTIDO ********************************************************************************************************************
Entry findInverted(streampos pos, string nomeArq){
    Entry auxEntry;

    ifstream invertedRead(nomeArq, ios::binary);

    invertedRead.seekg(pos); 
    invertedRead.read((char*)&auxEntry, sizeof(Entry));

/*
    cout << "Fui no endereco " << pos << " e ";  
    cout << " encontrei a palavra: "; 
    auxEntry.entryWord.wPrint();
    cout << endl; 
    invertedRead.close(); */

    return auxEntry; 
}