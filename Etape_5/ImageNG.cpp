#include <iostream>
#include <ostream>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "ImageNG.h"
#include "MyQT.h"
using namespace std;

//Constructeurs :

ImageNG::ImageNG(const ImageNG &objet)//Copie
{
    #ifdef DEBUG
        cout << "Constructeur de copie de la classe ImageNG" << endl;
    #endif

    int i,j;

    for(i=0;i<mesDimensions.getLargeur();i++)
    {
        for(j=0;j<mesDimensions.getHauteur();j++)
        {
            matrice[i][j] = objet.matrice[i][j];
        }
    }
}

ImageNG::ImageNG(int identifiant,const char *n) //Initialisation
{
    #ifdef DEBUG
        cout << "Constructeur d'initialisation de la classe ImageNG" << endl;
    #endif
}

ImageNG::ImageNG() //Par défaut
{
    #ifdef DEBUG
        cout << "Constructeur par défault de la classe ImageNG" << endl;
    #endif
}

ImageNG::ImageNG(int identifiant,const char *n,const Dimension &d)
{
    #ifdef DEBUG
        cout << "Constructeur d'intialisation complet de la classe ImageNG" << endl;
    #endif
}

ImageNG::ImageNG(const char *n)
{
    #ifdef DEBUG
        cout << "Constructeur d'initialisation du nom de la classe ImageNG" << endl;
    #endif

    importFromFile(n);
}

//Setters :

void ImageNG::setPixel(int x,int y,int val)
{
    #ifdef DEBUG
        cout << "Méthode setPixel de la classe ImageNG" << endl;
    #endif

    matrice[x][y]=val;
}

void ImageNG::setBackground(int val)
{
    #ifdef DEBUG
        cout << "Méthode setBackground de la classe ImageNG" << endl;
    #endif

    int i,j;

    for(i=0;i<mesDimensions.getLargeur();i++)
    {
        for(j=0;j<mesDimensions.getHauteur();j++)
        {
            setPixel(i,j,val);
        }
    }
}

//Getters :

int ImageNG::getPixel(int x,int y) const
{
    #ifdef DEBUG
        cout << "Méthode getPixel de la classe ImageNG" << endl;
    #endif

    return matrice[x][y];
}

int ImageNG::getLuminance() const
{
    #ifdef DEBUG
        cout << "Méthode getLuminance de la classe ImageNG" << endl;
    #endif

    int i,j; 
    int somme=0;
    int nbPixels=0;

    for(i=0;i<mesDimensions.getLargeur();i++)
    {
        for(j=0;j<mesDimensions.getHauteur();j++)
        {
            somme += matrice[i][j];
            nbPixels++;
        }
    }

    return(somme/nbPixels);
}

int ImageNG::getMinimum() const
{
    #ifdef DEBUG
        cout << "Méthode getMinimum de la classe ImageNG" << endl;
    #endif

    int min = 255;
    for(int i=0;i<mesDimensions.getLargeur();i++)
    {
        for(int j=0;j<mesDimensions.getHauteur();j++)
        {
            if (matrice[i][j] < min) min = matrice[i][j];
        }
    }
    return min;
}

int ImageNG::getMaximum() const
{
    #ifdef DEBUG
        cout << "Méthode getMaximum de la classe ImageNG" << endl;
    #endif

    int max = 0;
    for(int i=0;i<mesDimensions.getLargeur();i++)
    {
        for(int j=0;j<mesDimensions.getHauteur();j++)
        {
            if (matrice[i][j] > max) max = matrice[i][j];
        }
    }
    return max;
}

float ImageNG::getContraste() const
{
    #ifdef DEBUG
        cout << "Méthode getContraste de la classe ImageNG" << endl;
    #endif

    if(getMinimum()+getMaximum()==0)
    {
        perror("Le dénominateur vaut 0");
        exit(0);
    }

    return (((float)getMaximum()-getMinimum())/(getMinimum()+getMaximum()));
}

//Fonction Dessine :

void ImageNG::Dessine()
{
    #ifdef DEBUG
        cout << "Méthode Dessine() de la classe ImageNG" << endl;
    #endif

    MyQT myqt;
    
    myqt.ViewImage(*this);
}

//Méthodes d'importation et d'exportation des fichiers :

void ImageNG::importFromFile(const char *fichier)
{
    #ifdef DEBUG
        cout << "Méthode importFromFile de la classe ImageNG" << endl;
    #endif

    MyQT myqt;

    myqt.ImportFromFile(*this,fichier);
}

void ImageNG::exportToFile(const char* fichier, const char* format)
{
    #ifdef DEBUG
        cout << "Méthode exportToFile de la classe ImageNG" << endl;
    #endif

    MyQT myqt;

    myqt.ExportToFile(*this,fichier,format);
}

//Surcharge des opérateurs :

ImageNG& ImageNG::operator=(const ImageNG &image) 
{
    #ifdef DEBUG
        cout << "operator= de la classe ImageNG" << endl;
    #endif

    int i,j;

    id = image.id;
    strcpy(nom,image.nom);
    mesDimensions=image.mesDimensions;

    for(i=0;i<mesDimensions.getLargeur();i++)
    {
        for(j=0;j<mesDimensions.getHauteur();j++)
        {
            matrice[i][j]=image.matrice[i][j];
        }
    }

    return (*this);
}

