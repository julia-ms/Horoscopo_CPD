// Bibliotecas
#include "bib.h"


using namespace std;

// Declaração de função principal
int main(int arqc, char* argv[]) {
  //para funcionar em portugues corretamente, eh necessario digitar no terminal antes de rodar: chcp 65001
  setlocale(LC_ALL, "Portuguese_Brasil");

  string arq_data_is = argv[1];
  string arq_binary_is = argv[2];

  cout << arq_data_is;
  cout << arq_binary_is; 

  fillArchive(arq_data_is, arq_binary_is);
  readArchive(arq_binary_is); 
  return 0;
}