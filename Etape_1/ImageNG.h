#ifndef IMAGENG_H
#define IMAGENG_H

class ImageNG
{
    private:
        int id;
        char *nom;

    public:
        //Constructeurs :
        ImageNG();//Par défaut
        ImageNG(int identifiant,const char *n); //D'initialisation
        ImageNG(const ImageNG &objet); //De copie
        
        //Getters :
        int getId() const; //Getter Identifiant
        const char * getNom() const; //Getter Nom

        //Setters :
        void setId(int identifiant); //Setter Identifiant
        void setNom(const char *n); //Setter Nom

        //Destructeur :
        ~ImageNG();

        //Fonction d'affichage
        void Affiche() const;
};

#endif