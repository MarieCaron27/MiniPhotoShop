#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <cstddef>

using namespace std;

// Forward declaration des classes Itérateur et PhotoShop pour permettre son utilisation
template<class T> class Iterateur;
class PhotoShop;

template<class T> struct Cellule
{
    T valeur;
    Cellule<T> *suivant;
};

template<class T> class ArrayList
{
    private :
        Cellule<T> *pTete=NULL;
        
        //Classes amies :
        friend class Iterateur<T>;
        friend class PhotoShop;
        
    public:
        //Constructeurs :
        ArrayList(); //Par défaut
        ArrayList(const ArrayList<T> &l); //Copie 
        
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

