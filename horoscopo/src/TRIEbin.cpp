#include "../include/bib.h"

using namespace std;
 
// Define o tamanho do caractere
 

streampos root = -1; 


Trie initT() {
    Trie trie;
    trie.isLeaf = false; 
    for (int i = 0; i < CHAR_SIZE; i++) {
            trie.character[i] = -1;
    }
    trie.pos = -1; 
    return trie;
}

//funcao q coloca no arquivo um nodo da TRIE
streampos putInArqT(Trie trie) {
    int addressTrie;

    ofstream triePut("trie.bin", ios_base::binary | ios_base::app);

    if (!triePut) {                                   //arquivo nao foi criado/aberto
        return -1;
    }

    triePut.write((char*)&trie, sizeof(Trie));

    //cout << "colocando " << trie.pos << " no arquivo"; 

    addressTrie = triePut.tellp();
    addressTrie = addressTrie - sizeof(Trie);

    //cout << " na posicao " << addressTrie << endl;  
 
    triePut.close(); 
    return addressTrie; 

}

//funcao q le do arquivo um nodo da TRIE
Trie readInArqT(streampos pos) {
    Trie trie; 
    ifstream triePut("trie.bin", ios::binary);

    //vou ate o endereco desse nodo e leio
    triePut.seekg(pos); 
    triePut.read((char*)&trie, sizeof(Trie)); 

    triePut.close();
    return trie; 
}

int swapStructT(streampos posi, Trie trie){
    
    Trie trieAux; 
    trieAux = trie; 

    //cout << "fazendo o swap de " << trie.pos;

    ofstream trieSwap("trie.bin", ios::binary | ios::in);
        
    //move o ponteiro ate a posicao da string antiga 
    trieSwap.seekp(posi); 
    
   // cout << endl << "colocando " << trie.pos << " no arquivo na posicao " << posi << endl; 


    //escrevo nodo no arquivo nessa posicao
    trieSwap.write((char*)&trieAux, sizeof(Trie));        
    
    trieSwap.close();
    return 0; 
}



// Função iterativa para inserir uma chave em um Trie
void insertT(string key, streampos pos) {
    

    Trie rootTrie; 
    Trie auxTrie; 
    Trie currentTrie; 

    streampos auxPos; 
    streampos currentPos; 

    rootTrie = readInArqT(root); 

    currentTrie = rootTrie; 
    currentPos = root; 


    for (int i = 0; i < key.length(); i++) {

        if (currentTrie.character[key[i]] == -1) {

            //trie auxiliar serve para criar novo nodo
            //aux pos idem, sao so passageitos
            auxTrie = initT(); 
            auxPos = putInArqT(auxTrie); 
            currentTrie.character[key[i]] = auxPos;

            swapStructT(currentPos, currentTrie); 
        }
        currentPos = currentTrie.character[key[i]];
        currentTrie = readInArqT(currentPos); 
    }
 
    // marca o nodo atual como uma folha
    currentTrie.isLeaf = true; 
    currentTrie.pos = pos; 

    swapStructT(currentPos,currentTrie); 
}

// Função iterativa para pesquisar uma chave em um Trie. Ele retorna verdadeiro
// se a chave for encontrada no Trie; caso contrário, retorna falso
streampos searchT(string key) {
    //nao sei o que fazer com isso aq

    // retorna -1 se Trie estiver vazio
    if (root == -1) {
        return -1;
    }
 
    Trie rootTrie; 
    Trie auxTrie; 
    Trie currentTrie; 

    streampos auxPos; 
    streampos currentPos; 

    rootTrie = readInArqT(root); 

    currentTrie = rootTrie; 
    currentPos = root; 


    for (int i = 0; i < key.length(); i++) {
        // vai para o próximo nó

        currentPos = currentTrie.character[key[i]];
        currentTrie = readInArqT(currentPos);
        //cout << currentTrie.pos; 
        
         // se a string for inválida (alcançou o final de um caminho no Trie)
        if (currentPos == -1) {
            return -1;
        }
    }
    // retorna true se o nó atual for uma folha e o
    // fim da string é atingido
    return currentPos;
}
  
// Implementação C++ da estrutura de dados Trie
int criaTrie() {
    //root ja existe e esta definida la em cima

    Trie rootTrie = initT(); 
    root = putInArqT(rootTrie);

    Word wordAux; 

    ofstream testeTRIE("../debug/TRIE.txt");

    ifstream dic_binarya("../data/dictionary.bin", ios::binary);

    streampos posicaoTrie;
    string palavraTrie; 

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

        palavraTrie = wordAux.palavra; 
        posicaoTrie = enderecoInicio; 
        
        insertT(palavraTrie, posicaoTrie); 


        Trie auxPrint; 
        streampos auxPos = -1; 
        
        testeTRIE << palavraTrie << endl;
        auxPos = searchT(palavraTrie);
        //testeTRIE << auxPos; 
        auxPrint = readInArqT(auxPos); 
        testeTRIE << auxPrint.pos << endl << endl; 
    
    }

    testeTRIE.close();
    
    dic_binarya.close(); 
    return 0;


/*
    Trie auxPrint; 
    streampos auxPos = -1; 



    insertT("hello",2);

    auxPos = searchT("hello");
    cout << "o "; 
    //cout << auxPos; 
    auxPrint = readInArqT(auxPos); 
    cout << auxPrint.pos << " ";  

 
    insertT("helloworld",4);
    auxPos = searchT("helloworld");
    cout << "o "; 
    //cout << auxPos; 
    auxPrint = readInArqT(auxPos); 
    cout << auxPrint.pos << " ";  
 
 
    insertT("hell",5);
    auxPos = searchT("hell");
    cout << "o "; 
    //cout << auxPos;     
    auxPrint = readInArqT(auxPos); 
    cout << auxPrint.pos << " ";
 
    insertT("h",6);
    auxPos = searchT("h");
    cout << "o "; 
    //cout << auxPos;     
    auxPrint = readInArqT(auxPos); 
    cout << auxPrint.pos << " "; 
    cout << endl;
 */
 
    return 0;
}
