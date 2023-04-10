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
    int op;
    cout << "Qual classe gramatical você deseja visualizar?" << endl;
    cout << "1 - Substantivos\n2 - Verbos\n3 - Adjetivos" <<endl;
    cout << "Insira opção: ";
    cin >> op;
    writeList(op);
    return 0;
}

int writeList(int op){

    string classe;
    if (op == 1) classe = "substantivos";
    if (op == 2) classe = " Verbos";
    if (op == 3) classe = "Adjetivos";

    string nome_arquivo;
    string caminho = "../listados/";
    cout << "oi" << endl;
    cout << "Um arquivo txt vai ser criado listando todos os " << classe << " presentes em nosso banco de dados" << endl;
    cout << "Digite o nome do arquivo que deseja criar: ";
    //cin >> nome_arquivo;

    ofstream arquivo("teste.txt");

    if (arquivo.is_open()) {
        arquivo << "Este é um exemplo de arquivo de texto criado em C++." << endl;
        arquivo << "Mais uma linha de texto." << endl;
        arquivo.close();
        cout << "Arquivo criado com sucesso! Você pode encontra-lo na pasta >listados<" << endl;
    }
    else {
        cout << "Não foi possível criar o arquivo." << endl;
    }

    return 0;
}