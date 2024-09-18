#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <cstddef>

using namespace std;

// Forward declaration de la classe Iterateur pour permettre son utilisation
template<class T> class Iterateur;

template<class T> struct Cellule
{
    T valeur;
    Cellule<T> *suivant;
};

template<class T> class ArrayList
{
    private :
        Cellule<T> *pTete=NULL;
        
        //Itérateur :
        friend class Iterateur<T>;
        
    public:
        //Constructeurs :
        ArrayList(); //Par défaut
        ArrayList(const ArrayList<T> &l); //Copie NON
        
        //Méthodes :
        bool estVide() const;
        void insereElement(T const &val);
        T retireElement(int ind);
        
        //Getters :
        int getNombreElements() const;
        T& getElement(int ind) const;

        //Surcharge opérateurs :
        ArrayList<T>& operator=(const ArrayList<T> &l); 

        //Fonction d'affichage :
        void Affiche() const;

        //Destructeur :
        ~ArrayList();
};

#endif

