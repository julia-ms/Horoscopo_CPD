# Trabalho-Final-CPD-
Trabalho Final da cadeira de Classificação e Pesquisa de dados, do 3º  semestre de Engenharia de Computação da Universidade Federal do Rio Grande do Sul. 

O trabalho consiste em um gerador de frases aleatórias, inserindo palavras sorteadas do dicionário em modelos pré definidos de frases. Para isso, foi feita a limpeza dos dados em Python, nos deixando com um aquivo csv com o seguinte modelo: 
>palavra;classe;genero;numero;significado

Então, foi feito o programa em C++ com as seguintes funções:
- Gerar horoscopo do dia
- Inserir palavra nova no banco de dados
- Excluir palavra do banco de dados
- Listar todas as palavras do banco de dados em ordem alfabética
- Listar todas as palavras do banco de dados em ordem inversa à alfabética
- Ver significado de uma palavra

Para isso, armazenamos structs em arquivos binários contendo ID, palavra, classe, gênero, número, significado e um boolean para saber se a palavra está deletada ou não. Também criamos arquivos invertidos de classes que foram usados como índices para o trabalho e indexam as palavras. São arquivos binários que contém structs com a palavra, ID e endereço da struct no arquivo binário principal. Além disso, foi gerado um arquivo binário que contém a estrutura TRIE, árvore utilizada para pesquisa em nosso dicionário. 

Para rodá-lo, é necessário rodar a função para refazer a árvore TRIE, o que pode demorar!
