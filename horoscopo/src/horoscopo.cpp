#include "../include/bib.h"

using namespace std;

int generateRandom(int dia, int mes, int ano, string classe){
    

    int random; 
    int tam; 

    tam = getSize (classe); 

    srand(time(NULL));

    
    int aleatorio; 
    aleatorio = rand(); 
    random = (dia*mes*ano*aleatorio) % tam; 
    return random;
}

int getSize(string classe) {

}

int horoscopo() {
    string nome;
    int dia, mes, ano;

    cout << "insira seu nome: ";
    cin >> nome;
    cout << "insira sua data de nascimento (dd/mm/yyyy): ";
    cin >> dia;
    cin.ignore(); 
    cin >> mes;
    cin.ignore(); 
    cin >> ano;

    generateRandom(dia, mes, ano); 


}





