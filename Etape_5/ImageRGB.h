#ifndef IMAGERGB_H
#define IMAGERGB_H

#include "Dimension.h"
#include "Couleur.h"
#include "Image.h"

using namespace std;

class ImageRGB : public Image
{
    //Surcharge opérateurs :
    friend ostream &operator<<(ostream &os, const ImageRGB &i);
    
    private:
        //Variables statics constantes L_MAX et H_MAX + matrice :
        static const int L_MAX = 700;
        static const int H_MAX = 700;
        Couleur matrice[L_MAX][H_MAX];

    public:
        //Constructeurs :
        ImageRGB();//Par défaut
        ImageRGB(int identifiant,const char *n); //D'initialisation
        ImageRGB(const ImageRGB &objet); //De copie
        ImageRGB(int identifiant,const char *n,const Dimension &d); //D'initialisation complet
        ImageRGB(const char *n);
        
        //Getters :
        Couleur getPixel(int x,int y) const; 

        //Setters :
        void setPixel(int x,int y,const Couleur& valeur);
        void setBackground(const Couleur& valeur);

        //Surchage des opérateurs :
        ImageRGB &operator=(const ImageRGB &i);
        
        //Méthodes d'Image :
        void Dessine() override;
        void importFromFile(const char *fichier);
        void exportToFile(const char* fichier, const char* format) override;
        void Affiche() const override;

        //Destructeur :
        ~ImageRGB();
};

#endif