#ifndef LOG_H
#define LOG_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

class Log
{
    public:
        Log(string nomeArquivo);
        ~Log();

        void info(string message);
        void header(string title);
        void title(string title);
        stringstream ssLog;
        void logSSBuffer();
    private:
        string _nomeArquivo;
        ifstream inFile;
        ofstream outFile;
        void iniciaArquivo();
        void escreveNoArquivo(string conteudo);
};

#endif // LOG_H
