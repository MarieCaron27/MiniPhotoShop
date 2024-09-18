#include <iostream>
#include <ostream>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <iterator>

#include "Iterateur.h"
#include "MyQT.h"

using namespace std;

//Constructeur permettant d'atteindre la classe ArrayList :

template<class T>
Iterateur<T>::Iterateur(ArrayList<T>& l) : arrayList(l), pData(l.pTete)
{

}

//Méthodes :

template<class T>
void Iterateur<T>::reset() 
{ 
    pData = arrayList.pTete;
}

template <class T>
int Iterateur<T>::end()
{
    return pData == 0;
}

//Surcharge des opérateurs :

template<class T>
char Iterateur<T>::operator++() // Passe à l’élément suivant
{
    if (pData)
    {
        pData=pData->suivant;
        return 1;
    }
    else
    {
        return 0;
    }
}

template<class T>
char Iterateur<T>::operator++(int) 
{ 
    return operator++(); 
}

template<class T>
T& Iterateur<T>::operator&() const
{
    return pData->valeur;
}

template <class T>
Iterateur<T>::operator T() const
{
    return pData->valeur; 
}

template class Iterateur<Image*>;