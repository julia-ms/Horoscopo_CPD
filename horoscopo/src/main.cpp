// Bibliotecas
#include "../include/bib.h"


using namespace std;

// Declaração de função principal
//int main(int arqc, char* argv[]) {
  
int main(){  
  setlocale(LC_ALL, "Portuguese_Brasil");

//TESTANDO AQUI SE EU CONSIGO LER CORRETAMENTE ENDERECOS DO DICIONARIO 
  int fator; 
  tuple<int, int, int, int> tam;            //tamAdj, tamSub, tamVer, tamPrep; 
  tuple<streampos, streampos, streampos, streampos, string> posTuple;    //addressAdj, addressSub, addressVer, addressPrep;   

  //get<0>(tam) = generateInverted("adj.", "../invertidos/adjetivos.bin");
  //get<1>(tam) = generateInverted("s.", "../invertidos/substantivos.bin");
  //get<2>(tam) = generateInvertedVerb("../invertidos/verbos.bin");
  //get<3>(tam) = generateInverted("prep.", "../invertidos/preposicoes.bin");
  //readInverted("../invertidos/adjetivos.bin"); 
  //saveInt(get<0>(tam), get<1>(tam), get<2>(tam), get<3>(tam));

 
 
  //TODO O TRABALHO AQUI 

  //variaveis de controle de arquivos invertidos
  //fluxo do menu
  int modo = 0; 
  int newTry = 0; 
  int badTip = 0; 
  int stillBad = 0; 

  //structs auxiliares
  Entry auxPrint; 
  
  lerInteiros(get<0>(tam), get<1>(tam), get<2>(tam), get<3>(tam));


//lembrar do que eu precisar zerar
home: 
  do {
    system("cls"); 
    cout << "Bem-vindo(a) ao seu horoscopo. O que deseja fazer?" << endl;
    cout << "1 - Previsao do dia | 2 - Administrador" << endl << "Entre com a opção: "; 
    cin >> modo; 
  } while (modo != 1 && modo != 2); 

  if (modo == 1) {
  fator = horoscopo(); 

  switch (fator % 3) {
    case 0:
      posTuple = generateFrase(fator,0);
      break;

    case 1:
      posTuple = generateFrase(fator,1);
      break;

    case 2:
      posTuple = generateFrase(fator,2);
      break;

    default:
      break;
  }

  modo = 0; 
  sleep(10); 
  do {
    system("cls"); 
    cout << "Gostou do seu horoscopo?" << endl;
    cout << "1 - SIM | 2 - NÃO" << endl << "Entre com a opção: ";
    cin >> modo; 
  } while (modo != 1 && modo != 2); 
  
  if (modo == 1) {
    ofstream arquivo("../data/good.txt", std::ios::app);
    arquivo << get<4>(posTuple);
    arquivo << "\n"; 
    arquivo.close();
    cout << "Obrigada pelo feedback! Digite 1 para tentar novamente: "; 
    cin >> newTry; 
    if (newTry ==  1)
      goto home; 
    else 
      goto saida; 
  }
  else if (modo == 2) {
    system("cls"); 
    cout << "Por qual motivo você achou seu horóscopo ruim?" << endl;
    cout << "Se ha uma palavra que você achou ruim ou nao entendeu, digite 1. Se é outro motivo, digite outro numero." << endl;
    cout << "Entre com a opcão: "; 
    cin >> badTip;

    if(badTip != 1) {
      cout << "Certo. Obrigada pelo feedback! Mais sorte na proxima. Digite 1 para tentar novamente." << endl; 
      cin >> newTry; 
      if (newTry ==  1)
        goto home; 
      else 
        goto saida; 
    } 
    else if(badTip == 1) {
      
      //funcao pra ler do dicionario socorro
      Word word0, word1, word2, word3; 
      streampos pos0,pos1,pos2,pos3;

      //addressAdj, addressSub, addressVer, addressPrep;
      pos0 = findInverted(get<0>(posTuple), "../invertidos/adjetivos.bin").pos; 
      pos1 = findInverted(get<1>(posTuple), "../invertidos/substantivos.bin").pos; 
      pos2 = findInverted(get<2>(posTuple), "../invertidos/verbos.bin").pos; 
      pos3 = findInverted(get<3>(posTuple), "../invertidos/preposicoes.bin").pos; 

      word0 = searchWordAdress(pos0); 
      word1 = searchWordAdress(pos1); 
      word2 = searchWordAdress(pos2); 
      word3 = searchWordAdress(pos3); 

      cout << endl <<"Essas são as palavras usadas na sua frase: " << endl << endl; 

      cout << word0.palavra << ": " << word0.significado << endl; 
      cout << word1.palavra << ": " << word1.significado << endl; 
      cout << word2.palavra << ": " << word2.significado << endl; 
      cout << word3.palavra << ": " << word3.significado << endl << endl;
    
      cout << "Ainda acha o seu horóscopo ruim? Digite 1. Caso não, digite outro número" << endl; 
      cout << "Entre com a opção: ";
      cin >> stillBad; 

      if(stillBad != 1) {
        cout << "Certo. Obrigada pelo feedback! Mais sorte na proxima. Digite 1 para tentar novamente." << endl; 
        cin >> newTry; 
        if (newTry ==  1)
          goto home; 
        else 
          goto saida; 
      }


    }




  }

}



else if (modo == 2) {
  int op;
  cout << "Essa é a página do administrador. O que deseja fazer?\n1 - Incluir uma palvra nova\n2 - Excluir uma palvra existente\n3- Listar todas as palvras presentes no banco de daodos" << endl;
  cout << "Para sair aperte qualquer tecla." << endl;
  cout << "Insira opção: ";
  cin >> op;

  if(op == 1){
    includeWord();
  }else if(op == 2){
    excludeWord();
  }else if(op == 3){
    listWords();
  }else goto saida;
}



   


  
  //cout << tamAdj << "," << tamSub << "," << tamVer << "," << tamPrep; 

  saida:
  //saveInt(get<0>(tam), get<1>(tam), get<2>(tam), get<3>(tam));
  

  cout << "Fim do programa!";
  return 0;

}


//espaco para testar funcoes de busca e insersao direto no dicionario

