#include <iostream>
#include <ostream>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#include "PhotoShop.h"
#include "MyQT.h"

using namespace std;

int PhotoShop::numCourant;

//Constructeur :

PhotoShop::PhotoShop()
{
    #ifdef DEBUG
        cout << "Constructeur de la classe PhotoShop" << endl;
    #endif

    numCourant = 1;
}
    
//Méthodes : 
    
void PhotoShop::reset() 
{
    for (int i = 0; i < image.getNombreElements(); ++i) 
    {
        delete image.getElement(i);
    }

    image = ArrayList<Image*>(); // Réinitialise l'ArrayList à un nouvel état vide
    numCourant = 1; // Réinitialise numCourant à 1
}

void PhotoShop::ajouteImage(Image* pImage)
{
    #ifdef DEBUG
        cout << "Méthode ajouteImage de la classe PhotoShop" << endl;
    #endif

    if (pImage == NULL)
    {
        cout << "Erreur : tentative d'ajout d'une image NULL." << endl;
        return;
    }

    // Assigner un identifiant unique à l'image
    pImage->setId(numCourant);

    // Ajouter l'image à l'ArrayList
    image.insereElement(pImage);

    // Incrémenter numCourant pour le prochain ajout
    numCourant++;
}

//Affiche/Dessine Images

void PhotoShop::afficheImages() const 
{
    #ifdef DEBUG
        cout << "Méthode afficheImages de la classe PhotoShop" << endl;
    #endif

    for (int i = 0; i < image.getNombreElements(); ++i) 
    {
        Image* currentImage = image.getElement(i);
        
        if (currentImage)
        {
            cout << "Voici votre image n°" << i << ":" << endl;
            cout << "Voici son identifiant : " << currentImage->getId() << endl;

            // Utiliser la méthode virtuelle Affiche() de la classe Image
            currentImage->Affiche();
        }
        else
        {
            cout << "Image nulle à l'indice " << i << endl;
        }
    }
}

void PhotoShop::dessineImages() const
{
    #ifdef DEBUG
        cout << "Méthode dessineImages de la classe PhotoShop" << endl;
    #endif

    for (int i = 0; i < image.getNombreElements(); ++i)
    {
        Image* currentImage = image.getElement(i);
        
        if (currentImage)
        {
            cout << "Dessin de l'image n°" << i << ":" << endl;
            cout << "Identifiant : " << currentImage->getId() << endl;
            
            // Utilisation de la méthode virtuelle Dessine() de la classe Image
            currentImage->Dessine();
            
            cout << "------------------------------------" << endl;
        }
        else
        {
            cout << "Image nulle à l'indice " << i << endl;
        }
    }
}

//Getters :

Image* PhotoShop::getImageParIndice(int indice) 
{
    #ifdef DEBUG
        cout << "Méthode getImageParIndice de la classe PhotoShop" << endl;
    #endif

    // Vérification de l'indice
    if (indice < 0 || indice >= image.getNombreElements()) 
    {
        cout << "Indice hors limites" << endl;
        return NULL; // Retourne un pointeur nul si l'indice est incorrect
    }

    return image.getElement(indice);
}
    
Image* PhotoShop::getImageParId(int id)
{
    #ifdef DEBUG
        cout << "Méthode getImageParId de la classe PhotoShop" << endl;
    #endif

    if (id < 1 || id >= image.getNombreElements()) 
    {
        cout << "Indantifiant hors limites" << endl;
        return NULL; // Retourne un pointeur nul si l'indice est incorrect
    }

    return image.getElement(id);
}

//Suppression des Images :

void PhotoShop::supprimeImageParIndice(int ind)
{
    #ifdef DEBUG
        cout << "Méthode supprimeImageParIndice de la classe PhotoShop" << endl;
    #endif

    // Vérification de l'indice
    if (ind < 0 || ind >= image.getNombreElements()) 
    {
        cout << "Indice hors limites" << endl;
        exit(0); 
    }

    image.retireElement(ind);
}

void PhotoShop::supprimeImageParId(int id) 
{
    #ifdef DEBUG
        cout << "Méthode supprimeImageParId de la classe PhotoShop" << endl;
    #endif

    if (id < 0 || id >= image.getNombreElements()) 
    {
        cout << "Indantifiant hors limites" << endl;
        exit(0); 
    }

    image.retireElement(id);
}
    
//Destructeur :

PhotoShop::~PhotoShop()
{
    #ifdef DEBUG
        cout << "Destructeur de la classe PhotoShop" << endl;
    #endif
    
    reset();
} 