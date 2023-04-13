#include "../include/bib.h"

using namespace std;

Word newUserWord() {
    Word newWord;
    string palavra;
    string genero;
    string numero;
    string significado;

    int ID = 0; 

    cout << "Qual palavra você deseja incluir? Preencha as informações: " << endl;
    
    getchar(); 
    cout << "Palavra: "; 
    getline(cin, palavra);
    cout << endl; 
    
    cout << "Genero: "; 
    //getchar(); 
    getline(cin, genero);
    cout << endl; 
    
    cout << "Numero: "; 
    //getchar(); 
    getline(cin, numero);
    cout << endl; 
    
    //getchar(); 
    cout << "Significado: "; 
    getline(cin, significado);
    cout << endl; 


    newWord.palavra = palavra; 
    newWord.genero = genero; 
    newWord.numero = numero; 
    newWord.significado = significado; 
    newWord.deleted = false;

    ID = readNumEntry() + 1; 
    newWord.ID = ID;
    updateNumEntrys(ID);
    
    return newWord; 
}

int includeWord(){
    Word word;
    streampos posicao; 
    Entry newEntry; 
    int classe; 

    cout << "Você escolheu incluir palavra." << endl;
    cout << "A qual classe ela pertence?" << endl; 
    cout << "1 - Adjetivo" << endl; 
    cout << "2 - Substantivo" << endl; 
    cout << "3 - Verbo" << endl; 
    cout << "4 - Preposição" << endl; 
    cout << "Insira a opçao: "; 
    cin >> classe; 
    cout << endl << endl; 

    word = newUserWord(); 
    posicao = insertWordFinal(word); 

    newEntry.entryWord.fromString(word.palavra); 
    newEntry.ID = word.ID;
    newEntry.pos = posicao; 

    switch (classe) {
    case 1:
        word.classe = "adj."; 
        insertInverted(newEntry, "../invertidos/adjetivos.bin"); 

        break;
    case 2 :
        word.classe = "s."; 
        insertInverted(newEntry, "../invertidos/substantivos.bin"); 

        break;
    case 3 :
        word.classe = "v."; 
        insertInverted(newEntry, "../invertidos/verbos.bin"); 

        break;
    case 4 :
        word.classe = "prep."; 
        insertInverted(newEntry, "../invertidos/preposicoes.bin"); 

        break;
    
    default:
        break;
    }

    cout << "Arquivo inserido com sucesso! Agora tenho: " << readNumEntry() << "registros."; 

    return 0;
}


int excludeWord(){
    string wordToDelete; 
    int classe; 
    streampos posDelete; 
    Entry auxEntry; 

    //streampos posInverted, string name_Arq

    //1 - pede a palavra para o usuário  
    cout << "Qual palavra você deseja deletar?" << endl;
    getchar();
    getline(cin, wordToDelete);

    cout <<wordToDelete; 

    cout << "A qual classe ela pertence?" << endl; 
    cout << "1 - Adjetivo" << endl; 
    cout << "2 - Substantivo" << endl; 
    cout << "3 - Verbo" << endl; 
    cout << "4 - Preposição" << endl; 
    cout << "Insira a opçao: "; 
    cin >> classe; 
    cout << classe; 
    cout << endl << endl; 

    switch (classe){
    case 1:
        posDelete = binarySearchPos("../invertidos/adjetivos.bin", wordToDelete);
        auxEntry = findInverted(posDelete, "../invertidos/adjetivos.bin"); 

        if(auxEntry.entryWord.compareW(wordToDelete) == 0) {
            deleteWord(posDelete, "../invertidos/adjetivos.bin"); 
            cout << "Palavra " << wordToDelete << " deletada com sucesso!" << endl;
        } 
        break;

    case 2:
        posDelete = binarySearchPos("../invertidos/substantivos.bin", wordToDelete); 
        auxEntry = findInverted(posDelete, "../invertidos/substantivos.bin"); 

        cout << posDelete; 
        auxEntry.entryWord.wPrint();
        cout << "funfou"; 

        if(auxEntry.entryWord.compareW(wordToDelete) == 0) {
            deleteWord(posDelete, "../invertidos/substantivos.bin"); 
            cout << "Palavra " << wordToDelete << " deletada com sucesso!" << endl;
        } 
        break;

    case 3:
        posDelete = binarySearchPos("../invertidos/verbos.bin", wordToDelete);
        auxEntry = findInverted(posDelete, "../invertidos/verbos.bin"); 

        if(auxEntry.entryWord.compareW(wordToDelete) == 0) {
            deleteWord(posDelete, "../invertidos/verbos.bin"); 
            cout << "Palavra " << wordToDelete << " deletada com sucesso!" << endl;
        } 

        break; 
    case 4: 
        posDelete = binarySearchPos("../invertidos/preposicoes.bin", wordToDelete); 
        auxEntry = findInverted(posDelete, "../invertidos/preposicoes.bin"); 
       
        if(auxEntry.entryWord.compareW(wordToDelete) == 0) {
            deleteWord(posDelete, "../invertidos/preposicoes.bin"); 
            cout << "Palavra " << wordToDelete << " deletada com sucesso!" << endl;
        } 
        break; 
    
    default:
        break;
    }
    
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

    cout << "Arquivo gerado com sucesso!" << endl; 
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

    ifstream file(arqbin, ios::binary);

    Entry entryAux; 

    int ID; 
    //verifica se o arquivo abriu ou não 
    if (!file.is_open()) {
        cout << "deu ruim";
        return 1;  
    }

    // Obtenha o tamanho do arquivo em bytes.
    file.seekg(0, std::ios::end);
    std::streampos size = file.tellg();

    // Calcule o número de registros no arquivo.
    std::size_t num_records = size / sizeof(Entry);

    // Posicione o ponteiro de leitura/gravação no final do arquivo.
    file.seekg(-static_cast<std::streamoff>(sizeof(Entry)), std::ios::end);

    // Leia os registros do final para o início.
    for (std::size_t i = num_records; i > 0; --i) {
        Entry entry;

        std::streampos posic = static_cast<std::streampos>(i-1) * sizeof(Entry);
        file.seekg(posic);

        file.read(reinterpret_cast<char*>(&entry), sizeof(Entry));

        string palavra;
        palavra = entry.entryWord.toString();

        arquivo << palavra << endl;
    }

    arquivo.close(); 

    file.close();


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
