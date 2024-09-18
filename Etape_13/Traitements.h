#ifndef TRAITEMENTS_H
#define TRAITEMENTS_H

#include <iostream>

#include "ImageB.h"
#include "ImageNG.h"
#include "ArrayList.h"

using namespace std;

class Traitements
{
    public:
        static ImageB Seuillage(const ImageNG& imageIn, int seuil);
        static ImageNG FiltreMoyenneur(const ImageNG& imageIn, int taille);
        static ImageNG FiltreMedian(const ImageNG& imageIn, int taille);
        static ImageNG Erosion(const ImageNG& imageIn, int taille);
        static ImageNG Dilatation(const ImageNG& imageIn, int taille);
        static ImageNG Negatif(const ImageNG& imageIn);
};

#endif