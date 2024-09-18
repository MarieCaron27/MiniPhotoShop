#ifndef IMAGENG_H
#define IMAGENG_H
#include "Dimension.h"

class ImageNG
{
    //Surcharge opérateurs :
    friend ostream &operator<<(ostream &os, const ImageNG &i);
    friend ImageNG operator+(const int nombre,const ImageNG &image);
    friend ImageNG operator-(const int nombre,const ImageNG &image);

    private:
        int id;
        char *nom;
        Dimension mesDimensions;

        //Variables statics constantes L_MAX et H_MAX + matrice :
        static const int L_MAX = 700;
        static const int H_MAX = 700;
        
        //Matrice :
        int matrice[L_MAX][H_MAX];

        //Fonction Comparaison :
        int ComparaisonImageNG(const ImageNG& image) const;

    public:
        //Constructeurs :
        ImageNG();//Par défaut
        ImageNG(int identifiant,const char *n); //D'initialisation
        ImageNG(const ImageNG &objet); //De copie
        ImageNG(int identifiant,const char *n,const Dimension &d); //D'initialisation complet
        ImageNG(const char *n);
        
        //Getters :
        int getId() const; //Getter Identifiant
        const char * getNom() const; //Getter Nom
        Dimension getDimension() const; //Getter Dimension
        int getPixel(int x,int y) const; //Getter Pixels
        int getLuminance() const; //Retourne la valeur moyenne des niveaux de gris de tous les pixels de l’image
        int getMinimum() const; //Retourne le minimum des niveaux de gris de tous les pixels de l’image
        int getMaximum() const; //Retourne le maximum des niveaux de gris de tous les pixels de l’image
        float getContraste() const; //Retourne le constraste de l'image

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

        //Surchage des opérateurs :
        ImageNG &operator=(const ImageNG &i);
        ImageNG operator+(const int nombre) const;
        ImageNG operator-(const int nombre) const;
        ImageNG operator-(const ImageNG &i) const;
        
        int operator<(const ImageNG &i) const;
        int operator>(const ImageNG &i) const;
        int operator==(const ImageNG &i) const;
        
        ImageNG operator++();
        ImageNG operator++(int);
        ImageNG operator--();
        ImageNG operator--(int);
        

        //Destructeur :
        ~ImageNG();

        //Fonction d'affichage
        void Affiche() const;
};

#endif