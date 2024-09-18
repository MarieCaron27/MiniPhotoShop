#ifndef XYEXCEPTION_H
#define XYEXCEPTION_H

#include "Exception.h"

#include <iostream>
#include <string.h>
using namespace std;

class XYException : public Exception
{ 
    private:
        char coordonnee;
    
    public:       
        //Constructeurs :
        XYException();//Par défaut
        XYException(char c,string m); //D'initialisation
        XYException(const XYException &objet); //De copie
        
        //Getters :
        char getCoordonnee() const; //Getter Coordonnee

        //Setters :
        void setCoordonnee(char c); //Setter Coordonnee

        //Destructeur :
        ~XYException();
};

#endif