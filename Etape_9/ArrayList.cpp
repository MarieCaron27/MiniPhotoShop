#include <iostream>
#include <ostream>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <cstddef>

#include "ArrayList.h"

//Constructeurs :

template<class T>
ArrayList<T>::ArrayList(const ArrayList<T> &list)
{
    #ifdef DEBUG
        cout << "Constructeur de copie de la classe ArrayList" << endl;
    #endif

    pTete = NULL;

    Cellule<T> *pPrec = NULL;
    Cellule<T> *pCur = list.pTete;

    while (pCur)
    {
        if (!pTete)
        {
            // Si la liste est vide, crée le premier élément
            pTete = new Cellule<T>{pCur->valeur, NULL};
            pPrec = pTete;
        }
        else
        {
            // Ajoute un nouvel élément à la liste
            pPrec->suivant = new Cellule<T>{pCur->valeur, NULL};
            pPrec = pPrec->suivant;
        }

        pCur = pCur->suivant;
    }
}

template<class T>
ArrayList<T>::ArrayList() //Par défaut
{
    #ifdef DEBUG
        cout << "Constructeur par défault de la classe ArrayList" << endl;
    #endif

    pTete=NULL;
}

//Méthodes :

template<class T>
bool ArrayList<T>::estVide() const
{
    #ifdef DEBUG
        cout << "Méthode estVide de la classe ArrayList" << endl;
    #endif

    if(pTete==NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<class T>
void ArrayList<T>::insereElement(T const & valeur)
{
    #ifdef DEBUG
        cout << "Méthode insereElement de la classe ArrayList" << endl;
    #endif

    Cellule<T>* nouvelleCellule = new Cellule<T>;
    nouvelleCellule->valeur = valeur;
    nouvelleCellule->suivant = NULL;

    if (pTete == NULL) 
    {
        pTete = nouvelleCellule;
    } 
    else 
    {
        Cellule<T>* courant = pTete;
        while (courant->suivant != NULL) 
        {
            courant = courant->suivant;
        }

        courant->suivant = nouvelleCellule;
    }
}

template<class T>
T ArrayList<T>::retireElement(int ind)
{
    #ifdef DEBUG
        cout << "Méthode retireElement de la classe ArrayList" << endl;
    #endif

    if (ind < 0 || pTete == NULL) 
    {
        T defaultValue = T();
        return defaultValue;
    }

    if (ind == 0) 
    {
        T valeurRetiree = pTete->valeur;
        Cellule<T>* temp = pTete;
        pTete = pTete->suivant;
        delete temp;
        return valeurRetiree;
    }

    Cellule<T>* courant = pTete;
    for (int i = 0; courant != NULL && i < ind - 1; ++i) 
    {
        courant = courant->suivant;
    }

    if (courant == NULL || courant->suivant == NULL) 
    {
        T defaultValue = T();
        return defaultValue;
    }

    Cellule<T>* temp = courant->suivant;
    T valeurRetiree = temp->valeur;
    courant->suivant = temp->suivant;
    delete temp;
    return valeurRetiree;
}

//Getters :

template<class T>
int ArrayList<T>::getNombreElements() const
{
    struct Cellule<T> *pCur = pTete;
    int nombres = 0;

    #ifdef DEBUG
        cout << "Méthode getNombreElements de la classe ArrayList" << endl;
    #endif

    if(estVide())
    {
        perror("Liste vide !");
        exit(0);
    }

    while (pCur != NULL)
    {
        nombres++;
        pCur = pCur->suivant;
    }

    return nombres;
}


template<class T>
T& ArrayList<T>::getElement(int ind) const 
{
    #ifdef DEBUG
        cout << "Méthode getElement de la classe ArrayList" << endl;
    #endif

    if (estVide())
    {
        cout << "Liste vide\n";
        exit (0);
    }
    
    struct Cellule<T> *pCur;
    pCur = pTete;
    int i=0;

    while(pCur!=NULL)
    {
        if(ind==i)
        {
            return pCur->valeur;
        }
        
        pCur=pCur->suivant;
        i++;
    }
    
    cout << "Index" << ind << "non trouvé dans la liste\n";
    exit (0);
}

//Surcharge des opérateurs :

template<class T>
ArrayList<T> &ArrayList<T>::operator=(const ArrayList<T> &list)
{
    #ifdef DEBUG
        cout << "Opérateur = de la classe ArrayList" << endl;
    #endif

    if (this != &list)
    {
        // Libérer la mémoire occupée par l'objet actuel
        while (pTete)
        {
            Cellule<T> *temp = pTete;
            pTete = pTete->suivant;
            delete temp;
        }

        pTete = NULL; // Remettre à zéro la tête de la liste

        Cellule<T> *pparcSource = list.pTete;
        Cellule<T> **pparcDestination = &pTete;

        while (pparcSource)
        {
            *pparcDestination = new Cellule<T>;
            (*pparcDestination)->valeur = pparcSource->valeur;
            (*pparcDestination)->suivant = NULL;

            pparcDestination = &((*pparcDestination)->suivant);
            pparcSource = pparcSource->suivant;
        }
    }

    return *this;
}

//Fonction d'affichage :

template<class T>
void ArrayList<T>::Affiche() const
{
    #ifdef DEBUG
        cout << "Méthode Affiche() de la classe ArrayList" << endl;
    #endif
    
    if (estVide())
    {
        cout << "Liste vide\n" << endl;
    }
    
    struct Cellule<T> *pCur;
    pCur = pTete;

    cout << "Voici votre liste :" << endl;

    while (pCur != NULL)
    {
        cout << pCur->valeur << endl;
        pCur = pCur->suivant;
    }
}

//Destructeur :

template<class T>
ArrayList<T>::~ArrayList()
{
    #ifdef DEBUG
        cout << "Destructeur de la classe ArrayList" << endl;
    #endif

    Cellule<T> *pCur = pTete;
    Cellule<T> *pPrec = NULL;

    while (pCur)
    {
        pPrec = pCur;
        pCur = pCur->suivant;
        delete pPrec;
    }
}

