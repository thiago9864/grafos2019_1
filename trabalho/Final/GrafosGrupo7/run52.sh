#!/bin/bash
for alfa in 0.1 0.2 0.3; do
    x=0
    if ! pgrep -x "GrafosGrupo7_52" > /dev/null
    then
        x=$(( $x + 1 ))
        echo "Execucao: $x alfa: $alfa  `date`" >> ../saidas/run52.txt
        clear && g++ -std=c++11 *.cpp -o GrafosGrupo7_52 && ./GrafosGrupo7_52 ../instancias/grandes/I052.stp ../saidas/I052.txt 0 0 1 13309487 11 5 $alfa
    else
        sleep 5
    fi
done
