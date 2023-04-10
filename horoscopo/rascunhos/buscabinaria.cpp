#include <fstream>
#include <iostream>

using namespace std;

struct Entry {
    string entryWord;
    streampos pos;
    int ID;
};

// Função de comparação para busca binária
bool compareID(const Entry& a, const Entry& b) {
    return a.ID < b.ID;
}

// Função de busca binária por ID
streampos binarySearchByID(ifstream& file, int targetID) {
    // Verifica o tamanho do arquivo
    file.seekg(0, ios::end);
    streampos fileSize = file.tellg();

    // Define os limites da busca
    streampos low = 0;
    streampos high = fileSize / sizeof(Entry) - 1;

    while (low <= high) {
        // Calcula o meio do intervalo
        streampos mid = (low + high) / 2;

        // Posiciona o ponteiro no registro do meio
        file.seekg(mid * sizeof(Entry));
        Entry midEntry;
        file.read(reinterpret_cast<char*>(&midEntry), sizeof(Entry));

        // Compara o ID do registro do meio com o ID-alvo
        if (midEntry.ID == targetID) {
            // Encontrou o registro, retorna a posição dele no arquivo
            return midEntry.pos;
        } else if (compareID(midEntry, { "", 0, targetID })) {
            // O ID-alvo é maior que o ID do registro do meio,
            // portanto a busca deve continuar na metade superior do intervalo
            low = mid + 1;
        } else {
            // O ID-alvo é menor que o ID do registro do meio,
            // portanto a busca deve continuar na metade inferior do intervalo
            high = mid - 1;
        }
    }

    // Não encontrou o registro, retorna -1
    return -1;
}

int main() {
    // Abre o arquivo para leitura binária
    ifstream file("entries.bin", ios::binary);
    if (!file.is_open()) {
        cerr << "Erro ao abrir arquivo" << endl;
        return 1;
    }

    // Faz a busca binária pelo registro com ID 42
    streampos pos = binarySearchByID(file, 42);

    if (pos == -1) {
        cout << "Registro não encontrado" << endl;
    } else {
        cout << "Registro encontrado na posição " << pos << endl;
    }

    // Fecha o arquivo
    file.close();

    return 0;
}



#include <fstream>
#include <iostream>

using namespace std;

struct Entry {
    string entryWord;
    streampos pos;
    int ID;
};

// Função de comparação para busca binária
bool compare(const Entry& a, const Entry& b) {
    return a.entryWord < b.entryWord;
}

// Função de busca binária
streampos binarySearch(ifstream& file, const string& targetWord) {
    // Verifica o tamanho do arquivo
    file.seekg(0, ios::end);
    streampos fileSize = file.tellg();

    // Define os limites da busca
    streampos low = 0;
    streampos high = fileSize / sizeof(Entry) - 1;

    while (low <= high) {
        // Calcula o meio do intervalo
        streampos mid = (low + high) / 2;

        // Posiciona o ponteiro no registro do meio
        file.seekg(mid * sizeof(Entry));
        Entry midEntry;
        file.read(reinterpret_cast<char*>(&midEntry), sizeof(Entry));

        // Compara a palavra-chave do registro do meio com a palavra-alvo
        if (midEntry.entryWord == targetWord) {
            // Encontrou o registro, retorna a posição dele no arquivo
            return midEntry.pos;
        } else if (compare(midEntry, {targetWord, 0, 0})) {
            // A palavra-alvo é maior que a palavra-chave do registro do meio,
            // portanto a busca deve continuar na metade superior do intervalo
            low = mid + 1;
        } else {
            // A palavra-alvo é menor que a palavra-chave do registro do meio,
            // portanto a busca deve continuar na metade inferior do intervalo
            high = mid - 1;
        }
    }

    // Não encontrou o registro, retorna -1
    return -1;
}

int main() {
    // Abre o arquivo para leitura binária
    ifstream file("entries.bin", ios::binary);
    if (!file.is_open()) {
        cerr << "Erro ao abrir arquivo" << endl;
        return 1;
    }

    // Faz a busca binária pela palavra "hello"
    streampos pos = binarySearch(file, "hello");

    if (pos == -1) {
        cout << "Registro não encontrado" << endl;
    } else {
        cout << "Registro encontrado na posição " << pos << endl;
    }

    // Fecha o arquivo
    file.close();

    return 0;
}
