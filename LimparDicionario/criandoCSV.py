import csv
import pathlib

f = open('teste.csv', 'w', newline='', encoding='utf-8')
strVar =''
teste = 0
with open("texto.txt", "r", encoding="utf8") as x:
    for lines in x:
        if lines != "\n": 
            strVar = strVar+ lines[0:-2]
            teste = 1
        else:
            if teste == 1:
                #print(strVar + '\n')
                #list(strVar)
                tamanho = len(strVar)
                varList = list(strVar)
                for i in range (tamanho):
                    if varList[i] == ' ':
                        varList[i] = ','
                        break
                #print(frog)
                linhaPronta =  ''.join(varList)
                print(linhaPronta)
                #print(frog[4:7])
                #frog[4:5] = 'a'
                #print(frog[4:5])
                f.write(linhaPronta + '\n')
                strVar = ''
                teste = 0
    # while lines != :
    #     lines = x.readline()
    #     print (lines)
        
    #     if lines == "\n":
    #         lines = x.readline()