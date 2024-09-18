#include <iostream>
#include <ostream>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "RGBException.h"
#include "MyQT.h"
using namespace std;

//Constructeurs :

RGBException::RGBException() //Par défaut
{
    #ifdef DEBUG
        cout << "Constructeur par défaut de la classe RGBException" << endl;
    #endif

    setValeur(-1);
}

RGBException::RGBException(int v,string m) : Exception(m) //D'initialisation
{
    #ifdef DEBUG
        cout << "Constructeur d'initialisation de la classe RGBException" << endl;
    #endif

    setValeur(v);
}

RGBException::RGBException(const RGBException &objet) : Exception(objet) //De copie
{
    #ifdef DEBUG
        cout << "Constructeur de copie de la classe RGBException" << endl;
    #endif

    setValeur(objet.valeur);
}

//Getters :

int RGBException::getValeur() const
{
    #ifdef DEBUG
        cout << "Méthode getValeur de la classe RGBException" << endl;
    #endif

    return(valeur);
}

//Setters :

void RGBException::setValeur(int v)
{
    #ifdef DEBUG
        cout << "Méthode setValeur de la classe RGBException" << endl;
    #endif

    if(v<0)
    {
        throw RGBException();
    }

    if(v>255)
    {
        throw RGBException();
    }

    valeur=v;

}

//Destructeur :

RGBException::~RGBException()
{
    #ifdef DEBUG
        cout << "Destructeur de la classe RGBException" << endl;
    #endif
}