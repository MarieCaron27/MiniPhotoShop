#include <iostream>
#include <ostream>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <fstream>

#include "Image.h"
#include "Exception.h"
#include "XYException.h"
#include "RGBException.h"
#include "MyQT.h"

using namespace std;

//Constructeurs :

Image::Image(const Image &objet)//Copie
{
    #ifdef DEBUG
        cout << "Constructeur de copie de la classe Image" << endl;
    #endif

    int i,j;

    nom=NULL;
    setNom(objet.nom);
    setId(objet.id);
    setDimension(objet.getDimension());
}

Image::Image(int identifiant,const char *n) //Initialisation
{
    #ifdef DEBUG
        cout << "Constructeur d'initialisation de la classe Image" << endl;
    #endif

    nom=NULL;
    setNom(n);
    setId(identifiant);
}

Image::Image() //Par défaut
{
    #ifdef DEBUG
        cout << "Constructeur par défault de la classe Image" << endl;
    #endif

    nom=NULL;
    setNom("Default");
    setId(1);
}

Image::Image(int identifiant,const char *n,const Dimension &d)
{
    #ifdef DEBUG
        cout << "Constructeur d'initialisation complet de la classe Image" << endl;
    #endif

    nom=NULL;
    setId(identifiant);
    setNom(n);
    setDimension(d);
}

Image::Image(const char *n)
{
    #ifdef DEBUG
        cout << "Constructeur d'initialisation du nom de la classe Image" << endl;
    #endif

    nom=NULL;
    setNom(n);
}

//Setters :

void Image::setId(int identifiant)
{
    #ifdef DEBUG
        cout << "Méthode setId de la classe Image" << endl;
    #endif

    if(identifiant<0)
    {
        return;
    }
    
    id=identifiant;
}

void Image::setNom(const char *n)
{
    #ifdef DEBUG
        cout << "Méthode setNom de la classe Image" << endl;
    #endif

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

void Image::setDimension(const Dimension &d)
{
    #ifdef DEBUG
        cout << "Méthode setDimension de la classe Image" << endl;
    #endif

    int x,y;

    mesDimensions.setLargeur(d.getLargeur());
    mesDimensions.setHauteur(d.getHauteur());
}

//Getters :

int Image::getId() const
{
    #ifdef DEBUG
        cout << "Méthode getId de la classe Image" << endl;
    #endif

    return id;
}

const char* Image::getNom() const
{
    #ifdef DEBUG
        cout << "Méthode getNom de la classe Image" << endl;
    #endif

    return nom;
}

Dimension Image::getDimension() const
{
    #ifdef DEBUG
        cout << "Méthode getDimension de la classe Image" << endl;
    #endif

    return mesDimensions;
}

//Méthode permettant d’enregistrer sur flux fichier toutes les données des images

void Image::Save(ofstream& fichier) const 
{
    #ifdef DEBUG
        cout << "Méthode Save de la classe Image" << endl;
    #endif
    
    if (!fichier.rdbuf()->is_open()) 
    {
        cout << "Erreur d'ouverture du fichier !" << endl;
        return;
    }

    int taille = strlen(nom);
    
    fichier.write((char*)&id,sizeof(int));
    fichier.write((char *)&taille,sizeof(int));
    fichier.write((char*)nom,taille*sizeof(char));
    fichier.write((char*)&mesDimensions,sizeof(int));

    fichier.close();
}


//Méthode permettant de charger toutes les données relatives aux images enregistrée sur le flux 
//fichier passé en paramètre

void Image::Load(ifstream& fichier) 
{
    #ifdef DEBUG
        cout << "Méthode Load de la classe Image" << endl;
    #endif
    
    if (!fichier.is_open()) 
    {
        cout << "Erreur d'ouverture du fichier !" << endl;
        return;
    }

    int t=strlen(nom);

    fichier.read((char*)&id,sizeof(int));
    fichier.read((char *)&t,sizeof(int));
    fichier.read((char*)nom,t*sizeof(char));
    fichier.read((char*)&mesDimensions,sizeof(int));
    
    fichier.close();
}

//Destructeur :

Image::~Image()
{
    #ifdef DEBUG
        cout << "Destructeur de la classe Image" << endl;
    #endif

    if (nom)
    {
        delete nom;
    }
}
