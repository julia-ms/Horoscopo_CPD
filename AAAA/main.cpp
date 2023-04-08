// Bibliotecas
#include "bib.h"


using namespace std;

// Declaração de função principal
int main(int arqc, char* argv[]) {
  //para funcionar em portugues corretamente, eh necessario digitar no terminal antes de rodar: chcp 65001
  setlocale(LC_ALL, "Portuguese_Brasil");

  string arq_data_is = argv[1];
  string arq_binary_is = argv[2];

  //ter a opçao carregar dados novos ou dados já sao existentes! 
  //alguma lógica pra controlar isso e ter permanencia de dados

  fillFile(arq_data_is, arq_binary_is);
  readFile(arq_binary_is); 
  invertido();
  return 0;
}