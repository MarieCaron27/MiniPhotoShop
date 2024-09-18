#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <string.h>
using namespace std;

class Exception
{ 
    protected:
        string message;
    
    public:       
        //Constructeurs :
        Exception();//Par défaut
        Exception(string m); //D'initialisation
        Exception(const Exception &objet); //De copie
        
        //Getters :
        string getMessage() const; //Getter Message

        //Setters :
        void setMessage(string m); //Setter Message

        //Destructeur :
        virtual ~Exception();
};

#endif