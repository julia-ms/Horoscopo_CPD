#include "bib.h"

using namespace std;
/*
struct Word {
    int ID; 
    string palavra; 
    string classe;
    string genero;
    string numero;  
    string significado; 
}; 
*/
int invertido() {

    int linha_desejada = 5;
    int linha_atual = 1;

    char classe[50];
    int id;


    fstream arquivo_dicionario("dictionary.bin", ios::in | ios::binary);
    Word pWord;
    int ID;

    if (!arquivo_dicionario.is_open()) {
        cout << "deu ruim";
        return 1;  
    }

    while (arquivo_dicionario.read((char*)&pWord.ID, sizeof(int))){  

        getline(arquivo_dicionario, pWord.palavra, '\0');
        getline(arquivo_dicionario, pWord.classe, '\0');
        getline(arquivo_dicionario, pWord.genero, '\0');
        getline(arquivo_dicionario, pWord.numero, '\0');
        getline(arquivo_dicionario, pWord.significado, '\0');

        cout << "Palavra: " << pWord.palavra << endl;
        cout << "Classe: " << pWord.classe << endl;
        cout << "ID: " << pWord.ID << endl;
        cout << endl;

        ifstream arquivo_inv("arqinvertido.csv");
        //ofstream arquivo_temporario("temp.csv");
/*
        cin >> classe;
        cin >> id;
*/
        string auxclasse = pWord.classe;
        const char* auxchar = auxclasse.c_str();

        if(strcmp(auxchar, "adj")==0) linha_desejada = 1;
        if(strcmp(auxchar, "adj.,num.")==0) linha_desejada = 2;
        if(strcmp(auxchar, "adj.,num.,frac.,s.")==0) linha_desejada = 3;
        if(strcmp(auxchar, "adj.,num.,mult.")==0) linha_desejada = 4;
        if(strcmp(auxchar, "adj.,pron.,adv.")==0) linha_desejada = 5;
        if(strcmp(auxchar, "adj.,s.")==0) linha_desejada = 6;
        if(strcmp(auxchar, "adv.")==0) linha_desejada = 7;
        if(strcmp(auxchar, "adv.,interr.")==0) linha_desejada = 8;
        if(strcmp(auxchar, "adv.,s.")==0) linha_desejada = 9;
        if(strcmp(auxchar, "al.,abrev.")==0) linha_desejada = 10;
        if(strcmp(auxchar, "art.,def.")==0) linha_desejada = 11;
        if(strcmp(auxchar, "conj.")==0) linha_desejada = 12;
        if(strcmp(auxchar, "conj.,concess.")==0) linha_desejada = 13;
        if(strcmp(auxchar, "conj.,coord.")==0) linha_desejada = 14;
        if(strcmp(auxchar, "conj.,disj.")==0) linha_desejada = 15;
        if(strcmp(auxchar, "contr.")==0) linha_desejada = 16;
        if(strcmp(auxchar, "det.,pron.,dem.")==0) linha_desejada = 17;
        if(strcmp(auxchar, "det.,pron.,indef.")==0) linha_desejada = 18;
        if(strcmp(auxchar, "det.,pron.,poss.")==0) linha_desejada = 19;
        if(strcmp(auxchar, "ex.,abrev.")==0) linha_desejada = 20;
        if(strcmp(auxchar, "interj.")==0) linha_desejada = 21;
        if(strcmp(auxchar, "interj.,s.")==0) linha_desejada = 22;
        if(strcmp(auxchar, "m.,abrev.")==0) linha_desejada = 23;
        if(strcmp(auxchar, "pref.")==0) linha_desejada = 24;
        if(strcmp(auxchar, "prep.")==0) linha_desejada = 25;
        if(strcmp(auxchar, "pron.")==0) linha_desejada = 26;
        if(strcmp(auxchar, "pron.,dem.")==0) linha_desejada = 27;
        if(strcmp(auxchar, "pron.,indef.")==0) linha_desejada = 28;
        if(strcmp(auxchar, "pron.,indef.,s.")==0) linha_desejada = 29;
        if(strcmp(auxchar, "pron.,interr.")==0) linha_desejada = 30;
        if(strcmp(auxchar, "pron.,pess.")==0) linha_desejada = 31;
        if(strcmp(auxchar, "pron.,poss.")==0) linha_desejada = 32;
        if(strcmp(auxchar, "pron.,rel.")==0) linha_desejada = 33;
        if(strcmp(auxchar, "s.")==0) linha_desejada = 34;
        if(strcmp(auxchar, "v.")==0) linha_desejada = 35;
        if(strcmp(auxchar, "símb.")==0) linha_desejada = 36;
        if(strcmp(auxchar, "suf.")==0) linha_desejada = 37;
        if(strcmp(auxchar, "v.")==0) linha_desejada = 38;
        if(strcmp(auxchar, "v.,cop.")==0) linha_desejada = 39;
        if(strcmp(auxchar, "v.,intr.")==0) linha_desejada = 40;
        if(strcmp(auxchar, "v.,intr.,pron.")==0) linha_desejada = 41;
        if(strcmp(auxchar, "v.,pron.")==0) linha_desejada = 42;
        if(strcmp(auxchar, "v.,s.")==0) linha_desejada = 43;
        if(strcmp(auxchar, "v.,tr.")==0) linha_desejada = 44;
        if(strcmp(auxchar, "v.,tr.,,intr.,pron.")==0) linha_desejada = 45;
        if(strcmp(auxchar, "v.,tr.,intr.")==0) linha_desejada = 46;
        if(strcmp(auxchar, "v.,tr.,pron.")==0) linha_desejada = 47;
        




        vector<string>lines;
        string line;

        while (getline(arquivo_inv, line)){
            lines.push_back(line);
        }

        arquivo_inv.close();

        ofstream arquivo_inv2("arqinvertido.csv");

        if(arquivo_inv2.fail()){
            cout << "error aa" << endl;
            return 1;
        }

        linha_desejada--;

        for(int i = 0; i < lines.size(); i++){
            if(i != linha_desejada) arquivo_inv2 << lines[i] << endl;
            else arquivo_inv2 << lines[i] << ";" << pWord.ID << endl;
        }
    }
    
    return 0;
}

