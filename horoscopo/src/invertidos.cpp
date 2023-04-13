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
    streampos positionIn; 
    Entry auxEntry;
    string busca; 
    int posicaoAux; 

    auxEntry = entryToInsert; 
    busca = entryToInsert.entryWord.toString(); 
    //a posicao de entrada eh onde estava o primeiro maior
    //se a palavra ja existe, eu reescrevo só, entao de boa
    positionIn = binarySearchPos(nomeArq, busca); 
    writeEntryPosition(nomeArq, entryToInsert, positionIn);
    
    return  0; 
}

//faco escrever na posicao que quero

void writeEntryPosition(string filename, Entry newEntry, streampos pos) {

    fstream file(filename, std::ios::in | std::ios::out | std::ios::binary);
    if (!file) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return;
    }

    pos = pos/sizeof(Entry); 


    // Calcule o tamanho do arquivo em bytes.
    file.seekg(0, std::ios::end);
    streampos file_size = file.tellg();

    //calcula tamanho da entrada
    int sizeEntrada = sizeof(Entry); 
    
    // Verifique se a posição de escrita está dentro do arquivo.
    if (pos > file_size / sizeof(Entry)) {
        std::cerr << "Posição de escrita inválida." << std::endl;
        return;
    }



    // Desloque os registros existentes para baixo a partir da posição de escrita.
    std::size_t num_records_to_shift = file_size / sizeof(Entry) - pos;

    //coloco ponteiro de escrita final do arquivo 
    
    // Obtém o tamanho atual do arquivo
    file.seekp(0, std::ios::end);
    std::streampos tamanhoAtual = file.tellp();

    //coloca o ponteiro de leitura no final menos 1 entrada
    int tamanhoAtualInt = tamanhoAtual;
    int posicaoPointer; 
    posicaoPointer = tamanhoAtualInt-sizeEntrada; 
    file.seekg(posicaoPointer); 

    streampos posAtual; 
    int posAtualInt; 

    for (size_t i = 0; i < num_records_to_shift; i++) {
        // Posicione o ponteiro de leitura/gravação no registro anterior.
        // file.seekg((pos + num_records_to_shift - i - 1) * sizeof(Entry));
        // Entry prev_entry;
        // file.read((char*)&prev_entry, sizeof(Entry));

        // // Posicione o ponteiro de gravação no registro atual.
        // file.seekp((pos + num_records_to_shift - i) * sizeof(Entry));
        // file.write((char*)&prev_entry, sizeof(Entry));

        Entry prev_entry; 
        
        //leio o ultimo e guardo onde li
        posAtual = file.tellg(); 
        file.read((char*)&prev_entry, sizeof(Entry));

        //vou um na frente e escrevo la  
        posAtualInt = posAtual;
        posAtualInt = posAtualInt + sizeof(Entry); 
        file.seekp(posAtualInt); 
        file.write((char*)&prev_entry, sizeof(Entry)); 

        
        posAtualInt = posAtual;
        posAtualInt = posAtualInt - sizeof(Entry); 
        //volto pra ler um atras
        file.seekg(posAtualInt); 
    }

    // Posicione o ponteiro de gravação no novo registro.
    file.seekp(pos * sizeof(Entry));
    file.write((char*)&newEntry, sizeof(Entry));

    file.close();
}

