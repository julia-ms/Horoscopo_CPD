#include<iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//node declaration
struct BTree {
    int *d;              // dado/key ->  eh um ponteiro pois é usado um array de keys
    BTree **child_ptr;   // nodos filhos   
    bool l;              // folha ou nao
    int n;               // numero de filhos
} *r = NULL, *np = NULL, *x = NULL;     // zero ideia do que seja isso, acho q sao so BTrees ja definidas pq vao ser mto usadas

//creation of node
BTree* init() {
    int i; 
    np = new BTree;                      // np eh como chama um novo nodo
    np->d = new int[6];                  // ordem 6, pois cabem 6 keys 
    np->child_ptr = new BTree *[7];      // como sao 6 dados, cabem 7 filhos. cada filho eh um novo nodo com seus dados  
    np->l = true;                        // eh folha, só nao sei pq   
    np->n = 0;                           // no momento, nao tem filhos   
    for (i = 0; i < 7; i++) {            
        np->child_ptr[i] = NULL;         // como nao tem filhos, os ponteiros pra cada filho eh NULL
    }                                    // retorna esse novo nodo criado
    return np;                              
}

//traverse the tree
/*A função "traverse tree" em uma implementação de B-trees é responsável por 
percorrer a árvore a partir da raiz até encontrar um determinado nó, 
chave ou intervalo de chaves. Essa função é fundamental para a busca 
de informações em uma B-tree, já que é necessário percorrer a estrutura 
a partir da raiz para encontrar o nó correto.*/

void traverse(BTree *p) {
    cout<<endl;
    int i;
    for (i = 0; i < p->n; i++) {          // enquanto i for menor que o numero de filhos
        if (p->l == false) {              // se o nodo nao eh folha, ou seja, se nao acabou e ainda tem filhos   
            traverse(p->child_ptr[i]);    // vou recursivamente entrar no nodo filho e repetir isso, ate chegar no ultimo filho
        }
    cout << " " << p->d[i];               // assim, como depois eu volto tudo, vou imprimir o dado i e estarei imprimindo em ordem 
    }
    if (p->l == false) {                  // faco isso de novo, nao sei pq, talvez seja pro pai e o do lado tb aparecerem
        traverse(p->child_ptr[i]);
    }
    cout<<endl;
}

//sort the tree 
void sort(int *p, int n) {               // possivelmente serve para deixar as keys em ordem crescentes como devem ser
   int i, j, t;                          // entao eh um algoritmo de ordenar normal            
   for (i = 0; i < n; i++) {
      for (j = i; j <= n; j++) {
         if (p[i] >p[j]) {
            t = p[i];
            p[i] = p[j];
            p[j] = t;
         }
      }
   }
}

// ACHO q x é tipo o primeiro elemento? 

// aqui começa a ficar louco! é a funcao que divide o nodo e os filhos quando o tamanho excede t
int split_child(BTree *x, int i) {      // recebo o ponteiro para um nodo e um int i talvez faça sentido receber um ponteiro, já que to lidando com arquivos 
    int j, mid;                         // declaro um int meio e um int j (auxiliar?)
    BTree *np1, *np3, *y;               // aqui tenho 3 enderecos para b tree, talvez pq sejam 6 keys
    np3 = init();                       // create new node        
    np3->l = true;                      // digo que ele é folha (sem filhos)
    if (i == -1) {                           
        mid = x->d[2];                  // encontro meio assim pois eh o a key do meio [0,1, 2 ,3,4,5] ja q eh de ordem 6 (sao 6 keys)
                                        // eu salvei o dado já como mid (note q mid deve ser struct na outra implementacao)
        x->d[2] = 0;                    // como o meio e tudo q tem depois dele sai, posso ate zerar o dado q tava ali         
        x->n--;                         // zerei um, ja diminuo o numero de filhos
        
        np1 = init();                   // agora criei o nodo 1  
        np1->l= false;                  // ele nao eh folha 
        x->l= true;                     // mas x virará folha (e as keys? oq ta contecendo) (sera um nodo sem filhos?) 

        for (j = 3; j < 6; j++) {       // agora do meio ao fim, parece q aqui ocorrem trocas importantes
            np3->d[j - 3] = x->d[j];    // as keys 0, 1, 2 de um novo nodo serao as 1,2,3 do antigo
            np3->child_ptr[j - 3] = x->child_ptr[j]; // os filhos 0, 1, 2 do novo nodo serao 1,2,3 do antigo
            np3->n++;                   // vou atualizar o numero de filhos
            x->d[j] = 0;                // e cada vez que eu tiro uma key, eu zero/apago do antigo
            x->n--;                     // e tambem diminuo o numero de filhos 
        }
        for (j = 0; j < 6; j++) {       
            x->child_ptr[j] = NULL;     // quando acabar isso, o antigo nao tera nenhum filho (desceu)
        }
        np1->d[0] = mid;                // ja a primeira key de np1 sera o meio
        np1->child_ptr[np1->n] = x;     // x sera adicionado ao fim dos filhos de np1
        np1->child_ptr[np1->n + 1] = np3; // np3 sera adicionado ao fim tambem 
        np1->n++;                       // o numero de filhos de np1 aumenta em 1  
        r = np1;                        // r eu sei la o que eh e nao vejo a utilidade aqui 
    } 
    else {
        y = x->child_ptr[i];            // senao alguma coisa (?) esse novo y eh igual a child tal
        mid = y->d[2];                  // ai sim, mid eh o meio da child tal  
        y->d[2] = 0;                    // ja tirei o do meio do y
        y->n--;                         // diminui o nro de filhos  
        for (j = 3; j <6 ; j++) {
            np3->d[j - 3] = y->d[j];    // mesma coisa de antes, de encher np3 0,1,2 só que com y 3,4,5
            np3->n++;                   // tambem atualizo o numero de filhos de np3    
            y->d[j] = 0;                // e tb limpo oq tava em y  
            y->n--;                     // e tambem diminuo o nro de filhos
        }   
        x->child_ptr[i + 1] = y;        // dai y vira o ultimo filho de x  
        x->child_ptr[i + 1] = np3;      // e depois np3 vira o ultimo 
    }
    return mid;                         // e o meio q eu retorno de qualquer jeito 
}

