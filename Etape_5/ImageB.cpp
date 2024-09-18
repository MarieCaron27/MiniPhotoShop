#include <iostream>
#include <ostream>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "ImageB.h"
#include "MyQT.h"
using namespace std;

//Initialisation des variables membres statiques :

Couleur ImageB::couleurTrue(255,255,255);
Couleur ImageB::couleurFalse(0,0,0);

//Constructeurs :

ImageB::ImageB(const ImageB &objet) : Image(objet)//Copie
{
    int i,j;

    #ifdef DEBUG
        cout << "Constructeur de copie de la classe ImageB" << endl;
    #endif

    for(i=0;i<mesDimensions.getLargeur();i++)
    {
        for(j=0;j<mesDimensions.getHauteur();j++)
        {
            matrice[i][j] = objet.matrice[i][j];
        }
    }
}

ImageB::ImageB(int identifiant,const char *n) : Image(identifiant,n)//Initialisation
{
    #ifdef DEBUG
        cout << "Constructeur d'initialisation de la classe ImageB" << endl;
    #endif
}

ImageB::ImageB() //Par défaut
{
    #ifdef DEBUG
        cout << "Constructeur par défault de la classe ImageB" << endl;
    #endif
}

ImageB::ImageB(int identifiant,const char *n,const Dimension &d) : Image(identifiant,n,d)
{
    #ifdef DEBUG
        cout << "Constructeur d'intialisation complet de la classe ImageB" << endl;
    #endif
}

ImageB::ImageB(const char *n)
{
    #ifdef DEBUG
        cout << "Constructeur d'initialisation du nom de la classe ImageB" << endl;
    #endif
}

//Getters :

bool ImageB::getPixel(int x,int y) const
{
    #ifdef DEBUG
        cout << "Méthode getPixel de la classe ImageB" << endl;
    #endif

    return matrice[x][y];
}

//Setters : 

void ImageB::setPixel(int x,int y,bool valeur)
{
    #ifdef DEBUG
        cout << "Méthode setPixel de la classe ImageB" << endl;
    #endif

    matrice[x][y]=valeur;
}

void ImageB::setBackground(bool valeur)
{
    #ifdef DEBUG
        cout << "Méthode setBackground de la classe ImageB" << endl;
    #endif

    int i,j;

    for(i=0;i<mesDimensions.getLargeur();i++)
    {
        for(j=0;j<mesDimensions.getHauteur();j++)
        {
            setPixel(i,j,valeur);
        }
    }
}

//Surcharge des opérateurs :

ImageB& ImageB::operator=(const ImageB &image) 
{
    int i,j;

    #ifdef DEBUG
        cout << "operator= de la classe ImageB" << endl;
    #endif

    id = image.id;
    strcpy(nom,image.nom);
    mesDimensions=image.mesDimensions;

    for(i=0;i<mesDimensions.getLargeur();i++)
    {
        for(j=0;j<mesDimensions.getHauteur();j++)
        {
            matrice[i][j]=image.matrice[i][j];
        }
    }

    return (*this);
}

std::ostream& operator<<(std::ostream& os, const ImageB& image)
{
    #ifdef DEBUG
        cout << "operator<< de la classe ImageB" << endl;
    #endif

    os << "Identifiant = " << image.getId() << ", Nom = " << image.getNom()
    << ", Dimensions = " << image.getDimension() << endl;
    return os;
}

//Fonction Dessine :

void ImageB::Dessine()
{
    #ifdef DEBUG
        cout << "Méthode Dessine() de la classe ImageB" << endl;
    #endif

    MyQT myqt;

    myqt.ViewImage(*this);
}

//Méthode d'exportation des fichiers :

void ImageB::exportToFile(const char* fichier, const char* format)
{
    #ifdef DEBUG
        cout << "Méthode exportToFile() de la classe ImageB" << endl;
    #endif

    MyQT myqt;

    myqt.ExportToFile(*this,fichier,format);
}

//Fonction d'affichage :

void ImageB::Affiche() const
{
    #ifdef DEBUG
        cout << "Méthode Affiche() de la classe ImageB" << endl;
    #endif

    cout << "Identifiant = " << getId() << endl;
    cout << "Nom = " << getNom() << endl;
    cout << "Dimensions = " << getDimension() << endl;;
}

//Destructeur :

ImageB::~ImageB()
{
    #ifdef DEBUG
        cout << "Destructeur de la classe ImageB" << endl;
    #endif

}