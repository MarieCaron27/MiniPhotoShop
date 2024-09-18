#ifndef COULEUR_H
#define COULEUR_H

using namespace std;

class Couleur
{
    //Surcharge opérateurs :
    friend ostream &operator<<(ostream &os, const Couleur &c);
    
    private:
        int rouge;
        int vert;
        int bleu;

    public:
        //Variables statiques constantes :
        static const Couleur ROUGE;
        static const Couleur VERT;
        static const Couleur BLEU;
        static const Couleur BLANC;
        static const Couleur NOIR;

        //Constructeurs :
        Couleur(); //Par défaut
        Couleur(int rouge,int vert,int bleu); //Initialisation
        Couleur(const Couleur &objet); //Copie
        
        //Getters :
        int getRouge() const;
        int getVert() const;
        int getBleu() const;

        //Setters :
        void setRouge(int r);
        void setVert(int v);
        void setBleu(int b);
        
        //Fonction d'affichage :
        void Affiche() const;
};

#endif