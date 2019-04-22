#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

/**
Conversor de arquivos

LINHA DE COMANDO PRA RODAR:
clear && g++ conversor.cpp -o conversor && ./conversor
**/



int main(int argc, char *argv[])
{

    string nomeArquivoEntrada = "frb59-26-4.mis";
    string nomeArquivoSaida = "frb59-26-4.mis.txt";
    ifstream inFile;
    ofstream outFile;
    string line;
    string a, d;
    int b, c;


    //abre arquivo de entrada
    inFile.open(nomeArquivoEntrada.c_str());

    //abre arquivo para saida
    outFile.open(nomeArquivoSaida.c_str());

    //verifica se o arquivo foi aberto
    if (!inFile || !inFile.is_open())
    {
        cout << "Impossivel abrir o arquivo de entrada para leitura" << endl;
        exit(1); // sai do programa se nao conseguir abrir o arquivo
    }

    //le o arquivo linha por linha
    while (getline(inFile, line))
    {
        istringstream iss3(line);
        istringstream iss4(line);

        if (!(iss3 >> a >> b >> c))
        {
            if(a != "c"){
                cout << "a linha não tem 3 valores: " << line << endl;
            }

            if (!(iss4 >> a >> d >> b >> c))
            {
                if(a != "c"){
                    cout << "a linha não tem quatro valores: " << line << endl;
                }
            }
        }

        if(a == "p"){
            cout << a << " " << d << " " << b << " " << c << " " << endl;
            outFile << b << endl;
        }
        if(a == "e"){
            float peso = (rand() % 1000) / 5;
            outFile << b << " " << c << " " << peso << endl;
        }

    }

    outFile.close();
    inFile.close();

    return 0;
}

