#include <iostream>
#include <ostream>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <fstream>

#include "ImageB.h"
#include "Exception.h"
#include "XYException.h"
#include "RGBException.h"
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

ImageB::ImageB(const char *n) : Image(n)
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

    char repere;

    if(x<0)
    {
        repere='x';
        throw RGBException(repere,"Valeur pixel x pour ImageB incorrecte!");
    }

    if(x>255)
    {
        repere='x';
        throw RGBException(repere,"Valeur pixel x pour ImageB incorrecte!");
    }

    if(y<0)
    {
        repere='y';
        throw RGBException(repere,"Valeur pixel y pour ImageB incorrecte!");
    }

    if(y>255)
    {
        repere='y';
        throw RGBException(repere,"Valeur pixel y pour ImageB incorrecte!");
    }

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

//Méthode permettant d’enregistrer sur flux fichier toutes les données des images

void ImageB::Save(ofstream& fichier) const 
{
    #ifdef DEBUG
        cout << "Méthode Save de la classe ImageB" << endl;
    #endif

    if (!fichier.is_open()) 
    {
        cout << "Erreur d'ouverture du fichier !" << endl;
        return;
    }

    int taille = strlen(nom);

    fichier.write((char*)&id,sizeof(int));
    fichier.write((char*)&taille,sizeof(int));
    fichier.write(nom,taille);
    fichier.write((char*)&mesDimensions, sizeof(Dimension));

    for (int i = 0; i < mesDimensions.getLargeur(); ++i) 
    {
        for (int j = 0; j < mesDimensions.getHauteur(); ++j) 
        {
            bool pixel = matrice[i][j];
            fichier.write((char*)&pixel, sizeof(int));
        }
    }
}

//Méthode permettant de charger toutes les données relatives aux images enregistrée sur le flux 
//fichier passé en paramètre

void ImageB::Load(ifstream& fichier) 
{
    #ifdef DEBUG
        cout << "Méthode Load de la classe ImageB" << endl;
    #endif

    if (!fichier.is_open()) 
    {
        cout << "Erreur d'ouverture du fichier !" << endl;
        return;
    }

    int taille;
    
    fichier.read((char*)&id, sizeof(int));
    fichier.read((char*)&taille, sizeof(int));

    if (nom) 
    {
        delete[] nom;
    }
    nom = new char[taille + 1]; //assurer de libérer l'ancienne mémoire allouée pour le nom avant d'en allouer 
                                //une nouvelle pour éviter les fuites de mémoire
    
    fichier.read(nom, taille);
    nom[taille] = '\0';

    fichier.read((char*)&mesDimensions, sizeof(Dimension));

    for (int i = 0; i < mesDimensions.getLargeur(); ++i) 
    {
        for (int j = 0; j < mesDimensions.getHauteur(); ++j) 
        {
            fichier.read((char*)&matrice[i][j], sizeof(int));
        }
    }
}

//Méthodes get en string

string ImageB::getTypeString() const 
{
    return "B";
}

string ImageB::getDimensionString() const 
{
    return to_string(getDimension().getLargeur()) + "x" + to_string(getDimension().getHauteur());
}

//Destructeur :

ImageB::~ImageB()
{
    #ifdef DEBUG
        cout << "Destructeur de la classe ImageB" << endl;
    #endif

}