#include "../include/bib.h"

using namespace std;


//FUNCOES DE CRIACAO E LEITURA --------------------------------------------------------------------------------------------------
// funcao que abre o arquivo csv e coloca os itens em um arquivo binário com ID
int fillFile(string arq_data_is, string arq_binary_is){

    ifstream arq_data(arq_data_is);
    ofstream dic_binary(arq_binary_is, ios::binary);


    string line; 
    int IDAux; 
    Word wordAux; 

    //verifica se o arquivo abriu ou não 
    if (!arq_data.is_open() || !dic_binary.is_open()) {
        cout << "deu ruim";
        return 1;  
    }

    //le linha a linha e coloca em struct auxiliar 
    IDAux = 0; 
    while (getline(arq_data, line)) {

        //preencho struct palavra auxiliar 
        wordAux = construct(line, IDAux); 
        IDAux++;


        //coloco struct auxiliar no arquivo binario  
        //o + 1 é pra dar espaço para o terminador /0, já que os tamanhos das strings variam
        dic_binary.write((char*)&wordAux.ID, sizeof(int));
        dic_binary.write(wordAux.palavra.c_str(), wordAux.palavra.size() + 1);
        dic_binary.write(wordAux.classe.c_str(), wordAux.classe.size() + 1);
        dic_binary.write(wordAux.genero.c_str(), wordAux.genero.size() + 1);
        dic_binary.write(wordAux.numero.c_str(), wordAux.numero.size() + 1);
        dic_binary.write(wordAux.significado.c_str(), wordAux.significado.size() + 1);
        dic_binary.write((char*)&wordAux.deleted, sizeof(bool));

    }
    
    //fechamento de todos os arquivos abertos 
    arq_data.close();
    dic_binary.close();


    //escrevo o numero de entradas no inicio do arquivo
    //fstream dic_binary_entrys("../data/dictionary.bin", ios_base::binary | ios::in | ios::out);
    //dic_binary_entrys.seekp(0), ios::beg; 
    //dic_binary_entrys.write((char*)&IDAux, sizeof(int));
    //dic_binary_entrys.close(); 




    return 0; 
}

//funcao que abre o arquivo binario e le cada item printando no terminal
//pode ser usada na hora de procurar todos os itens de uma classe ou coisas assim....
int readFile(string arq_binary_is){
    ifstream dic_binary(arq_binary_is, ios::binary);

    Word wordAux; 

    int ID; 
    //verifica se o arquivo abriu ou não 
    if (!dic_binary.is_open()) {
        cout << "deu ruim";
        return 1;  
    }

    ofstream testePraga("../data/praga.txt");


    //lendo numero de entradas pra nao me atrapalhar
    //int numEntrys = 0; 
    //dic_binary.read((char*)&numEntrys, sizeof(int));

    while(dic_binary.read((char*)&wordAux.ID, sizeof(int))){
        getline(dic_binary, wordAux.palavra, '\0');
        getline(dic_binary, wordAux.classe, '\0');
        getline(dic_binary, wordAux.genero, '\0');
        getline(dic_binary, wordAux.numero, '\0');
        getline(dic_binary, wordAux.significado, '\0');  
        dic_binary.read((char*)&wordAux.deleted, sizeof(bool)); 


        //e aqui vou printar a struct pra mostrar que deu certo
        testePraga << "ID:" << wordAux.ID << endl; 
        testePraga << "palavra:" << wordAux.palavra << endl; 
        testePraga << "classe:"  << wordAux.classe  << endl;
        testePraga << "genero:"  << wordAux.genero  << endl;
        testePraga << "numero:"  << wordAux.numero  << endl;
        testePraga << "significado:" << wordAux.significado << endl;
        testePraga << "deleted:" << wordAux.deleted << endl << endl; 

    }

    testePraga.close(); 
    
    if (!dic_binary.eof()) {
        cout << "Não foi possível ler todo o arquivo.\n";
        return 1;
    }

    //cout << "numero de entradas eh: " << numEntrys; 
    //fechando arquivos
    dic_binary.close();
    return 0; 
}


