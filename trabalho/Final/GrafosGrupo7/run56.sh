#!/bin/bash
for alfa in 0.1 0.2 0.3; do
    x=0
    while [ $x -le 30 ]
    do
        if ! pgrep -x "GrafosGrupo7_56" > /dev/null
        then
            x=$(( $x + 1 ))
            echo "Execucao: $x alfa: $alfa  `date`" >> ../saidas/run56.txt
            clear && g++ -std=c++11 *.cpp -o GrafosGrupo7_56 && ./GrafosGrupo7_56 ../instancias/grandes/I056.stp ../saidas/I056.txt 0 0 1 14171206 11 5 $alfa
        else
            sleep 5
        fi
    done
done
