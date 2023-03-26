#include "bib.h"

using namespace std;


int teste(){
    cout << "oi" << endl;
    return 1; 
}

// funcao que abre o arquivo 
// cria arquivo binário
// coloca os dados no arquivo binário, com um ID antes 

int fillArchive(){

    string linha; 
    ifstream arq_data("reduced.csv");
    ofstream dic_binary("dictionary.bin", ios::binary);

    if (!arq_data.is_open()) {
        cout << "deu ruim";
        return 0;  
    }

    if (dic_binary.is_open()) {
        for(int i = 0; i <100; i++){

            getline(arq_data, linha);
            dic_binary.write(linha.c_str(), linha.size());        
        }
    }
    else {
        cout << "deu ruim de novo"; 
    }

    arq_data.close();
    dic_binary.close();
    return 1; 
}

int readArchive(){
    ifstream arq_bin("dictionary.bin", ios::binary); 

    if (!arq_bin.is_open()) {
        return 0; 
    }
    string linha; 
    while (getline(arq_bin, linha)) {
        cout << linha << std::endl;
    }
    arq_bin.close();
    return 1; 
}
