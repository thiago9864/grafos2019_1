#!/bin/bash
x=0
while [ $x -le 7 ]
do
    if ! pgrep -x "GrafosGrupo7_52_GRR" > /dev/null
    then
        x=$(( $x + 1 ))
        echo "Execucao: $x `date`" >> ../saidas/run52_GRR.txt
        clear && g++ -std=c++11 *.cpp -o GrafosGrupo7_52_GRR && ./GrafosGrupo7_52_GRR ../instancias/grandes/I052.stp ../saidas/I052.txt 0 0 1 13309487 12 5
    else
        sleep 5
    fi
done
