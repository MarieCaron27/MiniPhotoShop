#ifndef IMAGEB_H
#define IMAGEB_H

#include "Dimension.h"
#include "Couleur.h"
#include "Image.h"
#include "Exception.h"
#include "RGBException.h"
#include "XYException.h"

#include <fstream>

using namespace std;

class ImageB : public Image
{
    //Surcharge opérateurs :
    friend ostream &operator<<(ostream &os, const ImageB &i);
    
    private:
        //Variables statics constantes L_MAX et H_MAX :
        static const int L_MAX = 700;
        static const int H_MAX = 700;
        
        //Matrice :
        bool matrice[L_MAX][H_MAX];

    public:
        //Variables membres statiques :
        static Couleur couleurTrue;
        static Couleur couleurFalse;

        //Constructeurs :
        ImageB();//Par défaut
        ImageB(int identifiant,const char *n); //D'initialisation
        ImageB(const ImageB &objet); //De copie
        ImageB(int identifiant,const char *n,const Dimension &d); //D'initialisation complet
        ImageB(const char *n);
        
        //Getters :
        bool getPixel(int x,int y) const; 

        //Setters :
        void setPixel(int x,int y,bool valeur);
        void setBackground(bool valeur);

        //Surchage des opérateurs :
        ImageB &operator=(const ImageB &i);
        
        //Méthodes d'Image :
        void Dessine() override;
        void exportToFile(const char* fichier, const char* format) override;
        void Affiche() const override;

        //Méthode permettant d’enregistrer sur flux fichier toutes les données des dimensions
        void Save(ofstream & fichier) const;

        //Méthode permettant de charger toutes les données relatives aux dimensions enregistrée sur le flux 
        //fichier passé en paramètre
        void Load(ifstream & fichier);

        //Destructeur :
        ~ImageB();
};

#endif