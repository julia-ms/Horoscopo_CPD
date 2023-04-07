#include "../include/bib.h"

using namespace std;


//comecando com enderecos vazios pra nodos 
streampos r = -1;              //raiz 
streampos np = -1;             //node pointer
streampos auxx = -1;           //auxiliar x


void printNodo(Node nodo){ 
    cout << endl << endl; 
    cout << "Chaves: " << endl; 
    
    int i = 0; 
    for (auto keys:nodo.keys) {
        cout << "Chave[" << i << "] = ";
        keys.word.wPrint(); 
        cout << endl; 
        cout << "address = " << keys.address << endl;
        i++;  
    }
    cout << endl; 
    
    i = 0; 
    for (auto children:nodo.children){
        cout << "End filho["<< i << "]"<< children << endl;
        i++;
    }

    cout << "Eh folha? " << nodo.isLeaf << endl;
    cout << "Qnt chaves:" << nodo.numChildren << endl;
}


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
    node.isLeaf = true;                 // Indicando que o nó não é folha
    node.numChildren = 0; 
    return node; 
}

//funcao que coloca nodo no fim do arquivo e retorna endereço 
streampos putInArq(Node node) {
    streampos addressNode; 

    ofstream BTreePut("Btree.bin", ios::binary | ios::app);

    if (!BTreePut) {                                   //arquivo nao foi criado/aberto
        return -1;
    }

    addressNode = BTreePut.tellp();                     
    BTreePut.write((char*)&node, sizeof(Node));

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
    
    Node nodeAux; 
    nodeAux = node; 

    ofstream BTreeSwap("Btree.bin", ios::binary | ios::in);
        
    //move o ponteiro ate a posicao da string antiga 
    BTreeSwap.seekp(pos); 

    //escrevo nodo no arquivo nessa posicao
    BTreeSwap.write((char*)&nodeAux, sizeof(Node));        
    
    // cout << "estou fazendo swap e guardei o nodo: " << endl;
    // printNodo(nodeAux);
    
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
    //cout << "sera"; 
    cout<<endl;
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
    cout << "Estou fazendo split" << endl;
    int j;                                              // j eh um contador
   
    Key mid; 
    
    streampos np1, np3, y;                              // aqui tenho 3 enderecos para nodos, talvez pq sejam 6 keys (mas e pra lidar com t maiores? possivelmente array)
    Node nodep1, nodep3, nodeY, nodeXParam;                  // aqui tenhos os 3 nodos auxiliares
    
    //primeiro, vou inicializar tudo
    nodep3 = init();
    nodeY = init();

    nodep3.isLeaf = true;                                       

    //tenho aqui o nodo do endereco que mandaram
    nodeXParam = readInArq(x); 
    cout << "nodeXParam original" << endl; 
    printNodo(nodeXParam); 
    //acho q esse -1 eh pra quando ta no inicio do arquivo
    if (i == -1) {   
        cout << "Estou no if(i==-1)" << endl;                                        
        mid = nodeXParam.keys[2];                            // novamente tenho q lembrar q isso vale pra 6 chaves, e nao pra 250 como teremos depois. 2 eh o meio de 0 a 5
        
        //zerando o nodo   
        nodeXParam.keys[2].ID = 0;
        nodeXParam.keys[2].word.clear();
        nodeXParam.keys[2].address = -1; 

        //atualizando dados 
        nodeXParam.numChildren = nodeXParam.numChildren - 1;        // zerei um, ja diminuo o numero de filhos
        
        nodep1 = init();
        nodep1.isLeaf = false;                  
        nodeXParam.isLeaf = true; 
        cout << "Primeiro resultado do meu nodeX" << endl; 
        cout << "E o meu mid eh: ";
        mid.word.wPrint();
        cout << endl; 
        swapStruct(x, nodeXParam); 
        printNodo(nodeXParam);  

        //criando nodo 1 mas ainda sem salvar em nenhum lugar
                
        for (j = 3; j < 6; j++) {                       // agora do meio ao fim, parece q aqui ocorrem trocas importantes
            nodep3.keys[j-3] = nodeXParam.keys[j];           // as keys 0, 1, 2 de um novo nodo serao as 1,2,3 do antigo
            nodep3.children[j - 3] = nodeXParam.children[j]; // os filhos 0, 1, 2 do novo nodo serao 1,2,3 do antigo
            nodep3.numChildren = nodep3.numChildren+1;  // vou atualizar o numero de filhos

            // e cada vez que eu tiro uma key, eu zero/apago do antigo
            nodeXParam.keys[j].ID = 0;                       
            nodeXParam.keys[j].word.clear();
            nodeXParam.keys[j].address = -1; 
            nodeXParam.numChildren = nodeXParam.numChildren-1; 

            //swapStruct(x, nodeXParam); 
            //ate aqui, eu ainda nao precisei gravar p1 ou p
            //estou carregando eles
        }            
        for (j = 0; j < 6; j++) {       
            nodeXParam.children[j] = -1;                   // quando acabar isso, o antigo nao tera nenhum filho (desceu)
        }
        swapStruct(x, nodeXParam); 
        cout << "Segundo resultado do meu nodeX" << endl; 
        printNodo(nodeXParam);                                    
        //agora fazendo mudancas em p1
        nodep1.keys[0] = mid;                           // ja a primeira key de np1 sera o meio
        nodep1.children[nodep1.numChildren] = x;        // x sera adicionado ao fim dos filhos de np1


        //finalmente, criando lugar pra p3 
        //e aguardando endereco
        np3 = putInArq(nodep3); 
        cout << "Resultado do meu nodep3" << endl; 
        printNodo(nodep3);

        nodep1.children[nodep1.numChildren + 1] = np3;  // np3 sera adicionado ao fim tambem (note que eh o endereço no documento)
        nodep1.numChildren = nodep1.numChildren + 1;    // o numero de filhos de np1 aumenta em 1

        //salvo o endereco de np1 como o da raiz  
        np1 = putInArq(nodep1); 
        cout << "Resultado do meu nodep1" << endl; 
        printNodo(nodep1);
        r = np1;   
    } 

    else {
        cout << "Fui pro else" << endl;                                        
        y = nodeXParam.children[i];                          // y recebe o endereco de um dos filhos q eu recebi
        nodeY = readInArq(y); 
        mid = nodeY.keys[2];                            // de novo, isso funciona pq sao 6 dados. aqui mid eh o do meio. se eu tiver mais, como vou ter, muda  
        
        // cout << "mid is: "; 
        // mid.word.wPrint();
        // cout << endl; 

        //limpando y ja q ja salvei a chave no mid  
        nodeY.keys[2].ID = 0;                           // e cada vez que eu tiro uma key, eu zero/apago do antigo
        nodeY.keys[2].word.clear();
        nodeY.keys[2].address = -1;

        nodeY.numChildren = nodeY.numChildren-1;        // diminui o nro de filhos

        //vou no endereco y e guardo as mudancas
        cout << "Primeiro salvamento Y" << endl; 
        printNodo(nodeY);
        swapStruct(y,nodeY);


        for (j = 3; j <6; j++) {                       // aqui lembrar de mudar tb pra quando tiver mais itens 

            nodep3.keys[j-3] = nodeY.keys[j];           // mesma coisa de antes, de encher np3 0,1,2 só que com y 3,4,5
            nodep3.numChildren = nodep3.numChildren+1;  // tambem atualizo o numero de filhos de np3    

            //hora de zerar o que ja mudei
            nodeY.keys[j].ID = 0;                       
            nodeY.keys[j].word.clear();    
            nodeY.keys[j].address = -1;

            nodeY.numChildren = nodeY.numChildren - 1;  // e tambem diminuo o nro de filhos        
        }   
        //guardado mudancas de y
        cout << "Segundo salvamento Y" << endl; 
        printNodo(nodeY);
        swapStruct(y, nodeY); 

        //guardando np3 e suas mudancas  
        cout << "Salvando nodep" << endl; 
        printNodo(nodeY);
        np3 = putInArq(nodep3); 

                                   
        // y eh o dendereco de um nodo q ja ta e seu endereco nao foi alterado 
        nodeXParam.children[i+1] = y;                          
        nodeXParam.children[i+1] = np3;                       

        //atualizo x de novo
        cout << "Salvando nodeXParam" << endl; 
        printNodo(nodeXParam);
        swapStruct(x, nodeXParam); 
    }
    return mid;                                         // e o meio q eu retorno de qualquer jeito 
}


