import csv
import pathlib

f = open('teste.csv', 'w', newline='', encoding='utf-8')
strVar =''
teste = 0


listaClasses = ['abrev.','adj.','adv.','advers.','art.','auxil.','card.','caus.',
                'comp.','compar.','conj.','contr.','coord.','cop.','def.', 'dem.','det.','disj.',
                'elem.','f.','fin.','frac.','g.','indef.','integr.','interj.','interr.',
                'intr.','loc.','m.','mult.','num.','núm.','ord.','pess.','pl.','poss.','pref.',
                'prep.','pron.','rel.','s.','símb.','suf.','tr.','v.']


#if 'elem.' in listaClasses:
#    print("ta aquii")

with open("dicionario.txt", "r", encoding="utf8") as x:
    for lines in x:
        if lines != "\n": 
            strVar = strVar+ lines[0:-2]
            teste = 1
        else:
            if teste == 1:

                tamanho = len(strVar)
                varList = list(strVar)
                for i in range (tamanho):
                    if varList[i] == ' ':
                        varList[i] = ';'
                        varI = i
                        break

                # separa o significado 
                for i in range (varI,tamanho):
                    if varList[i] == '|':
                        aux = i+1
                        varList[i] = ''
                        while varList[aux] != '|':
                            varList[aux] = ''
                            aux = aux + 1
                        varList[aux] = ''

                            
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
                

                #ve se tem mais ; no resto do significado e troca por ,
                for i in range (varI,tamanho):
                    if varList[i] == ';':
                        varList[i] = ','
                    
                
                linhaPronta =  ''.join(varList)
                print(linhaPronta)
                f.write(linhaPronta + '\n')
                strVar = ''
                teste = 0
   

# tem 'e' no meio
# plural
# fem ou masc
# 2g
# 2 num
# apagar as classes que não estão na lista