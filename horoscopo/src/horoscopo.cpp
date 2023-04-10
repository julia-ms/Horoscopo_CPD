#include "../include/bib.h"

using namespace std;

int generateRandom(int fator, int tam){
    //gera uma entrada aleatoria;     
    int random; 

    srand(time(NULL));
    
    int aleatorio; 
    aleatorio = rand(); 
    random = abs((fator*aleatorio) % tam-1);

    //ver aqui depois 
    random = random*sizeof(Entry); 

    return random;
}

int horoscopo() {
    string nome;
    int dia, mes, ano;

    cout << "Insira seu nome: ";
    cin >> nome;
    cout << "Insira sua data de nascimento (dd/mm/yyyy): ";
    cin >> dia;
    cin.ignore(); 
    cin >> mes;
    cin.ignore(); 
    cin >> ano;

    return dia*mes*ano; 
}

tuple<streampos, streampos, streampos, streampos, string> generateFrase(int fator, int op){
    //variaveis de controle de arquivos invertidos
    int tamAdj, tamSub, tamVer, tamPrep; 
    streampos addressAdj, addressSub, addressVer, addressPrep; 
    string tip = "";

    lerInteiros(tamAdj, tamSub, tamVer, tamPrep);

    //cout << tamAdj << "," << tamSub << "," << tamVer << "," << tamPrep;
    //ID -1 eh excluido

    do {
    addressAdj = generateRandom(fator, tamAdj-1); 
    } while (findInverted(addressAdj, "../invertidos/adjetivos.bin").ID == -1);
    
    do {
    addressSub = generateRandom(fator, tamSub-1); 
    } while (findInverted(addressSub, "../invertidos/substantivos.bin").ID == -1);
    
    do {
    addressVer = generateRandom(fator, tamVer-1); 
    } while (findInverted(addressVer, "../invertidos/verbos.bin").ID == -1);
    
    do {
    addressPrep = generateRandom(fator, tamPrep-1); 
    } while (findInverted(addressPrep, "../invertidos/preposicoes.bin").ID == -1);
    

    //cout << fator; 

    if (op == 0){
        tip += "\"Nao deixe de ";
        tip += findInverted(addressVer, "../invertidos/verbos.bin").entryWord.toString(); 
        tip += " "; 
        tip += findInverted(addressPrep, "../invertidos/preposicoes.bin").entryWord.toString();
        tip += " à "; 
        tip += findInverted(addressSub, "../invertidos/substantivos.bin").entryWord.toString(); 
        tip += " "; 
        tip += findInverted(addressAdj, "../invertidos/adjetivos.bin").entryWord.toString();
        tip += '\"'; 
    }

    if (op == 1) {
        tip += "\"É a hora para ";
        tip += findInverted(addressVer, "../invertidos/verbos.bin").entryWord.toString(); 
        tip += " "; 
        tip += findInverted(addressPrep, "../invertidos/preposicoes.bin").entryWord.toString();
        tip += " um(a) "; 
        tip += findInverted(addressSub, "../invertidos/substantivos.bin").entryWord.toString(); 
        tip += " "; 
        tip += findInverted(addressAdj, "../invertidos/adjetivos.bin").entryWord.toString();
        tip += '\"'; 
    }

    if (op == 2) {
        tip += "\"Emoções devem ";
        tip += findInverted(addressVer, "../invertidos/verbos.bin").entryWord.toString(); 
        tip += " "; 
        tip += findInverted(addressPrep, "../invertidos/preposicoes.bin").entryWord.toString();
        tip += " forte "; 
        tip += findInverted(addressSub, "../invertidos/substantivos.bin").entryWord.toString(); 
        tip += " "; 
        tip += findInverted(addressAdj, "../invertidos/adjetivos.bin").entryWord.toString();
        tip += '\"'; 

    }
    cout <<endl; 
    cout << tip << endl; 
    cout <<endl;

    return make_tuple(addressAdj, addressSub, addressVer, addressPrep, tip); 

}



