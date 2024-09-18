#ifndef IMAGENG_H
#define IMAGENG_H
#include "Dimension.h"

class ImageNG
{
    private:
        int id;
        char *nom;
        Dimension mesDimensions;

        //Variables statics constantes L_MAX et H_MAX + matrice :
        static const int L_MAX = 500;
        static const int H_MAX = 500;
        
        //Matrice :
        int matrice[L_MAX][H_MAX];

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
        int getPixel(int x,int y) const; //Getter Pixels

        //Setters :
        void setId(int identifiant); //Setter Identifiant
        void setNom(const char *n); //Setter Nom
        void setDimension(const Dimension &d); //Setter Dimension
        void setPixel(int x,int y,int val); //Setter Pixels
        void setBackground(int val);

        //Méthode dessine :
        void Dessine();

        //Méthodes d'importations/exportations des fichiers :
        void importFromFile(const char* fichier);
        void exportToFile(const char* fichier, const char* format);

        //Destructeur :
        ~ImageNG();

        //Fonction d'affichage
        void Affiche() const;
};

#endif