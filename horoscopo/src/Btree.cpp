#include "../include/bib.h"

using namespace std;


//comecando com enderecos vazios pra nodos 
streampos r = -1;              //raiz 
streampos np = -1;             //node pointer
streampos auxx = -1;           //auxiliar x


void printNodo(Node nodo){ 
    Node nodeFilho; 
    cout << endl;
    cout << "*************" << endl;
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
        cout << "End filho["<< i << "] = "<< children << " - ";
        nodeFilho = readInArq(children); 
        nodeFilho.keys[0].word.wPrint();
        cout << ", "; 
        nodeFilho.keys[1].word.wPrint(); 
        cout << ", "; 
        nodeFilho.keys[2].word.wPrint(); 
        cout << ", "; 
        nodeFilho.keys[3].word.wPrint(); 
        cout << ", "; 
        nodeFilho.keys[4].word.wPrint(); 
        cout << ", "; 
        nodeFilho.keys[5].word.wPrint(); 
        
        cout << "->"; 
        for (auto children:nodeFilho.children){
            if (children != -1)
                cout << children << " ";
        } 
        cout << endl; 
        i++;


    }

    
    cout << "Eh folha? " << nodo.isLeaf << endl;
    cout << "Qnt chaves:" << nodo.numChildren << endl;
    cout << "*************";
    cout << endl; 

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

    //inicializando filhos em -1 
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

    ofstream BTreePut("Btree.bin", ios_base::binary | ios_base::app);

    if (!BTreePut) {                                   //arquivo nao foi criado/aberto
        return -1;
    }

                    
    BTreePut.write((char*)&node, sizeof(Node));
    // cout << "tellp: " << BTreePut.tellp() << endl; 

    addressNode = BTreePut.tellp();
    addressNode = addressNode - sizeof(Node);
    // cout << "ein, Dê... eu mereço?: " << addressNode << endl;   
    // int x;
    // cin >> x;
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
        cout << "- "; 
        node.keys[i].word.wPrint(); 
        cout <<endl;
    }
    cout<<endl;
    if (node.isLeaf == false) {                  // faco isso de novo, nao sei pq, talvez seja pro pai e o do lado tb aparecerem
        traverse(node.children[i]);
    }
    cout<<endl;
    // cout << "sera"; 
}


//sort the tree 

// ordena as keys em ordem crescente ALFABETICA dentro do nodo
// recebe o array de keys e a quantidade de keys 
void sort(Key *keys, int numKeys) {               
    int i, j;                                   
   
    string sj;                            // aqui pode ser um ponto que eu terei de alterar se tiver q usar array de char ao inves de str  
    string sj1;  
    Key auxKey;  
/*
    for (i = 0; i < numKeys; i++) {
        for (j = i; j <= numKeys; j++) {
            si = keys[i].word.toString(); 
            sj = keys[j].word.toString(); 

            if (si.compare("") != 0 && sj.compare("") != 0) {
                if ((si.compare(sj)) > 0) {
                auxKey = keys[i];
                keys[i] = keys[j];
                keys[j] = auxKey;
                }
            }
        }
    }
*/

    for (i = 0; i<6; i++) {

        for (j = 0; j < 6; j++) {
            sj = keys[j].word.toString(); 
            sj1 = keys[j+1].word.toString();

            if (sj.compare("") != 0 && sj1.compare("") != 0) {
                if ((sj.compare(sj1)) > 0){
                    auxKey = keys[j];
                    keys[j] = keys[j+1];
                    keys[j+1] = auxKey; 
                }
            }
        }
    }


    //printar sorted array
    cout << "sorted array" << endl; 
    for(i = 0; i < 6; i++) {
        keys[i].word.wPrint();
        cout << ","; 
    }
    cout << endl; 
    cout << endl; 
    //for ()
}



//recebo um endereco pro nodo x que ta em arquivo e um int i 
//suponho q int i na verdade seja uma Key newKey