//agr o bixo pega como q insere
void insert(Key key) {                  // o inteiro a eh o novo dado
    int i;                              // ints q eu nao sei devem ser dados
    Key t;                              // vai ser usada mais pra frente quando eu receber o meio 
    
    auxx = r;                           // o endereco do auxx eh o da raiz
    
    Node nodeX;   
    nodeX = init();  
    Node nodeRoot; 

    if (auxx == -1) {      

        //crio um nodo, coloco no arquivo e retorno a posicao dele 
        nodeRoot = init();                 
        r = putInArq(nodeRoot);             
        auxx = r;                       // x eh o q to trabalhando, nesse caso trab c a raiz    
    } 

    else {

        string strA; 
        string strI;
        string strI1; 
        string str0;
                
        nodeX = readInArq(auxx);      // usarei um nodeX                                          // a principio, no momento eh a raiz q eu smp vou usar

        if (nodeX.isLeaf== true && nodeX.numChildren == 6) {   // aqui, novamente, muda com a mudanca de tamanho 
            t = split_child(auxx, -1);                         // t eh o do meio, mandando -1?
            
            //cout << "t eh: "; 
            //t.word.wPrint();
            //cout << endl << endl; 
            
            //atualizando raiz caso eu queira saber
            nodeRoot = readInArq(r); 

            auxx = r;  
            nodeX = readInArq(auxx); 

            for (i = 0; i < (nodeX.numChildren); i++) {        // enquanto i for menor que o numero de elementos de x
                strA  = key.word.toString(); 
                strI  = nodeX.keys[i].word.toString(); 
                strI1 = nodeX.keys[i+1].word.toString(); 
                str0  = nodeX.keys[0].word.toString();

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

            //atualizando nodo X onde esta guardado updates
            //DUVIDAS 
            swapStruct(auxx, nodeX); 
        } 

        else {                              
            while (nodeX.isLeaf == false) {                         // agr, caso x nao seja folha 
                
                for (i = 0; i < (nodeX.numChildren); i++) {         // percorro o nro de filhos

                    strA = key.word.toString(); 
                    strI = nodeX.keys[i].word.toString();
                    strI1 = nodeX.keys[i+1].word.toString();
                    str0 = nodeX.keys[0].word.toString(); 

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

                //testes
                cout << "filhos dos filhos" << childrenI.numChildren;

                if (childrenI.numChildren == 6) {            // se o x tem 6 filhos
                    t = split_child(auxx, i);                // ai tem q fazer a ladaia de separar e coloco o dado mid em t
                    
                    nodeX.keys[nodeX.numChildren] = t;       // dai o ultimo dado eh esse do meio
                    nodeX.numChildren = nodeX.numChildren+1; // aumento o nro de dados do x
                    
                    swapStruct(auxx, nodeX);
                    continue;
                }   
                else {                                      // se nao ta cheio  
    
                    auxx = nodeX.children[i]; 
                    nodeX = readInArq(auxx); 

                    //atualizando nodo X onde esta guardado updates
                    //DUVIDAS 
                    swapStruct(auxx, nodeX); 
                }  

                nodeX = readInArq(auxx); 

            }
        }
    }
    
    nodeX.keys[nodeX.numChildren] = key;                    // salvando a key  
    sort(nodeX.keys, nodeX.numChildren);                    // ordeno tudo pra ficar bonitinho  
    nodeX.numChildren = nodeX.numChildren+1;                // aumento o nro de itens em x
    swapStruct(auxx, nodeX);                                // atualizo minha mudanca
}

int main() {
    Key key1, key2, key3, key4, key5, key6, key7, key8, key9, key10, key11, key12, key13, key14, key15, key16, key17, key18, key19, key20, key21, key22, key23, key24, key25, key26, key27, key28;

//preenchendo teste ------------------------------------------------------------------------------------------
    key1.word.fromString("dicionario"); 
    key2.word.fromString("abajour"); 
    key3.word.fromString("frogarm"); 
    key4.word.fromString("batata"); 
    key5.word.fromString("marinho"); 
    key6.word.fromString("hoje"); 
    key7.word.fromString("amanha"); 
    key8.word.fromString("ziterion");
    key15.word.fromString("teclado");
    key16.word.fromString("guitarra");
    key17.word.fromString("sorvete");
    key18.word.fromString("aventura");
    key19.word.fromString("felicidade");
    key20.word.fromString("chocolate");
    key21.word.fromString("melancia");
    key22.word.fromString("fantasia");
    key23.word.fromString("unicórnio");
    key24.word.fromString("viagem");
    key25.word.fromString("natureza");
    key26.word.fromString("amor");
    key27.word.fromString("liberdade");
    key28.word.fromString("sabedoria");


    key1.ID = 20;
    key2.ID = 30;
    key3.ID = 40;
    key4.ID = 50;
    key5.ID = 60;
    key6.ID = 70;
    key7.ID = 80;
    key8.ID = 90;
    key9.ID = 100;
    key10.ID = 10;

    insert(key1);
    // traverse(r);
    // cout << endl;

    insert(key2);
    // traverse(r);
    // cout << endl;

    insert(key3);
    // traverse(r);
    // cout << endl;

    insert(key4);
    // traverse(r);
    // cout << endl;

    insert(key5);
    // traverse(r);
    // cout << endl;

    insert(key6);
    // traverse(r);
    // cout << endl;

    insert(key7);
    cout << "Sétima chave" << endl;
    traverse(r);
    cout << endl;

    // insert(key8);
    // traverse(r);
    // cout << endl;

    // insert(key9);
    // traverse(r);
    // cout << endl;

    // insert(key10);
    // traverse(r);
    // cout << endl;

    // insert(key11);
    // traverse(r);
    // cout << endl;

    // insert(key12);
    // traverse(r);
    // cout << endl;

    // insert(key13);
    // traverse(r);
    // cout << endl;

    // insert(key14);
    // traverse(r);
    // cout << endl;

    /*insert(key15);
    insert(key16);
    insert(key17);
    insert(key18);
    insert(key19);
    insert(key20);
    insert(key21);
    insert(key22);
    insert(key23);
    insert(key24);
    insert(key25);
    insert(key26);
    insert(key27);
    insert(key28);*/

    Node auxPrint; 

    auxPrint = readInArq(r); 
    printNodo(auxPrint); 

    // cout<<"traversal of constructed B tree\n";               // printo todos os elementos (IMPORTANTE, usarei)
    // traverse(r);

    return 0; 
}
