#include "../include/bib.h"

using namespace std;

int newUserWord() {
    //printa perguntas aos usuarios
    //controi string com elas 
    //insere
    return 0; 
}

int includeWord(){
    cout << "Incluir" << endl;
    return 0;
}
int excludeWord(){
    cout << "excluir" << endl;
    return 0;
}
int listWords(){
    int op, op2;
    cout << "Qual classe gramatical você deseja visualizar?" << endl;
    cout << "1 - Substantivos\n2 - Verbos\n3 - Adjetivos\n4 - Preposições" <<endl;
    cout << "Insira opção: ";
    cin >> op;
    cout << "Voce deseja ver as palavras em qual ordem?" << endl;
    cout << "1 - Ordem alfabética\n2 - Ordem alfabética inversa" << endl;
    cout << "Insira opção: ";
    cin >> op2;
    if(op2 == 1) writeList(op);
    if(op2 == 2) writeListReverse(op);
    return 0;
}



//ESCREVE ARQUIVO EM ORDEM ALFABETICA-------------------------------------------------------------------------

int writeList(int op){

    string classe;
    if (op == 1) classe = "substantivos";
    if (op == 2) classe = "verbos";
    if (op == 3) classe = "adjetivos";
    if (op == 4) classe = "preposicoes";

    string nome_arquivo;

    cout << "Um arquivo txt vai ser criado listando em ordem alfabética todos os " << classe << " presentes em nosso banco de dados" << endl;
    cout << "Digite o nome do arquivo que deseja criar: ";
    cin >> nome_arquivo;

    ofstream arquivo("../listar/" + nome_arquivo + ".txt");

    string arqbin = "../invertidos/" + classe + ".bin";
    //cout << arqbin << endl;

    ifstream inverted_read(arqbin, ios::binary);

    Entry entryAux; 

    int ID; 
    //verifica se o arquivo abriu ou não 
    if (!inverted_read.is_open()) {
        cout << "deu ruim";
        return 1;  
    }

    string aux; 
    while(inverted_read.read((char*)&entryAux, sizeof(Entry))){
        //e aqui vou printar a struct pra mostrar que deu certo
        //arquivo << entryAux.ID << endl;
        aux = entryAux.entryWord.toString(); 
        arquivo << aux << endl;         
        //arquivo << entryAux.pos << endl << endl;
    }


    arquivo.close(); 
    
    if (!inverted_read.eof()) {
        cout << "Não foi possível ler todo o arquivo.\n";
        return 1;
    }

    inverted_read.close();


    return 0;
}

//LISTA EM ORDEM INVERSA-----------------------------------------------------------------------------------------------------------------

int writeListReverse(int op){

    string classe;
    if (op == 1) classe = "substantivos";
    if (op == 2) classe = "verbos";
    if (op == 3) classe = "adjetivos";
    if (op == 4) classe = "preposicoes";

    string nome_arquivo;

    cout << "Um arquivo txt vai ser criado listando em ordem inversa todos os " << classe << " presentes em nosso banco de dados" << endl;
    cout << "Digite o nome do arquivo que deseja criar: ";
    cin >> nome_arquivo;

    ofstream arquivo("../listar/" + nome_arquivo + ".txt");

    string arqbin = "../invertidos/" + classe + ".bin";
    //cout << arqbin << endl;

    ifstream inverted_read(arqbin, ios::binary);

    Entry entryAux; 

    int ID; 
    //verifica se o arquivo abriu ou não 
    if (!inverted_read.is_open()) {
        cout << "deu ruim";
        return 1;  
    }

    inverted_read.seekg(0, std::ios::end);
    int tamanho = inverted_read.tellg() / sizeof(Entry);

    vector<Entry> registros(tamanho);

    inverted_read.seekg(0, std::ios::beg);
    for (int i = 0; i < tamanho; i++) {
        inverted_read.read(reinterpret_cast<char*>(&registros[i]), sizeof(Entry));
    }
    string aux;

    for (auto it = registros.rbegin(); it != registros.rend(); ++it) {
        aux = entryAux.entryWord.toString();
        cout << aux << endl;
    }

    /*string aux; 
    while(inverted_read.read((char*)&entryAux, sizeof(Entry))){
        //e aqui vou printar a struct pra mostrar que deu certo
        //arquivo << entryAux.ID << endl;
        aux = entryAux.entryWord.toString(); 
        arquivo << aux << endl;         
        //arquivo << entryAux.pos << endl << endl;
    }*/


    arquivo.close(); 
    
    if (!inverted_read.eof()) {
        cout << "Não foi possível ler todo o arquivo.\n";
        return 1;
    }

    inverted_read.close();


    return 0;
}



/*
int main() {
    std::ifstream file("arquivo.bin", std::ios::binary | std::ios::ate);
    // Verifica se o arquivo foi aberto corretamente
    if (!file.is_open()) {
        std::cout << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }
    // Posiciona o ponteiro no final do arquivo
    file.seekg(0, std::ios::end);
    // Loop para ler o arquivo de trás para frente
    for (std::streampos i = file.tellg() - 1; i >= 0; i--) {
        // Move o ponteiro uma posição para trás
        file.seekg(i);
        // Lê um byte do arquivo
        char byte;
        file.read(&byte, 1);
        // Faça algo com o byte lido
        std::cout << byte;
    }
    file.close();
    return 0;
}
*/