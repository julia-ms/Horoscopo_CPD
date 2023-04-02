#include "../include/bib.h"

using namespace std;


//comecando com enderecos vazios pra nodos 
streampos r = -1;              //raiz 
streampos np = -1;             //node pointer
streampos auxx = -1;           //auxiliar x


//r eh raiz, np eh novo nodo e x eh um generico q vou usar
//funcao que cria/inicia nodo
Node init() {
    Node node;

    for (int i = 0; i < t; i++){
        node.keys[i].ID = 0;  
        node.keys[i].word.clear();
        node.keys[i].address = -1;   
    }

    //inicializando filhos em 1 
    for (int i = 0; i < t+1; i++){
        node.children[i] = -1 ;    
    }
    
    node.parent = 0;                     // Definindo a posição do pai como 0
    node.isLeaf = true;                 // Indicando que o nó não é folha
    node.numChildren = 0; 
    return node; 
}

//funcao que coloca nodo no fim do arquivo e retorna endereço 
streampos putInArq(Node node) {
    streampos addressNode; 

    ofstream BTreePut("Btree.bin", ios::binary | ios::app);

    if (!BTreePut) {                                   //arquivo nao foi criado/aberto
        return 1;
    }

    BTreePut.write((char*)&node, sizeof(Node));
    addressNode = BTreePut.tellp();                     

    BTreePut.close(); 
    return addressNode;                              // retorno a posicao do arquivo onde ta o nodo
}


//recebe uma posicao e retorna o nodo que ta la 
Node readInArq (streampos pos) {
    Node node; 
    ifstream BTreeRead("Btree.bin", ios::binary);

    //vou ate o endereco desse nodo e leio
    BTreeRead.seekg(pos); 
    BTreeRead.read((char*)&node, sizeof(Node)); 

    BTreeRead.close();
    return node; 
}

//vai ate uma posicao e coloca lá a struct recebida
int swapStruct(streampos pos, Node node){
    ofstream BTreeSwap("Btree.bin", ios::binary);
        
    //move o ponteiro ate a posicao da string antiga 
    BTreeSwap.seekp(pos); 

    //escrevo nodo no arquivo nessa posicao
    BTreeSwap.write((char*)&node, sizeof(Node));        
    
    BTreeSwap.close();
    return 0; 
}


//traverse the tree
void traverse(streampos p) {
    Node node; 
    node = readInArq(p); 
   
    int i;
    for (i = 0; i < node.numChildren; i++) {          // enquanto i for menor que o numero de filhos
        if (node.isLeaf == false) {              // se o nodo nao eh folha, ou seja, se nao acabou e ainda tem filhos   
            traverse(node.children[i]);    // vou recursivamente entrar no nodo filho e repetir isso, ate chegar no ultimo filho
        }
        node.keys[i].word.wPrint(); 
        cout <<endl;
    }

    if (node.isLeaf == false) {                  // faco isso de novo, nao sei pq, talvez seja pro pai e o do lado tb aparecerem
        traverse(node.children[i]);
    }
    cout<<endl;
    //cout << "erro"; 
}


//sort the tree 

// ordena as keys em ordem crescente ALFABETICA dentro do nodo
// recebe o array de keys e a quantidade de keys 
void sort(Key *keys, int numKeys) {               
    int i, j;                                   
   
    string si;                            // aqui pode ser um ponto que eu terei de alterar se tiver q usar array de char ao inves de str  
    string sj;  
    Key auxKey;  

    for (i = 0; i < numKeys; i++) {
        for (j = i; j <= numKeys; j++) {


            si = keys[i].word.toString(); 
            sj = keys[j].word.toString(); 

            if ((si.compare(sj)) > 0) {
                auxKey = keys[i];
                keys[i] = keys[j];
                keys[j] = auxKey;
            }
        }
    }
}



//recebo um endereco pro nodo x que ta em arquivo e um int i 
//suponho q int i na verdade seja uma Key newKey

