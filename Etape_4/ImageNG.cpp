#include <iostream>
#include <ostream>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "ImageNG.h"
#include "MyQT.h"
using namespace std;

//Constructeurs :

ImageNG::ImageNG(const ImageNG &objet) //Copie
{
    int i,j;

    nom=NULL;
    setNom(objet.nom);
    setId(objet.id);
    setDimension(objet.getDimension());

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
    nom=NULL;
    setNom(n);
    setId(identifiant);
}

ImageNG::ImageNG() //Par défaut
{
    nom=NULL;
    setNom("Default");
    setId(1);
}

ImageNG::ImageNG(int identifiant,const char *n,const Dimension &d)
{
    nom=NULL;
    setId(identifiant);
    setNom(n);
    setDimension(d);
}

ImageNG::ImageNG(const char *n)
{
    nom=NULL;
    setNom(n);
    importFromFile(n);
}

//Setters :

void ImageNG::setId(int identifiant)
{
    if(identifiant<0)
    {
        return;
    }
    
    id=identifiant;
}

void ImageNG::setNom(const char *n)
{
    if(n==NULL)
    {
        return;
    }
    
    if(nom!=NULL)
    {
        delete nom;
    }

    nom = new char[strlen(n)+1];
    strcpy(nom,n);
}

void ImageNG::setDimension(const Dimension &d)
{
    int x,y;

    mesDimensions.setLargeur(d.getLargeur());
    mesDimensions.setHauteur(d.getHauteur());
}

void ImageNG::setPixel(int x,int y,int val)
{
    matrice[x][y]=val;
}

void ImageNG::setBackground(int val)
{
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

int ImageNG::getId() const
{
    return id;
}

const char* ImageNG::getNom() const
{
    return nom;
}

Dimension ImageNG::getDimension() const
{
    return mesDimensions;
}

int ImageNG::getPixel(int x,int y) const
{
    return matrice[x][y];
}

int ImageNG::getLuminance() const
{
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
    MyQT myqt;
    
    myqt.ViewImage(*this);
}

//Méthodes d'importation et d'exportation des fichiers :

void ImageNG::importFromFile(const char *fichier)
{
    MyQT myqt;

    myqt.ImportFromFile(*this,fichier);
}

void ImageNG::exportToFile(const char* fichier, const char* format)
{
    MyQT myqt;

    myqt.ExportToFile(*this,fichier,format);
}

//Surcharge des opérateurs :

ImageNG& ImageNG::operator=(const ImageNG &image) 
{
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
    return image+nb;
}

ImageNG ImageNG::operator-(const int nb) const
{
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
    return image-nb;
}

ImageNG ImageNG::operator-(const ImageNG &i) const
{
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
    return ComparaisonImageNG(image)==-1;
}
        
int ImageNG::operator>(const ImageNG& image) const
{
    return ComparaisonImageNG(image)==1;
}
        
int ImageNG::operator==(const ImageNG& image) const
{
    return ComparaisonImageNG(image)==0;
}

ImageNG ImageNG::operator++() 
{
    (*this) = (*this) + 20;
    return (*this);
}

ImageNG ImageNG::operator++(int) 
{
    ImageNG image(*this); 
    (*this) = (*this) + 20;
    return (image);
}

ImageNG ImageNG::operator--() 
{
    (*this) = (*this) - 20;
    return (*this);
}

ImageNG ImageNG::operator--(int) 
{
    ImageNG image(*this); 
    (*this) = (*this) - 20;
    return (image);
}

std::ostream& operator<<(std::ostream& os, const ImageNG& image)
{
    os << "Identifiant = " << image.getId() << ", Nom = " << image.getNom()
    << ", Dimensions = " << image.getDimension() << ", Luminance = " << image.getLuminance()
    << ", Contraste = " << image.getContraste() << endl;
    return os;
}

//Fonction Comparaison :

int ImageNG::ComparaisonImageNG(const ImageNG& i) const
{
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

//Destructeur :

ImageNG::~ImageNG()
{
    int i,j;

    if (nom)
    {
        delete nom;
    }
}

//Fonction d'affichage :

void ImageNG::Affiche() const
{
    cout << "Identifiant = " << getId() << endl;
    cout << "Nom = " << getNom() << endl;
    cout << "Dimensions = " << getDimension() << endl;;
}
