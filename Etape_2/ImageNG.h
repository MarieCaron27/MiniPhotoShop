#ifndef IMAGENG_H
#define IMAGENG_H
#include "Dimension.h"

class ImageNG
{
    private:
        int id;
        char *nom;
        Dimension mesDimensions;

    public:
        //Constructeurs :
        ImageNG();//Par défaut
        ImageNG(int identifiant,const char *n); //D'initialisation
        ImageNG(const ImageNG &objet); //De copie
        ImageNG(int identifiant,const char *n,const Dimension &d); //D'initialisation complet
        
        //Getters :
        int getId() const; //Getter Identifiant
        const char * getNom() const; //Getter Nom
        Dimension getDimension() const; //Getter Dimension

        //Setters :
        void setId(int identifiant); //Setter Identifiant
        void setNom(const char *n); //Setter Nom
        void setDimension(const Dimension &d); //Setter Dimension

        //Destructeur :
        ~ImageNG();

        //Fonction d'affichage
        void Affiche() const;
};

#endif