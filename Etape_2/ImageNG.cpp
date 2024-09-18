#include <iostream>
#include <string.h>
#include "ImageNG.h"
using namespace std;

//Constructeurs :

ImageNG::ImageNG(const ImageNG &objet) //Copie
{
    nom=NULL;
    setNom(objet.nom);
    setId(objet.id);
    setDimension(objet.getDimension());
}

ImageNG::ImageNG(int identifiant,const char *n) //Initialisation
{
    nom=NULL;
    setNom(n);
    setId(identifiant);
}

ImageNG::ImageNG() //Par défaut
{
    nom=NULL;
    setNom("Default");
    setId(1);
}

ImageNG::ImageNG(int identifiant,const char *n,const Dimension &d)
{
    nom=NULL;
    setId(identifiant);
    setNom(n);
    setDimension(d);
}

//Setters :

void ImageNG::setId(int identifiant)
{
    if(identifiant<0)
    {
        return;
    }
    
    id=identifiant;
}

void ImageNG::setNom(const char *n)
{
    if(n==NULL)
    {
        return;
    }
    
    if(nom!=NULL)
    {
        delete nom;
    }

    nom = new char[strlen(n)+1];
    strcpy(nom,n);
}

void ImageNG::setDimension(const Dimension &d)
{
    mesDimensions=d;
}

//Getters :

int ImageNG::getId() const
{
    return id;
}

const char* ImageNG::getNom() const
{
    return nom;
}

Dimension ImageNG::getDimension() const
{
    return mesDimensions;
}

//Destructeur :

ImageNG::~ImageNG()
{
    if (nom)
    {
        delete nom;
    }
}

//Fonction d'affichage :

void ImageNG::Affiche() const
{
    cout << "Identifiant = " << getId() << endl;
    cout << "Nom = " << getNom() << endl;
    cout << "Dimensions = " << getDimension();
}