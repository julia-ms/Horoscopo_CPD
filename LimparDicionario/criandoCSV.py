import csv
import pathlib

f = open('teste.csv', 'w', newline='', encoding='utf-8')
strVar =''
teste = 0

listaClasses = ['abrev.','adj.','adv.','advers.','art.','auxil.','card.','caus.',
                'comp.','compar.','conj.','contr.','coord.','cop.','def.', 'dem.','det.','disj.',
                'elem.','fin.','frac.','g.','indef.','integr.','interj.','interr.',
                'intr.','loc.','mult.','num.','núm.','ord.','pess.','poss.','pref.',
                'prep.','pron.','rel.','s.','símb.','suf.','tr.','v.']
listaGeneros = [' f.',' m.']
listaNumero = [' pl.']


#if 'elem.' in listaClasses:
#    print("ta aquii")

with open("dicionario.txt", "r", encoding="utf8") as x:

    for lines in x:
        if lines != "\n": 
            strVar = strVar+ lines[0:-2]
            teste = 1
        else:
            if teste == 1:

                #separa palavra com ;
                #deixa varI no lugar do ;

                tamanho = len(strVar)
                varList = list(strVar)
                for i in range (tamanho):
                    if varList[i] == ' ':
                        varList[i] = ';'
                        varI = i
                        inicioClasse = i+1
                        break


                # separa o significado
                # apaga tudo que esta em modulo junto com a palavra (como falar)
                for i in range (varI,tamanho):
                    fimClasse = i; 
                    if varList[i] == '|':
                        aux = i+1
                        varList[i] = ''
                        while varList[aux] != '|':
                            varList[aux] = ''
                            aux = aux + 1
                        varList[aux] = ''
                        varList[aux+1] = ''


                            
                    if varList[i].isupper():
                        varList[i-1] = ';'
                        varI = i
                        break
                    if varList[i] == '1':
                        varList[i-1] = ';'
                        varI = i
                        break
                    if varList[i] == '[':
                        varList[i-1] = ';'
                        varI = i
                        break
                
                fimClasse = fimClasse-1
                
                if tamanho > fimClasse:
                    #ve se tem mais ; no resto do significado e troca por ,
                    for i in range (varI,tamanho):
                        if varList[i] == ';':
                            varList[i] = ','


                    #verificacoes só dentro da classe
                    #se eu acho um genero, so separo antes. pq se tiver mais genero depois, eles vem em seguida
                    temGen = 0
                    for i in range (inicioClasse, fimClasse-2):
                        aux = varList[i] + varList[i+1] + varList[i+2]

                        if (aux in listaGeneros):
                            if (i <= fimClasse):
                                temGen = 1
                                varList[i] = ';'
                                break
                    
                    if temGen == 0:
                        varList[fimClasse] = varList[fimClasse] + ';'


                    temNum = 0
                    for i in range (inicioClasse, fimClasse-3):
                        aux = varList[i] + varList[i+1] + varList[i+2] + varList[i+3]

                        if (aux in listaNumero):
                            if (i <= fimClasse):
                                temNum = 1 
                                varList[i] = ';'
                                break
                        
                    if temNum == 0:
                        varList[fimClasse] = varList[fimClasse] + ';'

                    for i in range (inicioClasse, fimClasse-2):
                        aux = varList[i] + varList[i+1] + varList[i+2]
                        if aux == ' e ':
                            varList[i] = ','
                            varList[i+1] = ''
                            varList[i+2] = ''

                        if varList[i] == ' ':
                            varList[i] = ','
                        

                    linhaPronta =  ''.join(varList)
                    f.write(linhaPronta + '\n')
                    strVar = ''
                    teste = 0
    


# tem 'e' no meio
# plural
# fem ou masc
# 2g
# 2 num
# apagar as classes que não estão na lista

