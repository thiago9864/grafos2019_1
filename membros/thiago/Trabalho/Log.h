#ifndef LOG_H
#define LOG_H
#include <iostream>
#include <string>

using namespace std;

class Log {
    public:
        //construtor
        Log(); 
        //destrutor
        ~Log();

        //metodos publicos
        void logString(string message);
        void logHeader(string title);
    private:
};

#endif // LOG_H