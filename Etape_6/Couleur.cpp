#include <iostream>
#include <ostream>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "Couleur.h"
#include "Exception.h"
#include "XYException.h"
#include "RGBException.h"
using namespace std;

//Initialisation des variables membres statiques :

const Couleur Couleur::ROUGE(255, 0, 0);
const Couleur Couleur::VERT(0, 255, 0);
const Couleur Couleur::BLEU(0, 0, 255);
const Couleur Couleur::BLANC(255,255,255);
const Couleur Couleur::NOIR(0,0,0);

//Constructeurs :

Couleur::Couleur() //Par défaut
{
    setRouge(0);
    setVert(0);
    setBleu(0);
}

Couleur::Couleur(const Couleur &objet)//Copie
{
    setRouge(objet.rouge);
    setVert(objet.vert);
    setBleu(objet.bleu);
}

Couleur::Couleur(int r,int v,int b) //Initialisation
{
    setRouge(r);
    setVert(v);
    setBleu(b);
}

//Getters :

int Couleur::getRouge() const
{
    return rouge;
}

int Couleur::getVert() const
{
    return vert;
}

int Couleur::getBleu() const
{
    return bleu;
}

//Setters :

void Couleur::setRouge(int r) 
{
    if(r<0)
    {
        throw RGBException(r,"Composante couleur rouge incorrecte!");
    }

    if(r>255)
    {
        throw RGBException(r,"Composante couleur rouge incorrecte!");
    }

    rouge=r;
}

void Couleur::setVert(int v)
{
    if(v<0)
    {
        throw RGBException(v,"Composante couleur verte incorrecte!");
    }

    if(v>255)
    {
        throw RGBException(v,"Composante couleur verte incorrecte!");
    }

    vert=v;
}

void Couleur::setBleu(int b)
{
    if(b<0)
    {
        throw RGBException(b,"Composante couleur bleue incorrecte!");
    }

    if(b>255)
    {
        throw RGBException(b,"Composante couleur bleue incorrecte!");
    }

    bleu=b;
}

//Surcharge des opérateurs :

std::ostream& operator<<(std::ostream& os, const Couleur& c)
{
    os << "Nuance de rouge :" << c.getRouge() << ", Nuance de vert = " << c.getVert()
    << ", Nuance de bleu = " << c.getBleu() << endl;
    return os;
}

//Fonction d'affichage :

void Couleur::Affiche() const
{
    cout << "Nuance de rouge = " << getRouge() << endl;
    cout << "Nuance de vert = " << getVert() << endl;
    cout << "Nuance de bleu = " << getBleu() << endl;;
}