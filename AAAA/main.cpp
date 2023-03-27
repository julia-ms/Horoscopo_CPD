// Bibliotecas
#include "bib.h"


using namespace std;

// Declaração de função principal
int main(int arqc, char* argv[]) {
  //para funcionar em portugues corretamente, eh necessario digitar no terminal antes de rodar: chcp 65001
  setlocale(LC_ALL, "Portuguese_Brasil");

  string arq_data_is = argv[1];
  string arq_binary_is = argv[2];



  fillFile(arq_data_is, arq_binary_is);
  readFile(arq_binary_is); 
  return 0;
}