// CONFERIR SE botei de volta TODOS OS NODOS ALTERADOS. PARA A MUDANÇA FICAR SALVA 
Key split_child(streampos x, int i) {                   // recebo o ponteiro para um nodo e um int i talvez faça sentido receber um ponteiro, já que to lidando com arquivos 
    
    /*DEBUG
    cout << "Estou fazendo split" << endl;
    */
    
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
    
    /* DEBUG 
    cout << "nodeXParam original" << endl; 
    printNodo(nodeXParam); 
    */

    //acho q esse -1 eh pra quando ta no inicio do arquivo
    if (i == -1) {   
        /* DEBUG 
        cout << "Estou no if(i==-1)" << endl;
        */                                        
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
        /* DEBUG 
        cout << "Primeiro resultado do meu nodeX" << endl; 
        cout << "E o meu mid eh: ";
        mid.word.wPrint();
        cout << endl; 
        */
        swapStruct(x, nodeXParam); 
       
       
        /* DEBUG 
        printNodo(nodeXParam);  
        */

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
        /* DEBUG 
        cout << "Segundo resultado do meu nodeX" << endl; 
        printNodo(nodeXParam);               
        */                     
        //agora fazendo mudancas em p1
        nodep1.keys[0] = mid;                           // ja a primeira key de np1 sera o meio
        nodep1.children[nodep1.numChildren] = x;        // x sera adicionado ao fim dos filhos de np1


        //finalmente, criando lugar pra p3 
        //e aguardando endereco
        np3 = putInArq(nodep3); 
        /* DEBUG 
        cout << "np3: " << np3 << endl; 
        cout << "Resultado do meu nodep3" << endl; 
        printNodo(nodep3);
        */

        nodep1.children[nodep1.numChildren + 1] = np3;  // np3 sera adicionado ao fim tambem (note que eh o endereço no documento)
        nodep1.numChildren = nodep1.numChildren + 1;    // o numero de filhos de np1 aumenta em 1

        //salvo o endereco de np1 como o da raiz  
        np1 = putInArq(nodep1); 
        /* DEBUG  
        cout << "np1: " << np1 << endl; 
        cout << "Resultado do meu nodep1" << endl; 
        printNodo(nodep1);
        */
        r = np1;   
    } 

    else { 
        /*DEBUG
        cout << "Fui pro else" << endl;                                        
        cout << "E to trabalhando com esse nodo aqui: "; 
        printNodo(nodeXParam); 
        */

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
        /* DEBUG 
        cout << "Primeiro salvamento Y" << endl; 
        printNodo(nodeY);
        */
        swapStruct(y,nodeY);


        for (j = 3; j <6; j++) {                       // aqui lembrar de mudar tb pra quando tiver mais itens 
            /* DEBUG 
            cout << "j:" << j << endl;
            cout << "j-3:" << (j-3) << endl;
            */
            nodep3.keys[j-3] = nodeY.keys[j];           // mesma coisa de antes, de encher np3 0,1,2 só que com y 3,4,5
            nodep3.numChildren = nodep3.numChildren+1;  // tambem atualizo o numero de filhos de np3    

            //hora de zerar o que ja mudei
            nodeY.keys[j].ID = 0;                       
            nodeY.keys[j].word.clear();    
            nodeY.keys[j].address = -1;

            nodeY.numChildren = nodeY.numChildren - 1;  // e tambem diminuo o nro de filhos        
        }   
        //OIOIOI burrices
        //nodeXParam = readInArq(x); 
        //guardado mudancas de y
        /* DEBUG 
        cout << "Segundo salvamento Y" << endl;     
        printNodo(nodeY);
        */
        swapStruct(y, nodeY); 

        //guardando np3 e suas mudancas  
        /*
        cout << "Salvando nodep3" << endl; 
        printNodo(nodep3);
        */
        
        np3 = putInArq(nodep3); 


    //AQUI CLARAMENTO TEM UM ERRO POIS PERCO UM NODO        
        // y eh o dendereco de um nodo q ja ta e seu endereco nao foi alterado 
    //OI
        for (int j = nodeXParam.numChildren; j >= i+1; j--){
            nodeXParam.children[j+1] = nodeXParam.children[j];
        }
            // Link the new child to this node
            nodeXParam.children[i+1] = y;


       // for (int j = nodeXParam.numChildren; j > i+1; j--){
       //     nodeXParam.children[j+1] = nodeXParam.children[j];
       // }
            // Link the new child to this node
            nodeXParam.children[i+1] = np3;
    
    
    //TCHAU

    //**************epa epa epa 
        //mudei i + 1 
    //    cout << "to apagando o endereco: " << nodeXParam.children[i+1] << "e colocando " << y; 
    //    nodeXParam.children[i+1] = y;   
    //    cout << "y" << endl; 
    //   printNodo(nodeY);    

    //    cout << "to apagando o endereco: " << nodeXParam.children[i+1] << "e colocando " << np3; 
    //    nodeXParam.children[i+1] = np3;  
        

    //**************epa epa epa 
        
        /*DEBUG
        //print x debug
        cout << "x" << endl;
        printNodo(nodeXParam);    

        cout << "np3" << endl;
        printNodo(nodeXParam);                     

        //atualizo x de novo
        cout << "Salvando nodeXParam" << endl; 
        //oioioi
        */
        swapStruct(x, nodeXParam); 
        
/*      DEBUG
        printNodo(nodeXParam);
        cout << "olha so to imprimindo oq ta em x: " << endl; 
        Node auxTestesBala; 
        auxTestesBala = readInArq(x);
        printNodo(auxTestesBala); 

        cout << "olha so to imprimindo oq ta em auxx: " << endl; 
        auxTestesBala = readInArq(auxx);
        printNodo(auxTestesBala);  */
        
    }
    return mid;                                         // e o meio q eu retorno de qualquer jeito 
}


