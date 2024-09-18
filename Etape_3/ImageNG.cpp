#include <iostream>
#include <string.h>
#include "ImageNG.h"
#include "MyQT.h"
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
    int i,j;

    nom=NULL;
    setNom(n);
    setId(identifiant);
}

ImageNG::ImageNG() //Par défaut
{
    int i,j;

    nom=NULL;
    setNom("Default");
    setId(1);
}

ImageNG::ImageNG(int identifiant,const char *n,const Dimension &d)
{
    int i,j;

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
    int x,y;

    mesDimensions.setLargeur(d.getLargeur());
    mesDimensions.setHauteur(d.getHauteur());
}

void ImageNG::setPixel(int x,int y,int val)
{
    matrice[x][y]=val;
}

void ImageNG::setBackground(int val)
{
    int i,j;

    for(i=0;i<mesDimensions.getLargeur();i++)
    {
        for(j=0;j<mesDimensions.getHauteur();j++)
        {
            setPixel(i,j,val);
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
    return matrice[x][y];
}

//Destructeur :

ImageNG::~ImageNG()
{
    int i,j;

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

void ImageNG::Dessine()
{
    MyQT myqt;
    
    myqt.ViewImage(*this);
}

//Méthodes d'importation et d'exportation des fichiers :

void ImageNG::importFromFile(const char *fichier)
{
    MyQT myqt;

    myqt.ImportFromFile(*this,fichier);
}

void ImageNG::exportToFile(const char* fichier, const char* format)
{
    MyQT myqt;

    myqt.ExportToFile(*this,fichier,format);
}