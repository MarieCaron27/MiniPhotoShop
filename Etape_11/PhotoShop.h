#ifndef PHOTOSHOP_H
#define PHOTOSHOP_H

#include <iostream>

#include "Image.h"
#include "ArrayList.h"

using namespace std;

class PhotoShop
{
    private:
        ArrayList<Image*> image;
        static int numCourant;
        static PhotoShop instance;

        //Constructeurs :
        PhotoShop(); //Par défaut
        PhotoShop(const PhotoShop &objet); //De copie

        //Surchage des opérateurs :
        PhotoShop &operator=(const PhotoShop &i);
    
    public:
        //Méthodes : 
        void reset(); //Permet de supprimer (et désallouer) toutes les images du conteneur
                    //images et de remettre la variable statique numCourant à 1
        void ajouteImage(Image* pImage); //Ajouter au conteneur images une image qui a été allouée dynamiquement 
                                        //au préalable
        
        //Affiche/Dessine Images
        void afficheImages() const; //Affiche en console les images contenues dans le conteneur images
        void dessineImages() const; //Dessine les images contenues dans le conteneur images
        
        //Getters :
        Image* getImageParIndice(int indice); //Permet de retourner le pointeur vers l’image située dans 
                                            //le conteneur images correspondant à l’indice
        Image* getImageParId(int id);   //Permet de retourner le pointeur vers l’image située dans 
                                        //le conteneur images correspondant à l’id
        
        static PhotoShop& getInstance();

        //Suppression des Images
        void supprimeImageParIndice(int ind); //Permet de supprimer le pointeur vers l’image située dans 
                                            //le conteneur images correspondant à l’indice
        void supprimeImageParId(int id); //Permet de supprimer le pointeur vers l’image située dans 
                                        //le conteneur images correspondant à l’id

        const char* verifierTypeImage(Image *imageTypeChoisi); 
        
        //Destructeur :
        ~PhotoShop(); 

        ArrayList<Image*>& getImages();
};

#endif