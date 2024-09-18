#include <iostream>
#include <string.h>
#include "ImageNG.h"
using namespace std;

//Constructeurs :

ImageNG::ImageNG(const ImageNG &objet) //Copie
{
    int i,j;

    nom=NULL;
    setNom(objet.nom);
    setId(objet.id);
    setDimension(objet.getDimension());

    for(i=0;i<mesDimensions.getLargeur();i++)
    {
        for(j=0;j<mesDimensions.getHauteur();j++)
        {
            matrice[i][j] = objet.matrice[i][j];
        }
    }
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

ImageNG::ImageNG(int identifiant,const char *n,const Dimension &d,int m[L_MAX][H_MAX])
{
    int i,j;

    nom=NULL;
    setId(identifiant);
    setNom(n);
    setDimension(d);

    for(i=0;i<mesDimensions.getLargeur();i++)
    {
        for(j=0;j<mesDimensions.getHauteur();j++)
        {
            matrice[i][j] = m[i][j];
        }
    }
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

void ImageNG::setPixel(int x,int y,int val)
{
    if(x<=0 || x>L_MAX)
    {
        return;
    }

    if(y<=0 || y>H_MAX)
    {
        return;
    }

    if(val<0 || val>255)
    {
        return;
    }
}

void ImageNG::setBackground(int val)
{
    int i,j;

    for(i=0;i<mesDimensions.getLargeur();i++)
    {
        for(j=0;j<mesDimensions.getHauteur();j++)
        {
            matrice[i][j]=val;
        }
    }
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

int ImageNG::getPixel(int x,int y) const
{
    return x;
    return y;
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

//Fonction Dessine :

ImageNG::Dessine()
{
    MyQT::ViewImage(this->image);
}

//Méthodes d'importation et d'exportation des fichiers :

ImageNG::importFromFile()
{
    MyQT::ImportFromFile(this->image,this->fichier);
}

ImageNG::exportToFile()
{
    MyQT::ExportToFile(this->image,this->fichier);
}