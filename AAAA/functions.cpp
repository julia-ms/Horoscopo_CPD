#include "bib.h"

using namespace std;

/*PASSOS
- ler o arquivo de texto 
- colocar cada linha em uma struct palavra
- printar essa struct palavra pra ver se ta okay
- guardar a struct palavra no arquivo binário
- depois reler a struct do arquivo binário
- printar essa struct lida de novo
*/
/*DUVIDAS
- o arquivo de índice aponta o ID de onde está a palavra que eu quero, mas..
    - sabendo o ID, eu preciso procurar a palavra no arquivo de dados original
        -> como? por busca binária?
    - e quando eu quiser, por exemplo, um SUBSTANTIVO FEMININO, eu procuro nos dois arquivos invertidos? 
*/

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
    }
    
    //fechamento de todos os arquivos abertos 
    arq_data.close();
    dic_binary.close();
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

    while(dic_binary.read((char*)&wordAux.ID, sizeof(int))){
        getline(dic_binary, wordAux.palavra, '\0');
        getline(dic_binary, wordAux.classe, '\0');
        getline(dic_binary, wordAux.genero, '\0');
        getline(dic_binary, wordAux.numero, '\0');
        getline(dic_binary, wordAux.significado, '\0');     

        /*//e aqui vou printar a struct pra mostrar que deu certo
        cout << "ID:" << wordAux.ID << endl; 
        cout << "palavra:" << wordAux.palavra << endl; 
        cout << "classe:"  << wordAux.classe  << endl;
        cout << "genero:"  << wordAux.genero  << endl;
        cout << "numero:"  << wordAux.numero  << endl;
        cout << "significado:" << wordAux.significado << endl <<endl;*/
    }
    
    if (!dic_binary.eof()) {
        cout << "Não foi possível ler todo o arquivo.\n";
        return 1;
    }

    //fechando arquivos
    dic_binary.close();
    return 0; 
}

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
    return wordAux; 
}
