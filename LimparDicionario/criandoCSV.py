import csv
import pathlib

f = open('PalavraPorLinha.csv', 'w', newline='', encoding='utf-8')
strVar =''
teste = 0
with open("dicionario.txt", "r", encoding="utf8") as x:
    for lines in x:
        if lines != "\n": 
            strVar = strVar+ lines[0:-2]
            teste = 1
        else:
            if teste == 1:
<<<<<<< Updated upstream
                #if strVar == ' ':
                    
                print(strVar + '\n')
                f.write(strVar + '\n')
=======
                tamanho = len(strVar)
                varList = list(strVar)
                for i in range (tamanho):
                    if varList[i] == ' ':
                        varList[i] = ','
                        break
                linhaPronta =  ''.join(varList)
                print(linhaPronta)
                f.write(linhaPronta + '\n')
>>>>>>> Stashed changes
                strVar = ''
                teste = 0