//FUNCAO DE INSERCAO E EXCLUSAO ---------------------------------------------------------------------------------------------
//insere Word ao final e retorna o endereco de insercao
streampos insertWordFinal(Word word) {
    streampos addressWord; 
    int ID; 

    //leio o numero de entradas no inicio do arquivo e adiciono 1, colocando isso como ID
    //ifstream dic_binary_insert_entrys("../data/dictionary.bin", ios_base::binary);
    //dic_binary_insert_entrys.read((char*)&ID, sizeof(int));
    //dic_binary_insert_entrys.close(); 
    //ID++;

    //updateNumEntrys(ID);


    //atualizo o ID da palavra a ser inserida
    word.ID = ID; 

    ofstream dic_binary_insert("../data/dictionary.bin", ios_base::binary | ios_base::app);

    if (!dic_binary_insert) {                                  
        return -1;
    }                
    dic_binary_insert.write((char*)&word, sizeof(Word));

    int ba;
    addressWord = dic_binary_insert.tellp();
    ba = addressWord; 

    //addressWord = addressWord - sizeof(Word);
    ba = ba - sizeof(Word);
    dic_binary_insert.close(); 

    addressWord = ba; 
    return addressWord;                              
}
/*
void deleteWord (string classe, int id) {
    Word auxWord; 
    streampos pos; 

    pos = lerIndex(classe, id); 
    // busca palavra no invertido, que retorna endereco

    auxWord = searchWordAdress(pos); 
    auxWord.deleted = true; 

    updateWord(pos, auxWord); 
}
*/
int updateNumEntrys(int actualID) {
    Word wordAux; 

    ofstream update_entrys("../data/dictionary.bin", ios::binary | ios::in);
     
    if (!update_entrys) {
        return -1; 
    }

    update_entrys.seekp(0); 

    //escrevo novo tamanho
    update_entrys.write((char*)&actualID, sizeof(int));        
    update_entrys.close();

    return 0; 
}

int updateWord (streampos pos, Word updated) {
    Word wordAux; 
    wordAux = updated; 

    ofstream dic_binary_update("../data/dictionary.bin", ios::binary | ios::in);
     
    if (!dic_binary_update) {
        return -1; 
    }

    //move o ponteiro ate a posicao da string antiga 
    dic_binary_update.seekp(pos); 

    //escrevo nodo no arquivo nessa posicao
    dic_binary_update.write((char*)&wordAux, sizeof(Word));        
    
    dic_binary_update.close();
    return 0; 
}    


//FUNCAO DE CRIACAO DE WORD -------------------------------------------------------------------------------------------------
//funcao que recebe uma string adequada e transforma em struct palavra
Word construct(string line, int IDAux) {
     
    Word wordAux; 
    string stringAux; 
    int i = 0;

    wordAux.ID = IDAux; 
    if (i < line.length()){
        while (line[i] != ';') {
            stringAux += line[i]; 
            i++; 
        }
        i++; 
        wordAux.palavra = stringAux; 
        stringAux = "";

        while (line[i] != ';') {
            stringAux += line[i]; 
            i++; 
        }
        i++; 
        wordAux.classe = stringAux; 
        stringAux = "";

        while (line[i] != ';') {
            stringAux += line[i]; 
            i++; 
        }
        i++; 
        wordAux.genero = stringAux; 
        stringAux = "";
        while (line[i] != ';') {
            stringAux += line[i]; 
            i++; 
        }
        i++; 
        wordAux.numero = stringAux; 
        stringAux = "";

        while (i < line.length()) {
            stringAux += line[i]; 
            i++; 
        }
        i++; 
        wordAux.significado = stringAux; 
        stringAux = "";
    }
    wordAux.deleted = 0; 
    return wordAux; 
}



Word doUserWord() {
    Word userWord; 
    string palavra, classe, genero, numero, significado;

    cout << "Insira a palavra: "; 
    cin >> palavra;  
    cout << "Insira a classe: "; 
    cin >> classe;  
    cout << "Insira o genero: "; 
    cin >> genero;  
    cout << "Insira o numero: "; 
    cin >> numero;  
    cout << "Insira o significado: "; 
    cin >> significado;  

    userWord.palavra = palavra; 
    userWord.classe = classe; 
    userWord.genero = genero; 
    userWord.numero = numero; 
    userWord.significado = significado; 

    return userWord; 
}




//FUNCOES PARA PESQUISA ------------------------------------------------------------------------------------------------------------

