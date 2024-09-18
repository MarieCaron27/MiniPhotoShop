#ifndef DIMENSION_H
#define DIMENSION_H

class Dimension
{
    private:
        int largeur;
        int hauteur;
    
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

        //Fonction d'affichage :
        
        void Affiche() const;

        //Test :

        friend std::ostream& operator<<(std::ostream& os, const Dimension& dimension);
};

#endif