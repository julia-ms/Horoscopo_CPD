#include "bib.h"

using namespace std;

int invertido() {


    int linha_desejada = 5;
    int linha_atual = 1;

    char classe[50];
    int id;

    for(int i=0;i<5;i++){

        ifstream arquivo_original("arqinvertido.csv");
        ofstream arquivo_temporario("temp.csv");

        cin >> classe;
        cin >> id;

        if(strcmp(classe, "sub")==0) linha_desejada = 1;
        if(strcmp(classe, "ver")==0) linha_desejada = 2;


        // copia as primeiras linhas até a linha desejada
        string linha;
        while (getline(arquivo_original, linha)) {
            if (linha_atual == linha_desejada) {
                // escreve a nova linha no arquivo temporário
                arquivo_temporario << linha << ";" << id << endl;
                break;
            }
            arquivo_temporario << linha << endl;
            linha_atual++;
        }

        // copia o restante das linhas
        while (getline(arquivo_original, linha)) {
            arquivo_temporario << linha << endl;
        }

        arquivo_original.close();
        arquivo_temporario.close();

        // renomeia o arquivo temporário para o nome original do arquivo CSV
        remove("arqinvertido.csv");
        rename("temp.csv", "arqinvertido.csv");
    }


    /*// file pointer
    fstream arq;
  
    // opens an existing csv file or creates a new file.
    arq.open("arqinvertido.csv", ios::out | ios::app);
*/
/*
    char ala[50];
    Word auxWord;

    cout << "oiiii" << endl;
    cin >> ala;
    for(int i=0;i<5;i++){
        if(strcmp(ala, "oi")==0) arq << "vamo caralho" << endl;
        else arq << "f :(" << ala << endl;
    }*/
    return 0;
}

/*
if (strcmp(favoriteDairyProduct, "cheese") == 0)
{
struct Word {
    int ID; 
    string palavra; 
    string classe;
    string genero;
    string numero;  
    string significado; 
}; 

ler word.classe
se for substantivo -> linha 1, contador incrementa

//escrever na linha que quer: 
 ifstream arquivo_original("arquivo.csv");
    ofstream arquivo_temporario("temp.csv");

    int linha_desejada = 3;
    int linha_atual = 1;

    // copia as primeiras linhas até a linha desejada
    string linha;
    while (getline(arquivo_original, linha)) {
        if (linha_atual == linha_desejada) {
            // escreve a nova linha no arquivo temporário
            arquivo_temporario << "nova linha a ser escrita na linha desejada" << endl;
            break;
        }
        arquivo_temporario << linha << endl;
        linha_atual++;
    }

    // copia o restante das linhas
    while (getline(arquivo_original, linha)) {
        arquivo_temporario << linha << endl;
    }

    arquivo_original.close();
    arquivo_temporario.close();

    // renomeia o arquivo temporário para o nome original do arquivo CSV
    remove("arquivo.csv");
    rename("temp.csv", "arquivo.csv");


#include <iostream>
#include <fstream>
#include <cstring>
#include <locale>

using namespace std; 

int main(int arqc, char* argv[]) {
    switch (classe)
    {
    case 'adj':
     
        break;
    case 'adj.,num.':
      
        break;
    case 'adj.,num.,frac.,s.':
        
        break;
    case 'adj.,num.,mult.':
       
        break;
    case 'adj.,num.,ord.,s.':
        
        break;
    case 'adj.,pron.,adv.':
        
        break;
    case 'adj.,s.':
        
        break;
    case 'adv.':
        
        break;
    case 'adv.,interr.':
      
        break;
    case 'adv.,s.':
        
        break;
    case 'al.,abrev.':
      
        break;
    case 'art.,def.':
        
        break;
    case 'conj.':
       
        break;
    case 'conj.,concess.':
        
        break;
    case 'conj.,coord.':
        
        break;
    case 'conj.,disj.':
       
        break;
    case 'contr.':
       
        break;
    case 'det.,pron.,dem.':
        
        break;
    case 'det.,pron.,indef.':
       
        break;
    case 'det.,pron.,poss.':
        
        break;
    case 'ex.,abrev.':
        
        break;
    case 'interj.':
       
        break;
    case 'interj.,s.':
        
        break;
    case 'm.,abrev.':
        
        break;
    case 'pref.':
        
        break;
    case 'prep.':
       
        break;
    case 'pron.':
       
        break;
    case 'pron.,dem.':
        
        break;
    case 'pron.,indef.':
        
        break;
    case 'pron.,indef.,s.':
        
        break;
    case 'pron.,interr.':
        
        break;
    case 'pron.,pess.':
        
        break;
    case 'pron.,poss.':
        
        break;
    case 'pron.,rel.':
       
        break;
    case 's.':
        
        break;
    case 'sigla':
        
        break;
    case 'símb.':
        
        break;
    case 'suf.':
        
        break;
    case 'v.':
        
        break;
    case 'v.,cop.':
        
        break;
    case 'v.,intr.':
        
        break;
    case 'v.,intr.,pron.':
        
        break;
    case 'v.,pron.':
       
        break;
    case 'v.,s.':
       
        break;
    case 'v.,tr.':
        
        break;
    case 'v.,tr.,,intr.,pron.':
       
        break;
    case 'v.,tr.,intr.':
        
        break;
    case 'v.,tr.,pron.':
        
        break;
    default:
        break;
    }
    
    
    cout << "oi" << endl;
    return 0;
}

*/