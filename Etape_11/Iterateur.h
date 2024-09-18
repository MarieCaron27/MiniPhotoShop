#ifndef ITERATEUR_H
#define ITERATEUR_H

#include "ArrayList.h"

using namespace std;

template<class T>
class Iterateur
{
    private :
        ArrayList<T>& arrayList; // Référence constante à l'ArrayList
        Cellule<T> *pData;

    public:
        //Constructeur permettant d'accéder à la classe ArrayList :
        Iterateur(ArrayList<T>& list);

        //Méthodes :
        void reset();
        int end();
        
        //Surcharge opérateurs :
        char operator++();
        char operator++(int);
        T& operator&() const;
        operator T() const;
};

#endif