//diferente do append, escreve em cima
int updateEntry (Entry newEntryValue, string nomeArq, streampos pos)  {
    Entry auxEntry;
    Entry readEntry; 

    auxEntry = newEntryValue; 

    fstream invertedUpdate(nomeArq, ios::binary | ios::in | ios::out) ;

    //lendo o que ta dentro só pra teste
    //invertedUpdate.seekg(pos); 
    //invertedUpdate.read((char*)&readEntry, sizeof(Entry));
    //readEntry.entryWord.wPrint(); 

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

//BUSCA BINÁRIA EM INVERTIDO **************************************
//busca por palavra


// Função de comparação para busca binária
bool compare( Entry a, Entry b) {
    string bstr;
    int compare; 
    int retorno = 0; 

    //retorna > 0 quando a eh maior 
    //retorna 0 quando eh igual
    //retorna < 0 quando a eh menor

    bstr = b.entryWord.toString(); 
    
    compare = a.entryWord.compareW(bstr); 

    if (compare < 0 )
        retorno = 1; 
    return retorno;
}

// Função de busca binária em arquivo invertido
Entry binarySearchWord(string nomeArq, string targetWord) {

    Entry errorEntry; 

    errorEntry.ID = -1; 

    //abrindo arquivo de índice
    ifstream file_binary_search(nomeArq, ios::binary);

    if (!file_binary_search.is_open()) {
        cerr << "Erro ao abrir arquivo" << endl;
        return errorEntry;
    }

    // Verifica o tamanho do arquivo
    file_binary_search.seekg(0, ios::end);
    streampos fileSize = file_binary_search.tellg();

    // Define os limites da busca
    int low = 0;
    int high = fileSize / sizeof(Entry) - 1;

    while (low <= high) {
        // Calcula o meio do intervalo
        int mid = (low + high) / 2;

        // Posiciona o ponteiro no registro do meio
        file_binary_search.seekg(mid * sizeof(Entry));
        Entry midEntry;

        file_binary_search.read((char*)&midEntry, sizeof(Entry));

        // Compara a palavra-chave do registro do meio com a palavra-alvo
        if (midEntry.entryWord.compareW(targetWord) == 0 ) {
            // Encontrou o registro, retorna a posição dele no arquivo
            return midEntry;
        } 
        else if (midEntry.entryWord.compareW(targetWord) < 0) {

            // target eh maior que midEntry quando retorna menor que 0
            // A palavra-alvo é maior que a palavra-chave do registro do meio,
            // portanto a busca deve continuar na metade superior do intervalo
            low = mid + 1;
        } else {
            // A palavra-alvo é menor que a palavra-chave do registro do meio,
            // portanto a busca deve continuar na metade inferior do intervalo
            high = mid - 1;
        }
    }

    file_binary_search.close();


    // Não encontrou o registro, retorna -1
    return errorEntry;
}

// Função de busca binária em arquivo invertido
// Uso pra buscar a posicao de insercao
streampos binarySearchPos(string nomeArq, string targetWord) {

    streampos pos; 
    //abrindo arquivo de índice
    ifstream file_binary_search(nomeArq, ios::binary);

    if (!file_binary_search.is_open()) {
        cerr << "Erro ao abrir arquivo" << endl;
        return -1;
    }

    // Verifica o tamanho do arquivo
    file_binary_search.seekg(0, ios::end);
    streampos fileSize = file_binary_search.tellg();

    // Define os limites da busca
    streampos low = 0;
    streampos high = fileSize / sizeof(Entry) - 1;

    int lowInt; 
    int highInt; 


    streampos mid; 
    int midInt; 

    while (low <= high) {
        // Calcula o meio do intervalo
        mid = (low + high) / 2;

        // Posiciona o ponteiro no registro do meio
        file_binary_search.seekg(mid * sizeof(Entry));
        Entry midEntry;

        file_binary_search.read((char*)&midEntry, sizeof(Entry));

        // Compara a palavra-chave do registro do meio com a palavra-alvo
        if (midEntry.entryWord.compareW(targetWord) == 0 ) {
            // Encontrou o registro, retorna a posição dele no arquivo
            cout << "encontrei"; 
            return mid * sizeof(Entry);
        } 
        else if (midEntry.entryWord.compareW(targetWord) < 0) {

            // target eh maior que midEntry quando retorna menor que 0
            // A palavra-alvo é maior que a palavra-chave do registro do meio,
            // portanto a busca deve continuar na metade superior do intervalo
            lowInt = low; 
            midInt = mid; 
            lowInt = midInt + 1; 

            low = lowInt;
        } else {
            // A palavra-alvo é menor que a palavra-chave do registro do meio,
            // portanto a busca deve continuar na metade inferior do intervalo
            highInt = high; 
            midInt = mid; 
            highInt = midInt - 1; 

            high = highInt;
        }
    }

    file_binary_search.close();


    // Não encontrou o registro, retorna -1
    return mid*sizeof(Entry);
}
