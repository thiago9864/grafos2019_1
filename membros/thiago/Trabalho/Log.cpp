#include "Log.h"

Log::Log()
{
    //construtor
}

Log::~Log()
{
    //destrutor
}


void Log::logString(string message){
    cout << message << endl;
}
void Log::logHeader(string title){
    cout << endl << "**** " << title << " ****" << endl;
}