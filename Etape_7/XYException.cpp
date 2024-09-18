#include <iostream>
#include <ostream>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "XYException.h"
#include "MyQT.h"
using namespace std;

//Constructeurs :

XYException::XYException() //Par défaut
{
    #ifdef DEBUG
        cout << "Constructeur par défaut de la classe XYException" << endl;
    #endif

    setCoordonnee('x');
}

XYException::XYException(char c,string m) : Exception(m) //D'initialisation
{
    #ifdef DEBUG
        cout << "Constructeur d'initialisation de la classe XYException" << endl;
    #endif

    setCoordonnee(c);
}

XYException::XYException(const XYException &objet) : Exception(objet) //De copie
{
    #ifdef DEBUG
        cout << "Constructeur de copie de la classe XYException" << endl;
    #endif

    setCoordonnee(objet.coordonnee);
}

//Getters :

char XYException::getCoordonnee() const
{
    #ifdef DEBUG
        cout << "Méthode getCoordonnee() de la classe XYException" << endl;
    #endif

    return coordonnee;
}

//Setters :

void XYException::setCoordonnee(char c) 
{
    #ifdef DEBUG
        cout << "Méthode setCoordonnee() de la classe XYException" << endl;
    #endif

    coordonnee=c;

    if(coordonnee=='x')
    {
        throw XYException(coordonnee,"Erreur coordoonée pixel x");
    }
    
    if(coordonnee=='y')
    {
        throw XYException(coordonnee,"Erreur coordoonée pixel y");
    }
    
    if(coordonnee=='d')
    {
        throw XYException(coordonnee,"Erreur dimensions");
    }
}

//Destructeur :

XYException::~XYException()
{
    #ifdef DEBUG
        cout << "Destructeur de la classe XYException" << endl;
    #endif
}