/*

linha 1: adj
linha 2: adj.,num.
linha 3: adj.,num.,frac.,s.
linha 4: adj.,num.,mult.
linha 5: adj.,pron.,adv.
linha 6: adj.,s.
linha 7: adv.
linha 8: adv.,interr.
linha 9: adv.,s.
linha 10: al.,abrev.
linha 11: art.,def.
linha 12: conj.
linha 13: conj.,concess. 
linha 14: conj.,coord.
linha 15: conj.,disj.
linha 16: contr.
linha 17: det.,pron.,dem.
linha 18: det.,pron.,indef.
linha 19: det.,pron.,poss.
linha 20: ex.,abrev.
linha 21: interj.
linha 22: interj.,s.
linha 23: m.,abrev.
linha 24: pref.
linha 25: prep.
linha 26: pron.
linha 27: pron.,dem.
linha 28: pron.,indef.
linha 29: pron.,indef.,s.
linha 30: pron.,interr.
linha 31: pron.,pess.
linha 32: pron.,poss.
linha 33: pron.,rel.
linha 34: s.
linha 35: sigla
linha 36: símb.
linha 37: suf.
linha 38: v.
linha 39: v.,cop.
linha 40: v.,intr.
linha 41: v.,intr.,pron.
linha 42: v.,pron.
linha 43: v.,s.
linha 44: v.,tr.
linha 45: v.,tr.,,intr.,pron.
linha 46: v.,tr.,intr.
linha 47: v.,tr.,pron.  

*/