//pesquiso palavra no arquivo por ID. se nao encontra esse ID, retorna erro
Word searchWordID(int id) {
    Word wordAux; 
    Word wordError; 
    int idAux = -1; 
    wordError.ID = -1; 
    
    //le o numero de entradas no inicio pra nao atrapalhar 

    
    ifstream dic_binary_searchID("../data/dictionary.bin", ios::binary);


    //int numEntrys = 0; 
    //dic_binary_searchID.read((char*)&numEntrys, sizeof(int));

    while (dic_binary_searchID.read((char*)&wordAux, sizeof(Word))){
        idAux = wordAux.ID; 
        if (idAux == id) 
            break; 
    }    

    dic_binary_searchID.close(); 

    if (idAux == id) {
        return wordAux; 
    }
    else return wordError; 
}

//pega uma struct palavra pelo seu endereco
Word searchWordAdress(streampos pos) {
    Word wordAux; 
    
    ifstream dic_binary_searchAdress("../data/dictionary.bin", ios::binary);

    //aq nao pega certo
    dic_binary_searchAdress.seekg(pos); 

    dic_binary_searchAdress.read((char*)&wordAux.ID, sizeof(int));
    getline(dic_binary_searchAdress, wordAux.palavra, '\0');
    getline(dic_binary_searchAdress, wordAux.classe, '\0');
    getline(dic_binary_searchAdress, wordAux.genero, '\0');
    getline(dic_binary_searchAdress, wordAux.numero, '\0');
    getline(dic_binary_searchAdress, wordAux.significado, '\0');  
    dic_binary_searchAdress.read((char*)&wordAux.deleted, sizeof(bool)); 

/*
    cout << "procurando pela palavra, encontrei"; 
    cout << "ID = " << wordAux.ID; 
    cout << "palavra = "; 
    cout << wordAux.palavra << endl; 
    cout << "classe = "; 
    cout << wordAux.classe << endl; 
    cout << "genero = "; 
    cout << wordAux.genero << endl;
    cout << "numero = "; 
    cout << wordAux.numero << endl;
    cout << "significado = "; 
    cout << wordAux.significado << endl;
*/
    //dic_binary_searchAdress.read((char*)&wordAux, sizeof(Word)); 
    dic_binary_searchAdress.close(); 

    return wordAux; 
}


//pesquiso palavra no arquivo por palavra. se nao encontra essa palavra, retorna erro
Word searchWord(string word) {
    //essa tem erro de tamanho
    Word wordAux; 
    Word wordError; 
    string strAux = ""; 
    wordError.ID = -1; 
    
    //leio o primeiro int pra nao atrapalhar
    ifstream dic_binary_search("../data/dictionary.bin", ios::binary);
    //int numEntrys = 0; 
    //dic_binary_search.read((char*)&numEntrys, sizeof(int));

    while (dic_binary_search.read((char*)&wordAux, sizeof(Word))){
        strAux = wordAux.palavra; 
        if (strAux == word) 
            break; 
    }    

    dic_binary_search.close(); 

    if (strAux == word) {
        return wordAux; 
    }
    else return wordError; 
}


//GUARDA TAMANHOS  ------------------------------------------------------------------------------------------------------------

void saveInt(int a, int b, int c, int d) {
  // criar um objeto de fluxo de saída para o arquivo
  std::ofstream arquivo("../data/int.bin", std::ios::binary);

  // escrever os 4 inteiros no arquivo
  arquivo.write((char*)&a, sizeof(int));
  arquivo.write((char*)&b, sizeof(int));
  arquivo.write((char*)&c, sizeof(int));
  arquivo.write((char*)&d, sizeof(int));

  // fechar o arquivo
  arquivo.close();
}

void lerInteiros(int& a, int& b, int& c, int& d) {
  // criar um objeto de fluxo de entrada para o arquivo
  std::ifstream arquivoLeitura("../data/int.bin", std::ios::binary);

  // ler os 4 inteiros do arquivo
  arquivoLeitura.read((char*)&a, sizeof(int));
  arquivoLeitura.read((char*)&b, sizeof(int));
  arquivoLeitura.read((char*)&c, sizeof(int));
  arquivoLeitura.read((char*)&d, sizeof(int));

  // fechar o arquivo
  arquivoLeitura.close();
}

