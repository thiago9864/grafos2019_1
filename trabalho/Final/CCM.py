import subprocess
import time
print("Tentando rodar um exe...")

#executavel
diretorio = 'c:\\Users\\Thiago\\Documents\\Repositorios\\UFJF\\grafos2019_1\\trabalho\Final\\GrafosGrupo7\\bin\Debug\\'
arquivo = diretorio + 'GrafosGrupo7.exe'

#Argumentos
diretorio_instancia = 'instancias\\pequenas\\'
arq_instancia = diretorio_instancia + 'cc3-10p.stp'
diretorio_saida = 'saidas\\'
arq_saida = diretorio_saida + 'cc3-10p.txt'
direcionado = '0'
ponderado_no = '0'
ponderado_aresta = '1'
best = '12772'

comando = [arquivo, arq_instancia, arq_saida, direcionado, ponderado_no, ponderado_aresta, best]
'''
input_cin = b'13\n'
p = subprocess.call()
#time.sleep(3)
p.stdin.write(input_cin)
'''
process = subprocess.Popen(comando, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
process.stdin.write(b"13\n")
print (process.communicate()[0])
process.stdin.close()