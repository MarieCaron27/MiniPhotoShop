#ifndef IMAGE_H
#define IMAGE_H
#include "Dimension.h"

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

        //Destructeur :
        virtual ~Image();
};

#endif