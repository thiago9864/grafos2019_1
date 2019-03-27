#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class FileManager {
    public:
        //construtor
        FileManager(string filename); 
        //destrutor
        ~FileManager();

        //metodos publicos
        string abrir();
        void salvar(string conteudo);
    private:
        string nomeArquivo;
};