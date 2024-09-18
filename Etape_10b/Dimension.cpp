#include <iostream>
#include <ostream>
#include <string.h>
#include <fstream>

#include "Dimension.h"
#include "Exception.h"
#include "XYException.h"
#include "RGBException.h"
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
        throw XYException(l,"Largeur plus petite que 0!");
    }
    
    largeur=l;
}

void Dimension::setHauteur(int h)
{
    if(h<0)
    {
        throw XYException(h,"Hauteur plus petite que 0!");
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

//Surcharge des opérateurs:

int Dimension::operator==(const Dimension &d) const
{
    return ComparaisonDimension(d)==0;
}

int Dimension::operator!=(const Dimension &d) const
{
    return ComparaisonDimension(d)==-1;
}

std::ostream &operator<<(std::ostream &os, const Dimension &dimension)
{
    os << "Largeur = " << dimension.getLargeur() << ", Hauteur = " << dimension.getHauteur();
    return os;
}

istream &operator>>(istream &is, Dimension &dimension) 
{
    cout << "Saisir la largeur :";
    is >> dimension.largeur;

    cout << "Saisir la hauteur :";
    is >> dimension.hauteur;
    return is;
}

Dimension Dimension::operator+(const int nb) const 
{
    Dimension mesNouvellesDimensions(*this);
    
    mesNouvellesDimensions.largeur += nb;
    mesNouvellesDimensions.hauteur += nb;
    
    return mesNouvellesDimensions;
}

Dimension Dimension::operator-(const int nb) const
{
    Dimension mesNouvellesDimensions(*this);
    
    mesNouvellesDimensions.largeur -= nb;
    mesNouvellesDimensions.hauteur -= nb;
    
    return mesNouvellesDimensions;
}

//Fonction Comparaison :

int Dimension::ComparaisonDimension(const Dimension &d) const
{
    if(d.getLargeur()==getLargeur() && d.getHauteur()==getHauteur())
    {
        return 0;
    }

    return -1;    
}

//Fonction d'affichage :

void Dimension::Affiche() const
{
    cout << "Largeur = " << getLargeur() << endl;
    cout << "Hauteur = " << getHauteur() << endl;
}

//Méthode permettant d’enregistrer sur flux fichier toutes les données des dimensions

void Dimension::Save(ofstream& fichier) const 
{
    #ifdef DEBUG
        cout << "Méthode Save de la classe Dimension" << endl;
    #endif

    if (!fichier.rdbuf()->is_open()) 
    {
        cout << "Erreur d'ouverture du fichier !" << endl;
        return;
    }
    
    fichier.write((char *)&largeur, sizeof(int));
    fichier.write((char *)&hauteur, sizeof(int));

    fichier.close();
}


//Méthode permettant de charger toutes les données relatives aux dimensions enregistrée sur le flux 
//fichier passé en paramètre

void Dimension::Load(ifstream& fichier) 
{
    #ifdef DEBUG
        cout << "Méthode Load de la classe Dimensions" << endl;
    #endif
    
    if (!fichier.rdbuf()->is_open()) 
    {
        cout << "Erreur d'ouverture du fichier !" << endl;
        return;
    }

    fichier.read((char *)&largeur, sizeof(int));
    fichier.read((char *)&hauteur, sizeof(int));

    fichier.close();
}

//Attribution des valeurs par défaut :

const Dimension Dimension::VGA = Dimension(640,480);
const Dimension Dimension::HD = Dimension(1280,720);
const Dimension Dimension::FULL_HD = Dimension(1920,1080);