//agr o bixo pega como q insere
void insert(Key key) {                  // o inteiro a eh o novo dado
    
    /* DEBUG 
    cout << "Estou inserindo" << endl;
    if (key.word.compareW("abelhinha") == 0){
        cout << "-------" << endl;
        cout << "ABELHINHA" << endl;
        cout << "-------" << endl;
    }
    */
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
            /* DEBUG 
            cout << "O temido chegou. Folha e filhos pa" << endl;
            cout << "vou mandar isso aqui pra lá" << endl;
            printNodo(nodeX);
            */
            t = split_child(auxx, -1);                         // t eh o do meio, mandando -1?
            nodeX = readInArq(auxx); 

            //cout << "t eh: "; 
            //t.word.wPrint();
            //cout << endl << endl; 
            
            //atualizando raiz caso eu queira saber
            // nodeRoot = readInArq(r); 
            // cout << "Imprimindo meu nodo raiz" << endl;
            // printNodo(nodeRoot);


            /* DEBUG 
            cout << "r: " << r << endl;
            */
            auxx = r;  
            nodeX = readInArq(auxx); 
            /* DEBUG 
            cout << "Imprimindo meu NOVO nodeX" << endl;
            printNodo(nodeX);
            */

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
            /* DEBUG 
            cout << "Salvando meu nodeX" << endl;
            printNodo(nodeX);
            */
            swapStruct(auxx, nodeX); 
        }
        else {    
            //PERIGO MUDADO
            //nodeX = readInArq(auxx); 
            /* DEBUG 
            cout << "else 402" << endl; 
            */                        
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
                
                /* DEBUG 
                if (key.word.compareW("abelinha") == 0){
                    cout << "childrenI" << endl;
                    printNodo(childrenI);
                    cout<<endl;
                    traverse(r);
                }
                */
                //EEEERROOOO POR AQUI
                //testes
                // cout << "filhos dos filhos" << childrenI.numChildren;
                /* DEBUG 
                cout << "------------------------------------------------------------" << endl;
                */
                if (childrenI.numChildren == 6) {            // se o x tem 6 filhos
                    
                    /* DEBUG 
                    cout << "childrenI.numChildren == 6 e end eh" << auxx << endl;
                    
                    if (key.word.compareW("abelhinha") == 0){
                        cout << "nodeX antes do split:" << endl;
                        printNodo(nodeX);
                    }
                    */
                    t = split_child(auxx, i);                // ai tem q fazer a ladaia de separar e coloco o dado mid em t
                    
                    //A MUDANCA DE MILHOES
                    nodeX = readInArq(auxx); 

                    /* DEBUG 
                    if (key.word.compareW("abelhinha") == 0){
                        cout << "nodeX depois do SPLIT UM... CONTANDO:" << endl;
                        printNodo(nodeX);
                        cout << "t eh: ";
                        t.word.wPrint(); 
                        cout << endl;
                    }
                    */

                    //exatamente aq
                    
                    nodeX.keys[nodeX.numChildren] = t;       // dai o ultimo dado eh esse do meio
                        
                    nodeX.numChildren = nodeX.numChildren+1; // aumento o nro de dados do x
                    
                    //BAH OH
                    //sort(nodeX.keys, nodeX.numChildren); 
                    //swapStruct(auxx, nodeX);


                    // if (key.word.compareW("abelhinha") == 0){

                    //     cout << "ANTES DA SORTE... azar....";
                    //     printNodo(nodeX); 

                        

                    //     cout << "DEPOIS DO SORT DEU... azar....";
                    //     printNodo(nodeX); 


                    //     cout << "nodeX depois do split:" << endl;
                    //     printNodo(nodeX);

                    //     cout << "t eh: ";
                    //     t.word.wPrint(); 
                    // }
                    //MUDEI AQUI
                    swapStruct(auxx, nodeX);
                    continue;
                }   
                else {                                      // se nao ta cheio  
                    //OUTRA MUDANCA MILHONARIA
                    //nodeX = readInArq(auxx); 

                    /* DEBUG 
                    cout << "else 440" << endl;
                    */

                    auxx = nodeX.children[i]; 
                    nodeX = readInArq(auxx); 

                    /* DEBUG 
                    if (key.word.compareW("abelhinha") == 0){
                        cout << "no else node x virou: " << endl;
                        printNodo(nodeX);
                    }
                    */

                    //atualizando nodo X onde esta guardado updates
                    //DUVIDAS 
                    swapStruct(auxx, nodeX); 
                }  

                nodeX = readInArq(auxx); 

                /* DEBUG 
                if (key.word.compareW("abelhinha") == 0){
                        cout << "saindo do perigo"<<endl<<"nodeX depois de tudo eh:" << endl;
                        printNodo(nodeX);
                }
                cout << "------------------------------------------------------------" << endl;
                */
            }
        }
    }


    
    nodeX.keys[nodeX.numChildren] = key;                    // salvando a key  
    /* DEBUG 
    cout << "INSERI ESSE AQUI OLHA"; 
    printNodo(nodeX);
    */

    sort(nodeX.keys, nodeX.numChildren);                    // ordeno tudo pra ficar bonitinho  
    /* DEBUG
    cout << "ORDENEI ESSE AQUI OLHA"; 
    
    printNodo(nodeX);
    */

    nodeX.numChildren = nodeX.numChildren+1;                // aumento o nro de itens em x
    swapStruct(auxx, nodeX);                                // atualizo minha mudanca

}