// CONFERIR SE botei de volta TODOS OS NODOS ALTERADOS. PARA A MUDANÇA FICAR SALVA 
Key split_child(streampos x, int i) {                   // recebo o ponteiro para um nodo e um int i talvez faça sentido receber um ponteiro, já que to lidando com arquivos 
    int j;                                              // j eh um contador
    
    Key mid; 

    streampos np1, np3, y;                           // aqui tenho 3 enderecos para nodos, talvez pq sejam 6 keys (mas e pra lidar com t maiores? possivelmente array)
    Node nodep1, nodep3, nodeY, nodeX;                  // aqui tenhos os 3 nodos auxiliares
    
    nodep3 = init();                                       
    nodep3.isLeaf = true;                                       

    //tenho aqui o nodo do endereco que mandaram
    nodeX = readInArq(x); 

    //acho q esse -1 eh pra quando ta no inicio do arquivo
    if (i == -1) {                                           
        mid = nodeX.keys[2];                            // novamente tenho q lembrar q isso vale pra 6 chaves, e nao pra 250 como teremos depois
                                                        // encontro meio assim pois eh a key do meio [0,1, 2 ,3,4,5] ja q eh de ordem 6 (sao 6 keys)
        //zero o q estava no meio                                              
        nodeX.keys[2].ID = 0;
        nodeX.keys[2].word.clear();
        nodeX.keys[2].address = -1; 

        nodeX.numChildren = nodeX.numChildren--;        // zerei um, ja diminuo o numero de filhos

        nodep1 = init();                                // agora criei o nodo 1
        nodep1.isLeaf = false;                          // ele nao eh folha

        nodeX.isLeaf = true; 
                
        for (j = 3; j < 6; j++) {                       // agora do meio ao fim, parece q aqui ocorrem trocas importantes
            nodep3.keys[j-3] = nodeX.keys[j];           // as keys 0, 1, 2 de um novo nodo serao as 1,2,3 do antigo
            nodep3.children[j - 3] = nodeX.children[j]; // os filhos 0, 1, 2 do novo nodo serao 1,2,3 do antigo
            nodep3.numChildren = nodep3.numChildren+1;  // vou atualizar o numero de filhos

            nodeX.keys[j].ID = 0;                       // e cada vez que eu tiro uma key, eu zero/apago do antigo
            nodeX.keys[j].word.clear();
            nodeX.keys[j].address = -1; 
            nodeX.numChildren = nodeX.numChildren-1; 
        }
            
        for (j = 0; j <= 6; j++) {       
            nodeX.children[j] = -1;                   // quando acabar isso, o antigo nao tera nenhum filho (desceu)
        }

        nodep1.keys[0] = mid;                           // ja a primeira key de np1 sera o meio
        nodep1.children[nodep1.numChildren] = x;        // x sera adicionado ao fim dos filhos de np1

        np3 = putInArq(nodep3); 

        nodep1.children[nodep1.numChildren + 1] = np3;  // np3 sera adicionado ao fim tambem (note que eh o endereço no documento)
        nodep1.numChildren = nodep1.numChildren + 1;    // o numero de filhos de np1 aumenta em 1
        
        //coloco nodop1 onde estava r               
        //tem q ver se a raiz ta mesmo no lugar
        //eh o mesmo q falar q o endereco r agora e o endereco de p1. 
        swapStruct(r, nodep1);

        //atualizo node x   
        swapStruct(x, nodeX); 
    } 

    else {
        y = nodeX.children[i];                          // y recebe o endereco de um dos filhos q eu recebi
        nodeY = readInArq(y); 

        mid = nodeY.keys[2];                            // de novo, isso funciona pq sao 6 dados. aqui mid eh o do meio. se eu tiver mais, como vou ter, muda  


        nodeY.keys[2].ID = 0;                           // e cada vez que eu tiro uma key, eu zero/apago do antigo
        nodeY.keys[2].word.clear();
        nodeY.keys[2].address = -1;
        nodeY.numChildren = nodeY.numChildren-1;        // diminui o nro de filhos

        for (j = 3; j <6 ; j++) {                       // aqui lembrar de mudar tb pra quando tiver mais itens 

            nodep3.keys[j-3] = nodeY.keys[j];           // mesma coisa de antes, de encher np3 0,1,2 só que com y 3,4,5
            nodep3.numChildren = nodep3.numChildren-1;  // tambem atualizo o numero de filhos de np3    

            nodeY.keys[j].ID = 0;                       // e tb limpo oq tava em y
            nodeY.keys[j].word.clear();    
            nodeY.keys[j].address = -1;

            nodeY.numChildren = nodeY.numChildren - 1;  // e tambem diminuo o nro de filhos
        }   

        np3 = putInArq(nodep3); 
        swapStruct(y, nodeY);                           // alguns dados de y foram alterados 

        // y eh o dendereco de um nodo q ja ta e seu endereco nao foi alterado 
        nodeX.children[i+1] = y;                        // dai y vira o ultimo filho de x  
        nodeX.children[i+1] = np3;                      // e depois np3 vira o ultimo 

        //como fiz mudancas em node x, node p1 e node p3, preciso gravar essas mudancas
        swapStruct(x, nodeX); 
    }
    return mid;                                         // e o meio q eu retorno de qualquer jeito 
}


