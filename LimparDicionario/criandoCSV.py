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

with open("texto.txt", "r", encoding="utf8") as x:
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
                for i in range (varI,tamanho):
                    if varList[i].isupper():
                        varList[i-1] = ';'
                        break
                    if varList[i] == '1':
                        varList[i-1] = ';'
                        break
                    if varList[i] == '[':
                        varList[i-1] = ';'
                        break
                    
                
                linhaPronta =  ''.join(varList)
                print(linhaPronta)
                f.write(linhaPronta + '\n')
                strVar = ''
                teste = 0
   