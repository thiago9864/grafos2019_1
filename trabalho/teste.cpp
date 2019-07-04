#include <iostream>
#include <string>

using namespace std;
class Teste {
    public:
        Teste(){}
        string getValor(){return valorqualquer;}
    private:
        string valorqualquer="123";

};
int main(int argc, char *argv[])
{
    Teste *teste1 = new Teste();

    cout << teste1->getValor() << endl;

    delete teste1;
    if(teste1 == nullptr){
        cout << "Teste é nulo? Sim" << endl;
    } else {
        cout << "Teste é nulo? Não" << endl;
    }
    
    cout << teste1->getValor() << endl;

    cout << "tamanho: " << sizeof(teste1) << endl;
    cout << "tamanho*: " << sizeof(*teste1) << endl;

    return 0;
}