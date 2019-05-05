#include "Log.h"

Log::Log(string nomeArquivo)
{
    //construtor
    _nomeArquivo = nomeArquivo;
    iniciaArquivo();
}

Log::~Log()
{
    //destrutor
}


void Log::info(string message)
{
    string conteudo = message + "\n";
    escreveNoArquivo(conteudo);
    cout << conteudo;
}
void Log::header(string title)
{
    string conteudo = "**** " + title + " ****\n";
    escreveNoArquivo(conteudo);
    cout << conteudo;
}
void Log::title(string title)
{
    string conteudo = "**** " + title + " ****\n\n";
    escreveNoArquivo(conteudo);
    cout << conteudo;
}
void Log::logSSBuffer(){
    string conteudo = ssLog.str();
    escreveNoArquivo(conteudo);
    cout << conteudo;
    ssLog.str(std::string());
}

void Log::iniciaArquivo()
{

    //abre arquivo para saida
    outFile.open(_nomeArquivo.c_str());

    //verifica se o arquivo foi aberto
    if (!outFile || !outFile.is_open())
    {
        info("Impossivel abrir o arquivo de saida para escrita");
        exit(1); // sai do programa se nao conseguir abrir o arquivo
    }

    //grava o arquivo
    outFile << "Inicio\n\n";

	outFile.close();
}

void Log::escreveNoArquivo(string conteudo)
{
    string arquivo, line;

    //abre o arquivo para entrada
    inFile.open(_nomeArquivo.c_str());

    //verifica se o arquivo foi aberto
    if (!inFile || !inFile.is_open())
    {
        info("Impossivel abrir o arquivo de saida para leitura");
        exit(1); // sai do programa se nao conseguir abrir o arquivo
    }

    //faz a leitura
    while (getline(inFile, line))
    {
        arquivo += line + "\n";
    }

    inFile.close();

    //abre arquivo para saida
    outFile.open(_nomeArquivo.c_str());

    //verifica se o arquivo foi aberto
    if (!outFile || !outFile.is_open())
    {
        info("Impossivel abrir o arquivo de saida para escrita");
        exit(1); // sai do programa se nao conseguir abrir o arquivo
    }

    //adiciona o novo conteudo
    arquivo += conteudo;

    //grava o arquivo
    outFile << arquivo;

	outFile.close();
}
