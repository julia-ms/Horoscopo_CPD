// Bibliotecas
#include "../include/bib.h"


using namespace std;

// Declaração de função principal
int main(int arqc, char* argv[]) {
  
//int main(){  
  //para funcionar em portugues corretamente, eh necessario digitar no terminal antes de rodar: chcp 65001
  setlocale(LC_ALL, "Portuguese_Brasil");

  
  string arq_data_is = argv[1];
  string arq_binary_is = argv[2];
  fillFile(arq_data_is, arq_binary_is);

  cout << "atualizou"; 

  readFile(arq_binary_is); 
  
  //invertido(); 
  /*
  ifstream arq_qtd("quantidade.bin", ios::binary);
  int qtd = 0; 
  int soma = 0; 
  while (arq_qtd.read((char*)&qtd, sizeof(int))){
    cout << qtd << endl; 
    soma += qtd;
  }
  cout << "soma eh " << soma; 
  arq_qtd.close(); */

  //string classe = "v.";

  //lerIndex(classe, 10753);  

/*
  int choice;
  volta:
  cout << "Insira 1 para ir para o horoscopo e 2 para ir para a parte administrativa: ";
  cin >> choice;
  if (choice == 1){ 
    horoscopo();
  }else{
    if(choice == 2){
      adm();
    }else{ 
        cout << "escolha invalida" << endl;
        goto volta;
      }
  }

  */ 

  return 0;
}