ImageNG ImageNG::operator+(const int nb) const
{
    #ifdef DEBUG
        cout << "operator+ de la classe ImageNG" << endl;
    #endif

    ImageNG image(*this);
    int largeur = mesDimensions.getLargeur();
    int hauteur = mesDimensions.getHauteur();

    for(int x=0;x<largeur;x++)
    {
        for(int y=0;y<hauteur;y++)
        {
            image.matrice[x][y] +=nb;

            if(image.matrice[x][y]<0)
            {
                image.matrice[x][y]=0;
            }

            if(image.matrice[x][y]>255)
            {
                image.matrice[x][y]=255;
            }
        }
    }

    return image;
}

ImageNG operator+(int nb,const ImageNG &image)
{
    #ifdef DEBUG
        cout << "operator+(int nb,const ImageNG &image) de la classe ImageNG" << endl;
    #endif

    return image+nb;
}

ImageNG ImageNG::operator-(const int nb) const
{
    #ifdef DEBUG
        cout << "operator- de la classe ImageNG" << endl;
    #endif

    ImageNG image(*this);

    for(int x=0;x<mesDimensions.getLargeur();x++)
    {
        for(int y=0;y<mesDimensions.getHauteur();y++)
        {
            image.matrice[x][y] -=nb;

            if(image.matrice[x][y]<0)
            {
                image.matrice[x][y]=0;
            }

            if(image.matrice[x][y]>255)
            {
                image.matrice[x][y]=255;
            }
        }
    }

    return image;
}

ImageNG operator-(int nb,const ImageNG &image)
{
    #ifdef DEBUG
        cout << "operator-(int nb,const ImageNG &image) de la classe ImageNG" << endl;
    #endif

    return image-nb;
}

ImageNG ImageNG::operator-(const ImageNG &i) const
{
    #ifdef DEBUG
        cout << "operator-(const ImageNG &i) de la classe ImageNG" << endl;
    #endif

    ImageNG image(*this);

    for(int x=0;x<mesDimensions.getLargeur();x++)
    {
        for(int y=0;y<mesDimensions.getHauteur();y++)
        {
            image.matrice[x][y] -= i.matrice[x][y];

            if(image.matrice[x][y]<0)
            {
                image.matrice[x][y]=0;
            }

            if(image.matrice[x][y]>255)
            {
                image.matrice[x][y]=255;
            }
        }
    }

    return image;
}

int ImageNG::operator<(const ImageNG& image) const
{
    #ifdef DEBUG
        cout << "operator< de la classe ImageNG" << endl;
    #endif

    return ComparaisonImageNG(image)==-1;
}
        
int ImageNG::operator>(const ImageNG& image) const
{
    #ifdef DEBUG
        cout << "operator> de la classe ImageNG" << endl;
    #endif

    return ComparaisonImageNG(image)==1;
}
        
int ImageNG::operator==(const ImageNG& image) const
{
    #ifdef DEBUG
        cout << "operator== de la classe ImageNG" << endl;
    #endif

    return ComparaisonImageNG(image)==0;
}

ImageNG ImageNG::operator++() 
{
    #ifdef DEBUG
        cout << "operator++ de la classe ImageNG" << endl;
    #endif

    (*this) = (*this) + 20;
    return (*this);
}

ImageNG ImageNG::operator++(int) 
{
    #ifdef DEBUG
        cout << "operator++(int) de la classe ImageNG" << endl;
    #endif

    ImageNG image(*this); 
    (*this) = (*this) + 20;
    return (image);
}

ImageNG ImageNG::operator--() 
{
    #ifdef DEBUG
        cout << "operator-- de la classe ImageNG" << endl;
    #endif

    (*this) = (*this) - 20;
    return (*this);
}

ImageNG ImageNG::operator--(int) 
{
    #ifdef DEBUG
        cout << "operator--(int) de la classe ImageNG" << endl;
    #endif

    ImageNG image(*this); 
    (*this) = (*this) - 20;
    return (image);
}

std::ostream& operator<<(std::ostream& os, const ImageNG& image)
{
    #ifdef DEBUG
        cout << "operator<< de la classe ImageNG" << endl;
    #endif

    os << "Identifiant = " << image.getId() << ", Nom = " << image.getNom()
    << ", Dimensions = " << image.getDimension() << ", Luminance = " << image.getLuminance()
    << ", Contraste = " << image.getContraste() << endl;
    return os;
}

//Fonction Comparaison :

int ImageNG::ComparaisonImageNG(const ImageNG& i) const
{
    #ifdef DEBUG
        cout << "Fonction de comparaison de la classe ImageNG" << endl;
    #endif

    for (int x = 0; x < mesDimensions.getLargeur(); x++)
    {
        for (int y = 0; y < mesDimensions.getHauteur(); y++)
        {
            if (i.getPixel(x, y) < getPixel(x, y))
            {
                return -1;
            }

            if (i.getPixel(x, y) > getPixel(x, y))
            {
                return 1;
            }
        }
    }

    return 0;
}

//Fonction d'affichage :

void ImageNG::Affiche() const
{
    #ifdef DEBUG
        cout << "Méthode Affiche() de la classe ImageNG" << endl;
    #endif

    cout << "Identifiant = " << getId() << endl;
    cout << "Nom = " << getNom() << endl;
    cout << "Dimensions = " << getDimension() << endl;;
}

//Destructeur :

ImageNG::~ImageNG()
{
    #ifdef DEBUG
        cout << "Destructeur de la classe ImageNG" << endl;
    #endif

    if (nom)
    {
        delete nom;
    }
}