//agr o bixo pega como q insere
void insert(Key key) {                  // o inteiro a eh o novo dado
    int i;                              // ints q eu nao sei devem ser dados
    Key t;                              // vai ser usada mais pra frente quando eu receber o meio 
    
    auxx = r;                           // o endereco do auxx eh o da raiz
    Node nodeX;                         // vou usar esse nodo


    if (auxx == -1) {                   // ?
        nodeX = init();                 // inicio ele 
        r = putInArq(nodeX);            // agora tenho endereco pra raiz 
        auxx = r;                       // x eh o q to trabalhando, nesse caso trab c a raiz

        //r sempre sera o endereco da raiz. sempree    
    } 

    else {

        //cout << "erro aq dentro"; 

        string strA; 
        string strI;
        string strI1; 
        string str0;
                
        nodeX = readInArq(auxx);      // usarei um nodeX    
                                      // a principio, no momento eh a raiz q eu smp vou usar

        if (nodeX.isLeaf== true && nodeX.numChildren == 6) {   // aqui, novamente, muda com a mudanca de tamanho 
            t = split_child(auxx, -1);                         // t eh o do meio, mandando -1?
            auxx = r;                                          
            nodeX = readInArq(auxx); 
            //sera q aqui eu to so mudando com quem eu to mexendo?

        
            for (i = 0; i < (nodeX.numChildren); i++) {        // enquanto i for menor que o numero de elementos de x
                strA  = key.word.toString(); 
                //cout << "A: " << strA << endl; 
                strI  = nodeX.keys[i].word.toString(); 
                //cout << "I: " << strI << endl; 
                strI1 = nodeX.keys[i+1].word.toString(); 
                //cout << "I1: " << strI1 << endl; 
                str0  = nodeX.keys[0].word.toString();
                //cout << "0 : " << str0 << endl; 

                if ((strA.compare(strI) > 0 ) && (strA.compare(strI1) < 0)) {    //ve se a string ta no intervalo
                    i++;                                    // ou seja, se ta dentro do intervalo, aumento i, e saio  
                    break;
                }
                else if (strA.compare(str0) < 0) {          // mas se ele nao ta no intervalo e eh menor q o primeiro, eu tb saio  
                    break;
                } 
                else {                                      // se nao, eu só continuo  
                    continue;
                }
            }
            auxx = nodeX.children[i]; 
            nodeX = readInArq(auxx); 
        } 

        else {                              
            while (nodeX.isLeaf == false) {                         // agr, caso x nao seja folha 
                //cout << "infinito "; 
                
                for (i = 0; i < (nodeX.numChildren); i++) {         // percorro o nro de filhos

                    strA = key.word.toString(); 
                    //cout << "a: " << strA << endl; 
                    strI = nodeX.keys[i].word.toString();
                    //cout << "I: " << strI << endl; 
                    strI1 = nodeX.keys[i+1].word.toString();
                    //cout << "I1: " << strI1 << endl; 
                    str0 = nodeX.keys[0].word.toString(); 
                    //cout << "I0: " << str0 << endl; 

                    if ((strA.compare(strI) > 0) && (strA.compare(strI1) < 0)) {// se a eh maior que o dado 1 e menor q o outro dado (ta no meio)
                        i++;                                // break
                        break;
                    } 
                    else if (strA.compare(str0) < 0) {                 // se for menor q o primeiro break tb  
                        break;
                    } 
                    else {                                  // se nao, sigo procurando
                        continue;
                    }
                }

                Node childrenI; 
                childrenI = readInArq(nodeX.children[i]); 
                if (childrenI.numChildren == 6) {            // se o x tem 6 filhos
                    t = split_child(auxx, i);                // ai tem q fazer a ladaia de separar e coloco o dado mid em t
                    
                    nodeX.keys[nodeX.numChildren] = t;       // dai o ultimo dado eh esse do meio
                    nodeX.numChildren = nodeX.numChildren+1; // aumento o nro de dados do x
                    continue;
                }   
                else {                                      // se nao ta cheio  
                    auxx = nodeX.children[i];               // aqui parece ser so uma dinamica com enderecos                    
                    nodeX = readInArq(auxx); 
                }  
            }
        }

    }
    nodeX.keys[nodeX.numChildren] = key;                    // salvando a key  

    sort(nodeX.keys, nodeX.numChildren);                    // ordeno tudo pra ficar bonitinho  
    nodeX.numChildren = nodeX.numChildren+1;                // aumento o nro de itens em x
    
    swapStruct(auxx, nodeX);                                // atualizo minha mudanca
}



int main() {
    Key key1, key2, key3, key4, key5, key6, key7, key8;

//preenchendo teste ------------------------------------------------------------------------------------------
    key1.word.fromString("dicionario"); 
    key2.word.fromString("abajour"); 
    key3.word.fromString("frogarm"); 
    key4.word.fromString("batata"); 
    key5.word.fromString("marinho"); 
    key6.word.fromString("hoje"); 
    key7.word.fromString("amanha"); 
    key8.word.fromString("ziterion"); 


    key1.ID = 20;
    key2.ID = 30;
    key3.ID = 40;
    key4.ID = 50;
    key5.ID = 60;
    key6.ID = 70;
    key7.ID = 80;
    key8.ID = 90;
 
  
    insert(key1);                                            // vou inserindo todos os elementos na arvore (IMPORTANTE, usarei)
    insert(key2);
    insert(key3);
    insert(key4);
    insert(key5);
    insert(key6);
    //insert(key7);
    //insert(key8);

    cout<<"traversal of constructed B tree\n";               // printo todos os elementos (IMPORTANTE, usarei)
    traverse(r);

    return 0; 
}
