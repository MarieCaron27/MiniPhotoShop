#include <iostream>
#include <fstream>
#include <ostream>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#include "PhotoShop.h"
#include "Iterateur.h"
#include "MyQT.h"

using namespace std;

int PhotoShop::numCourant;
PhotoShop PhotoShop::instance;
Image *PhotoShop::operande1 = nullptr;
Image *PhotoShop::operande2 = nullptr;
Image *PhotoShop::resultat = nullptr;

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
    // Libérer la mémoire associée à la liste
    for (Iterateur<Image*> it(image); !it.end(); ++it)
    {
        delete it;
    }

    // Vider la liste (libère automatiquement la mémoire)
    image.estVide();

    // Réinitialiser numCourant à 1
    numCourant = 1;
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

PhotoShop& PhotoShop::getInstance()
{
    #ifdef DEBUG
        cout << "Méthode getInstance de la classe PhotoShop" << endl;
    #endif

    return instance;
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

// Méthodes pour vérifier le type d'image en fonction de l'élément de menu choisi

const char* PhotoShop::verifierTypeImage(Image* imageTypeChoisi) 
{
    Image* imageSelectionnee = imageTypeChoisi;
    const char* type = nullptr;

    if (imageSelectionnee) 
    {
        // Comparaison des indicateurs pour déterminer le type d'image
        if (dynamic_cast<ImageNG*>(imageTypeChoisi)) 
        {
            type = "NG";
        }
        else if(dynamic_cast<ImageRGB*>(imageTypeChoisi))
        {
            type = "RGB";
        } 
        else if(dynamic_cast<ImageB*>(imageTypeChoisi))
        {
            type = "B";
        }
        else 
        {
            // Afficher un message d'erreur si les types ne correspondent pas
            perror("Erreur : Le type d'image sélectionné ne correspond pas à l'option choisie.");
            exit(0);
        }
    } 
    else
    {
        // Image non sélectionnée ou pointeur null
        perror("Erreur : Aucune image sélectionnée.");
        exit(0);
    }

    return type;
}

//Sauvergarde fichier CSV :

int PhotoShop::importeImages(string nomFichier)
{
    std::ifstream fichier(nomFichier);

    if (!fichier.is_open())
        return 0;

    int nombreImagesImportees = 0;

    string ligne;
    while (getline(fichier, ligne))
    {
        size_t posDebut = 0;
        size_t posFin = ligne.find(';');

        // Utiliser posFin pour détecter la fin de chaque champ
        string typeImage = ligne.substr(posDebut, posFin - posDebut);
        posDebut = posFin + 1;
        posFin = ligne.find(';', posDebut);
        string cheminImage = ligne.substr(posDebut, posFin - posDebut);
        posDebut = posFin + 1;
        string nomImage = ligne.substr(posDebut);

        // En fonction du type d'image, créer un objet du bon type
        if (typeImage == "NG")
        {
            ImageNG *pImageNG = new ImageNG();
            pImageNG->importFromFile(cheminImage.c_str());
            pImageNG->setNom(nomImage.c_str());
            ajouteImage(pImageNG);
        }
        else if (typeImage == "RGB")
        {
            ImageRGB *pImageRGB = new ImageRGB();
            pImageRGB->importFromFile(cheminImage.c_str());
            pImageRGB->setNom(nomImage.c_str());
            ajouteImage(pImageRGB);
        }
        nombreImagesImportees++;
    }

    return nombreImagesImportees;
}

// Méthode permettant de sauvegarder l'état de la bibliothèque dans un fichier binaire
void PhotoShop::Save(const string &nomFichier) const
{
    std::ofstream fichier(nomFichier, std::ios::binary);

    if (!fichier.is_open())
    {
        std::cout << "Erreur lors de l'ouverture du fichier " << nomFichier << std::endl;
        return;
    }

    // Sauvegarde de numCourant
    fichier.write(reinterpret_cast<const char *>(&numCourant), sizeof(numCourant));

    // Sauvegarde de couleurs TRUE et FALSE
    fichier.write(reinterpret_cast<const char *>(&ImageB::couleurTrue), sizeof(ImageB::couleurTrue));
    fichier.write(reinterpret_cast<const char *>(&ImageB::couleurFalse), sizeof(ImageB::couleurFalse));

    // Sauvegarde le nombre d'images dans le conteneur
    int nbImages = image.getNombreElements();
    fichier.write(reinterpret_cast<const char *>(&nbImages), sizeof(nbImages));

    // Sauvegarde des images
    for (int i = 0; i < nbImages; ++i)
    {
        Image *pImage = image.getElement(i);

        // Écriture de l'identifiant du type d'image
        if (dynamic_cast<ImageNG *>(pImage) != nullptr)
        {
            int typeImage = 1;
            fichier.write(reinterpret_cast<const char *>(&typeImage), sizeof(typeImage));
        }
        else if (dynamic_cast<ImageRGB *>(pImage) != nullptr)
        {
            int typeImage = 2;
            fichier.write(reinterpret_cast<const char *>(&typeImage), sizeof(typeImage));
        }
        else if (dynamic_cast<ImageB *>(pImage) != nullptr)
        {
            int typeImage = 3;
            fichier.write(reinterpret_cast<const char *>(&typeImage), sizeof(typeImage));
        }

        // Appel à la méthode Save() de la classe ImageXXX
        pImage->Save(fichier);
    }

    fichier.close();
}

// Méthode permettant de charger l'état de la bibliothèque depuis un fichier binaire
void PhotoShop::Load(const string &nomFichier)
{
    std::ifstream fichier(nomFichier, std::ios::binary);

    if (!fichier.is_open() || fichier.fail())
    {
        std::cout << "Erreur lors de l'ouverture du fichier " << nomFichier << std::endl;
        return;
    }

    // Réinitialisation de l'application
    cout << "Avant reset()" << endl;
    reset();
    cout << "Après reset()" << endl;

    // Lecture de numCourant
    fichier.read(reinterpret_cast<char *>(&numCourant), sizeof(numCourant));
    cout << "numCourant: " << numCourant << endl;

    // Lecture de couleurs TRUE et FALSE
    fichier.read(reinterpret_cast<char *>(&ImageB::couleurTrue), sizeof(ImageB::couleurTrue));
    fichier.read(reinterpret_cast<char *>(&ImageB::couleurFalse), sizeof(ImageB::couleurFalse));
    
    cout << "couleurTrue: " << ImageB::couleurTrue << endl;
    cout << "couleurFalse: " << ImageB::couleurFalse << endl;

    // Lecture du nombre d'images dans le conteneur
    int nbImages = 0;
    fichier.read(reinterpret_cast<char *>(&nbImages), sizeof(nbImages));
    
    cout << "Nombre Images: " << nbImages << endl;

    int typeImage;
    
    // Lecture des images
    for (int i = 0; i < nbImages; ++i)
    {
        typeImage = 0;
        fichier.read(reinterpret_cast<char *>(&typeImage), sizeof(typeImage));

        cout << i << ") Type de l'image : " << typeImage << endl;

        if (typeImage == 1)
        {
            ImageNG *pImageNG = new ImageNG();
            pImageNG->Load(fichier);
            image.insereElement(pImageNG);
            cout << "ImageNG ajoutée" << endl;
        }
        else if (typeImage == 2)
        {
            ImageRGB *pImageRGB = new ImageRGB();
            pImageRGB->Load(fichier);
            image.insereElement(pImageRGB);
            cout << "ImageRGB ajoutée" << endl;
        }
        else if (typeImage == 3)
        {
            ImageB *pImageB = new ImageB();
            pImageB->Load(fichier);
            image.insereElement(pImageB);
            cout << "ImageB ajoutée" << endl;
        }
    }

    fichier.close();
}
    
//Destructeur :

PhotoShop::~PhotoShop()
{
    #ifdef DEBUG
        cout << "Destructeur de la classe PhotoShop" << endl;
    #endif
    
    reset();
} 

ArrayList<Image*>& PhotoShop::getImages() 
{
    return image; // Renvoie la liste d'images
}