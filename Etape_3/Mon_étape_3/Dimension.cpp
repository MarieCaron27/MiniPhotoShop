#include <iostream>
#include <ostream>
#include <string.h>
#include "Dimension.h"
using namespace std;

//Constructeurs :

Dimension::Dimension(const Dimension &objet) //Copie
{
    setLargeur(objet.largeur);
    setHauteur(objet.hauteur);
}

Dimension::Dimension(int l,int h) //Initialisation
{
    setLargeur(l);
    setHauteur(h);
}

Dimension::Dimension() //Par défaut
{
    setLargeur(400);
    setHauteur(300);
}

//Setters :

void Dimension::setLargeur(int l)
{
    if(l<0)
    {
        return;
    }
    
    largeur=l;
}

void Dimension::setHauteur(int h)
{
    if(h<0)
    {
        return;
    }
    
    hauteur=h;
}

//Getters :

int Dimension::getLargeur() const
{
    return largeur;
}

int Dimension::getHauteur() const
{
    return hauteur;
}

//Fonction d'affichage :

void Dimension::Affiche() const
{
    cout << "Largeur = " << getLargeur() << endl;
    cout << "Hauteur = " << getHauteur() << endl;
}

//Attribution des valeurs par défaut :

const Dimension Dimension::VGA = Dimension(640,480);
const Dimension Dimension::HD = Dimension(1280,720);
const Dimension Dimension::FULL_HD = Dimension(1920,1080);

//Accès fonction affiche ImageNG :

std::ostream& operator<<(std::ostream& os, const Dimension& dimension)
{
    os << "Largeur = " << dimension.getLargeur() << ", Hauteur = " << dimension.getHauteur();
    return os;
}