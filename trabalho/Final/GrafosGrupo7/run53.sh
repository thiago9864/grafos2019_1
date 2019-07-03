#!/bin/bash
for alfa in 0.1 0.2 0.3; do
    x=0
    while [ $x -le 30 ]
    do
        if ! pgrep -x "GrafosGrupo7_53" > /dev/null
        then
            x=$(( $x + 1 ))
            echo "Execucao: $x alfa: $alfa  `date`" >> ../saidas/run53.txt
            clear && g++ -std=c++11 *.cpp -o GrafosGrupo7_53 && ./GrafosGrupo7_53 ../instancias/grandes/I053.stp ../saidas/I053.txt 0 0 1 30854904 11 5 $alfa
        else
            sleep 5
        fi
    done
done
