#ifndef RGBEXCEPTION_H
#define RGBEXCEPTION_H

#include <iostream>
#include <string.h>
using namespace std;

#include "Exception.h"

class RGBException : public Exception
{ 
    private:
        int valeur;
    
    public:       
        //Constructeurs :
        RGBException();//Par défaut
        RGBException(int v,string m); //D'initialisation
        RGBException(const RGBException &objet); //De copie
        
        //Getters :
        int getValeur() const; //Getter Valeur

        //Setters :
        void setValeur(int v); //Setter Message

        //Destructeur :
        ~RGBException();
};

#endif