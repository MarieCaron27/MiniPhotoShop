#ifndef IMAGE_H
#define IMAGE_H
#include "Dimension.h"

#include <fstream>

class Image
{
    protected:
        int id;
        char *nom;
        Dimension mesDimensions;

    public:    
        //Constructeurs :
        Image();//Par défaut
        Image(int identifiant,const char *n); //D'initialisation
        Image(const Image &objet); //De copie
        Image(int identifiant,const char *n,const Dimension &d); //D'initialisation complet
        Image(const char *n);

        //Getters :
        int getId() const; //Getter Identifiant
        const char * getNom() const; //Getter Nom
        Dimension getDimension() const; //Getter Dimension

        //Setters :
        void setId(int identifiant); //Setter Identifiant
        void setNom(const char *n); //Setter Nom
        void setDimension(const Dimension &d); //Setter Dimension

        //Méthode dessine :
        virtual void Dessine()=0;

        //Méthodes d'importations/exportations des fichiers :
        virtual void exportToFile(const char* fichier, const char* format)=0;
        
        //Fonction d'affichage
        virtual void Affiche() const=0;

        //Méthode permettant d’enregistrer sur flux fichier toutes les données des dimensions
        void Save(ofstream & fichier) const;

        //Méthode permettant de charger toutes les données relatives aux dimensions enregistrée sur le flux 
        //fichier passé en paramètre
        void Load(ifstream & fichier);

        //Méthodes get en string :
        virtual std::string getTypeString() const = 0;
        virtual std::string getDimensionString() const = 0;

        //Destructeur :
        virtual ~Image();
};

#endif