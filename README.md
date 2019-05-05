# Trabalho Grafos
Trabalho para a disciplina de Grafos 2019.1 da UFJF

Membros: Gabriele Cesar, Laura Polverari, Thiago Almeida, Victor Aquiles

#Linha de comando usada nos testes
Certificar que o terminal está na pasta trabalho/grafosGrupo7.

Parâmetros de execução:
./grafosGrupo7 <arq entrada> <arq saida> <direcionado> <ponderadoVertice> <ponderadoAresta>

Descrição:
<arq entrada>       = Caminho do arquivo contendo a instancia
<arq saida>         = Caminho do arquivo com os logs de saída
<direcionado>       = 1: Sim, 0: Não (opcional, Não por padrão)
<ponderadoVertice>  = 1: Sim, 0: Não (opcional, Não por padrão)
<ponderadoAresta>   = 1: Sim, 0: Não (opcional, Sim por padrão)

Linhas de comando:
UNIX (macOS / Linux): clear && g++ -std=c++11 *.cpp -o grafosGrupo7 && ./grafosGrupo7 ../data/entrada_conexas.txt ../data/saida.txt 0 0 1
