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
                #if strVar == ' ':
                    
                print(strVar + '\n')
                f.write(strVar + '\n')
                strVar = ''
                teste = 0
    # while lines != :
    #     lines = x.readline()
    #     print (lines)
        
    #     if lines == "\n":
    #         lines = x.readline()