//agr o bixo pega como q insere
void insert(int a) {                    // o inteiro a eh o novo dado
    int i, t;                           // ints q eu nao sei devem ser dados
    
    x = r;                              // ?
    
    if (x == NULL) {                    // ?
        r = init();
        x = r;                          // criei dois nodos   
    } 
    else {
        if (x->l== true && x->n == 6) {                     // se ele é folha (nao eh criado sempre como?) e o numero de filhos eh 6 (como?)
            t = split_child(x, -1);                         // t eh o do meio, mandando -1?
            x = r; 
                                                     // ? de novo meu Deus  
            for (i = 0; i < (x->n); i++) {                  // enquanto i for menor que o numero de elementos de x
                if ((a >x->d[i]) && (a < x->d[i + 1])) {    //se o dado q quero colocar for maior q o do filho do x e menor q do prox filho
                    i++;                                    // ou seja, se ta dentro do intervalo, aumento i, e saio  
                    break;
                } 
                else if (a < x->d[0]) {                     // mas se ele nao ta no intervalo e eh menor q o primeiro, eu tb saio  
                    break;
                } 
                else {                                      // se nao, eu só continuo  
                    continue;
                }
            }
            x = x->child_ptr[i];                            // x ?? fica igual ao filho i de x 
        } 
        else {                              
            while (x->l == false) {                         // agr, caso x nao seja folha 
                for (i = 0; i < (x->n); i++) {              // percorro o nro de filhos
                    if ((a >x->d[i]) && (a < x->d[i + 1])) {// se a eh maior que o dado 1 e menor q o outro dado (ta no meio)
                        i++;                                // break
                        break;
                    } 
                    else if (a < x->d[0]) {                 // se for menor q o primeiro break tb  
                        break;
                    } 
                    else {                                  // se nao, sigo procurando
                        continue;
                    }
                }
                if ((x->child_ptr[i])->n == 6) {            // se o x tem 6 filhos
                    t = split_child(x, i);                  // ai tem q fazer a ladaia de separar e coloco o dado mid em t
                    x->d[x->n] = t;                         // dai o ultimo dado eh esse do meio
                    x->n++;                                 // aumento o nro de dados do x
                    continue;
                }   
                else {                                      // se nao ta cheio  
                    x = x->child_ptr[i];                    // eh so adicionar o filho  
                }
            }
        }
    }
    x->d[x->n] = a;                                         // o ultimo recebe a   
    sort(x->d, x->n);                                       // ordeno tudo pra ficar bonitinho  
    x->n++;                                                 // aumento o nro de itens em x
}

int main() {
   int i, n, t;
   srand(time(NULL));

   for(i = 0; i < 75; i++) {
        t = rand() % 100;
        cout << "t eh" << t; 
        insert(t);                                            // vou inserindo todos os elementos na arvore (IMPORTANTE, usarei)
   }
   cout<<"traversal of constructed B tree\n";               // printo todos os elementos (IMPORTANTE, usarei)
   traverse(r);
}


/*
aqui eu tenho uma implementação de B tree, o que quero fazer essa noite é
    - entender como funciona 
    - ver se é possível substituir ints por keys
        - ver se é possivel ordenar pelas keys dessas palavras
    - ver se é possível fazer essa ordenação usando uma estrutura em disco  


*/