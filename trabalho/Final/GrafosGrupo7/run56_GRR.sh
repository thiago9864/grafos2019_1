#!/bin/bash
x=0
while [ $x -le 7 ]
do
    if ! pgrep -x "GrafosGrupo7_56_GRR" > /dev/null
    then
        x=$(( $x + 1 ))
        echo "Execucao: $x `date`" >> ../saidas/run56_GRR.txt
        clear && g++ -std=c++11 *.cpp -o GrafosGrupo7_56_GRR && ./GrafosGrupo7_56_GRR ../instancias/grandes/I056.stp ../saidas/I056.txt 0 0 1 14171206 12 5
    else
        sleep 5
    fi
done