int main() {
    Key key1, key2, key3, key4, key5, key6, key7, key8, key9, key10, key11, key12, key13, key14, key15, key16, key17, key18, key19, key20, key21, key22, key23, key24, key25, key26, key27, key28, key29, key30, key31, key32, key33, key34, key35, key36, key37, key38, key39, key40, key41, key42, key43, key44, key45, key46, key47, key48, key49, key50, key51, key52, key53, key54, key55, key56, key57, key58, key59, key60, key61, key62, key63, key64, key65, key66, key67, key68, key69, key70, key71, key72, key73, key74, key75, key76, key77;
//preenchendo teste ------------------------------------------------------------------------------------------
    key1.word.fromString("anjo");
    key2.word.fromString("banana");
    key3.word.fromString("carro");
    key4.word.fromString("dado");
    key5.word.fromString("elefante");
    key6.word.fromString("futebol");
    key7.word.fromString("guitarra");
    key8.word.fromString("hidroavião");
    key9.word.fromString("internet");
    key10.word.fromString("jardim");
    key11.word.fromString("kiwi");
    key12.word.fromString("limonada");
    key13.word.fromString("montanha");
    key14.word.fromString("notebook");
    key15.word.fromString("oculos");
    key16.word.fromString("piano");
    key17.word.fromString("queijo");
    key18.word.fromString("rosa");
    key19.word.fromString("sabonete");
    key20.word.fromString("tartaruga");
    key21.word.fromString("uva");
    key22.word.fromString("viagem");
    key23.word.fromString("xadrez");
    key24.word.fromString("yoga");
    key25.word.fromString("zebra");
    key26.word.fromString("amora");
    key27.word.fromString("borboleta");
    key28.word.fromString("caranguejo");
    key29.word.fromString("dente");
    key30.word.fromString("escova");
    key31.word.fromString("foguete");
    key32.word.fromString("gato");
    key33.word.fromString("hidrante");
    key34.word.fromString("iglu");
    key35.word.fromString("janela");
    key36.word.fromString("ketchup");
    key37.word.fromString("lagosta");
    key38.word.fromString("melancia");
    key39.word.fromString("navio");
    key40.word.fromString("ouro");
    key41.word.fromString("pato");
    key42.word.fromString("quimono");
    key43.word.fromString("rato");
    key44.word.fromString("sorvete");
    key45.word.fromString("tartan");
    key46.word.fromString("urubu");
    key47.word.fromString("vassoura");
    key48.word.fromString("waffle");
    key49.word.fromString("xarope");
    key50.word.fromString("yacht");
    key51.word.fromString("zangão");
    key52.word.fromString("abelha");
    key53.word.fromString("bacon");
    key54.word.fromString("cacto");
    key55.word.fromString("dedo");
    key56.word.fromString("eletricidade");
    key57.word.fromString("fogão");
    key58.word.fromString("girafa");
    key59.word.fromString("helicóptero");
    key60.word.fromString("ilha");
    key61.word.fromString("jacaré");
    key62.word.fromString("kimono");
    key63.word.fromString("limão");
    key64.word.fromString("mala");
    key65.word.fromString("noz");
    key66.word.fromString("orelha");
    key67.word.fromString("pimenta");
    key68.word.fromString("queimadura");
    key69.word.fromString("roda");
    key70.word.fromString("sapato");
    key71.word.fromString("tatu");
    key72.word.fromString("urso");
    key73.word.fromString("vaca");
    key74.word.fromString("xícara");
    key75.word.fromString("yoga");
    key76.word.fromString("zumbi");
    key77.word.fromString("abacaxi");

    insert(key1);
    insert(key2);
    insert(key3);
    insert(key4);
    insert(key5);
    insert(key6);
    insert(key7);
    insert(key8);
    insert(key9);
    insert(key10);
    insert(key11);
    insert(key12);
    insert(key13);
    insert(key14);
    insert(key15);
    insert(key16);
    insert(key17);
    insert(key18);
    insert(key19);
    insert(key20);
    insert(key21);
    insert(key22);
    insert(key23);
    insert(key24);
    /*insert(key25);
    insert(key26);
    insert(key27);
    insert(key28);
    insert(key29);
    insert(key30);
    insert(key31);
    insert(key32);
    insert(key33);
    insert(key34);
    insert(key35);
    insert(key36);
    insert(key37);
    insert(key38);
    insert(key39);
    insert(key40);
    insert(key41);
    insert(key42);
    insert(key43);
    insert(key44);
    insert(key45);
    insert(key46);
    insert(key47);
    insert(key48);
    insert(key49);
    insert(key50);
    insert(key51);
    insert(key52);
    insert(key53);
    insert(key54);
    insert(key55);
    insert(key56);
    insert(key57);
    insert(key58);
    insert(key59);
    insert(key60);
    insert(key61);
    insert(key62);
    insert(key63);
    insert(key64);
    insert(key65);
    insert(key66);
    insert(key67);
    insert(key68);
    insert(key69);
    insert(key70);
    insert(key71);
    insert(key72);
    insert(key73);
    insert(key74);
    insert(key75);
    insert(key76);
    insert(key77);*/


   
    Node auxPrint; 

    auxPrint = readInArq(r); 
    printNodo(auxPrint); 

    // cout<<"traversal of constructed B tree\n";               // printo todos os elementos (IMPORTANTE, usarei)
    traverse(r);

    return 0; 
}
