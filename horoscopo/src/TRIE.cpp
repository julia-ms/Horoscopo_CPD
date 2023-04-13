#include "../include/bib.h"

using namespace std;
 
// Define o tamanho do caractere
#define CHAR_SIZE 128
 
// Uma classe para armazenar um nó Trie
class Trie
{
public:
    bool isLeaf;
    Trie* character[CHAR_SIZE];
    int pos;
 
    // Construtor
    Trie()
    {
        this->isLeaf = false;
 
        for (int i = 0; i < CHAR_SIZE; i++) {
            this->character[i] = nullptr;
        }

        pos  = -1; 
    }
 
    void insert(string, streampos);
    bool deletion(Trie*&, string);
    Trie* search(string);
    bool haveChildren(Trie const*);
};
 
// Função iterativa para inserir uma chave em um Trie
void Trie::insert(string key, streampos pos)
{
    // inicia do nó raiz
    Trie* curr = this;
    for (int i = 0; i < key.length(); i++)
    {
        // cria um novo nó se o caminho não existir
        if (curr->character[key[i]] == nullptr) {
            curr->character[key[i]] = new Trie();
        }
 
        // vai para o próximo nó
        curr = curr->character[key[i]];
    }
 
    // marca o nodo atual como uma folha
    curr->isLeaf = true;
    curr->pos = pos; 
}
 
// Função iterativa para pesquisar uma chave em um Trie. Ele retorna verdadeiro
// se a chave for encontrada no Trie; caso contrário, retorna falso
Trie* Trie::search(string key)
{
    // retorna false se Trie estiver vazio
    if (this == nullptr) {
        return nullptr;
    }
 
    Trie* curr = this;
    for (int i = 0; i < key.length(); i++)
    {
        // vai para o próximo nó
        curr = curr->character[key[i]];
 
        // se a string for inválida (alcançou o final de um caminho no Trie)
        if (curr == nullptr) {
            return nullptr;
        }
    }
 
    // retorna true se o nó atual for uma folha e o
    // fim da string é atingido
    return curr;
}
 
// Retorna true se um determinado nó tiver algum filho
bool Trie::haveChildren(Trie const* curr)
{
    for (int i = 0; i < CHAR_SIZE; i++)
    {
        if (curr->character[i]) {
            return true;    // filho encontrado
        }
    }
 
    return false;
}
 
// Função recursivo para deletar uma chave no Trie
bool Trie::deletion(Trie*& curr, string key)
{
    // retorna se Trie estiver vazio
    if (curr == nullptr) {
        return false;
    }
 
    // se o final da chave não for alcançado
    if (key.length())
    {
        //recorre para o nó correspondente ao próximo caractere na chave
        // e se retornar verdadeiro, exclui o nó atual (se não for folha)
 
        if (curr != nullptr &&
            curr->character[key[0]] != nullptr &&
            deletion(curr->character[key[0]], key.substr(1)) &&
            curr->isLeaf == false)
        {
            if (!haveChildren(curr))
            {
                delete curr;
                curr = nullptr;
                return true;
            }
            else {
                return false;
            }
        }
    }
 
    // se o fim da chave for atingido
    if (key.length() == 0 && curr->isLeaf)
    {
        // se o nodo atual for um nodo folha e não tiver filhos
        if (!haveChildren(curr))
        {
            //deleta o nó atual
            delete curr;
            curr = nullptr;
 
            // exclui os nós pais não-folha
            return true;
        }
 
        // se o nodo atual for um nodo folha e tiver filhos
        else {
            // marca o nó atual como um nó não folha (DON'T DELETE IT)
            curr->isLeaf = false;
 
            // não exclui seus nós pais
            return false;
        }
    }
 
    return false;
}
 
// Implementação C++ da estrutura de dados Trie
int main()
{
    Trie* head = new Trie();
 
    head->insert("hello",2);
    cout << head->search("hello")->pos << " ";      // imprime 1
 
    head->insert("helloworld",4);
    cout << head->search("helloworld")->pos << " "; // imprime 1
 
    //cout << head->search("helll")->ID << " ";      // imprime 0 (Não encontrado)
 
    head->insert("hell",5);
    cout << head->search("hell")->pos << " ";       // imprime 1
 
    head->insert("h",6);
    cout << head->search("h")->pos;                 // imprime 1
 
    cout << endl;
 
 
    return 0;
}
