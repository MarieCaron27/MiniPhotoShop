#ifndef DIMENSION_H
#define DIMENSION_H

#include <iostream>
#include <fstream>

using namespace std;

class Dimension
{
    friend ostream &operator<<(ostream &os, const Dimension &dimension);
    friend istream &operator>>(istream &is, Dimension &dimension);
    
    private:
        int largeur;
        int hauteur;

        //Fonction Comparaison :
        int ComparaisonDimension(const Dimension &dimension) const;
    
    public:
        static const Dimension VGA;
        static const Dimension HD;
        static const Dimension FULL_HD;
        
        //Constructeurs :
        Dimension();//Par défaut
        Dimension(int l,int h); //D'initialisation
        Dimension(const Dimension &objet); //De copie
        
        //Getters :
        int getLargeur() const; //Getter Largeur
        int getHauteur() const; //Getter Hauteur

        //Setters :
        void setLargeur(int l); //Setter Largeur
        void setHauteur(int h); //Setter Hauteur

        //Surchage des opérateurs :
        int operator==(const Dimension &dimension) const;
        int operator!=(const Dimension &dimension) const;
        Dimension operator+(const int nb) const;
        Dimension operator-(const int nb) const;

        //Fonction d'affichage :
        void Affiche() const;

        //Méthode permettant d’enregistrer sur flux fichier toutes les données des dimensions
        void Save(ofstream & fichier) const;

        //Méthode permettant de charger toutes les données relatives aux dimensions enregistrée sur le flux 
        //fichier passé en paramètre
        void Load(ifstream & fichier);
};

#endif