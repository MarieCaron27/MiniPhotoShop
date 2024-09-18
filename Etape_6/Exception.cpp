#include <iostream>
#include <ostream>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "Exception.h"
#include "MyQT.h"
using namespace std;

//Constructeurs :

Exception::Exception() //Par défaut
{
    #ifdef DEBUG
        cout << "Constructeur par défault de la classe Exception" << endl;
    #endif

    setMessage("Il y a un problème.");
}

Exception::Exception(string m) //D'initialisation
{
    #ifdef DEBUG
        cout << "Constructeur d'initialisation de la classe Exception" << endl;
    #endif

    setMessage(m);
}

Exception::Exception(const Exception &objet) //De copie
{
    #ifdef DEBUG
        cout << "Constructeur de copie de la classe Exception" << endl;
    #endif

    setMessage(objet.message);
}

//Getters :

string Exception::getMessage() const
{
    #ifdef DEBUG
        cout << "Méthode getMessage de la classe Exception" << endl;
    #endif

    return message;
}

//Setters :

void Exception::setMessage(string m)
{
    #ifdef DEBUG
        cout << "Méthode setMessage de la classe Exception" << endl;
    #endif

    message=m;
}

//Destructeur :

Exception::~Exception()
{
    #ifdef DEBUG
        cout << "Destructeur de la classe Exception" << endl;
    #endif
}