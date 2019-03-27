#include "FileManager.h"

FileManager::FileManager(string filename)
{
    nomeArquivo = filename;
}

FileManager::~FileManager()
{
    cout << "Destruindo objeto FileSystem" << endl;
}

string FileManager::abrir(){
    cout << "nomeArquivo: " << nomeArquivo << endl;

    int sum = 0;
    int x;
    ifstream inFile;
    
    inFile.open(nomeArquivo);
    if (!inFile) {
        cout << "Impossivel abrir o arquivo";
        exit(1); // terminate with error
    }
    
    while (inFile >> x) {
        sum = sum + x;
    }
    
    inFile.close();
    cout << "Sum = " << sum << endl; 

    return "arquivo";
}

void FileManager::salvar(string conteudo){
    ofstream out; // out é uma variavel.
	out.open(nomeArquivo);
    if (!out) {
        cout << "Impossivel abrir o arquivo";
        exit(1); // terminate with error
    }
	out<<conteudo;  // saida de uma variavel
	out.close(); // nã oesqueça de fechar...
}