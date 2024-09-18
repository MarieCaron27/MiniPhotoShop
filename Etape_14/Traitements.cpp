#include "Traitements.h"
#include <algorithm>
#include <sstream>

ImageB Traitements::Seuillage(const ImageNG& imageIn, int seuil)
{
    #ifdef DEBUG
        cout << "Méthode Seuillage de la classe Traitements" << endl;
    #endif

    int i, j;
    ImageB monImage(imageIn.getId(),(string(imageIn.getNom()) + "-moyenne" + to_string(seuil)).c_str(), imageIn.getDimension());

    Dimension mesDimensions = imageIn.getDimension();

    for(i = 0; i < mesDimensions.getLargeur(); i++)
    {
        for(j = 0; j < mesDimensions.getHauteur(); j++)
        {
            if(imageIn.getPixel(i, j) > seuil)
            {
                monImage.setPixel(i, j, true);
            }
            else
            {
                monImage.setPixel(i, j, false);
            }
        }
    }

    return monImage;
}

ImageNG Traitements::FiltreMoyenneur(const ImageNG& imageIn, int taille) 
{
    #ifdef DEBUG
        cout << "Méthode FiltreMoyenneur de la classe Traitements" << endl;
    #endif

    int largeur = imageIn.getDimension().getLargeur();
    int hauteur = imageIn.getDimension().getHauteur();
    
    ImageNG monImage(imageIn.getId(),(string(imageIn.getNom()) + "-moyenne" + to_string(taille)).c_str(), imageIn.getDimension());

    int demiTaille = taille / 2;

    for (int x = 0; x < largeur; x++) 
    {
        for (int y = 0; y < hauteur; y++) 
        {
            int somme = 0;
            int count = 0;

            // Parcourir les pixels voisins autour du pixel actuel
            for (int i = -demiTaille; i <= demiTaille; i++) 
            {
                for (int j = -demiTaille; j <= demiTaille; j++) 
                {
                    int newX = x + i;
                    int newY = y + j;

                    // Vérifier si les coordonnées sont valides (si oui, on les ajoutes sinon, exclus)
                    if (newX >= 0 && newX < largeur && newY >= 0 && newY < hauteur) 
                    {
                        somme += imageIn.getPixel(newX, newY);
                        count++;
                    }
                }
            }

            // Vérifier si count est différent de zéro avant de calculer la moyenne
            int moyenne = (count != 0) ? somme / count : 0;
            monImage.setPixel(x, y, moyenne);
        }
    }

    return monImage;
}

ImageNG Traitements::FiltreMedian(const ImageNG& imageIn, int taille)
{

	ImageNG imageOut(imageIn);

	int m = imageIn.getDimension().getLargeur();
    int n = imageIn.getDimension().getHauteur();

    // for (int i = 0; i < m; ++i) {
    //     for (int j = 0; j < n; ++j) {
    //         // Créer la fenêtre
    //         vector<int> fenetre;

    //         // Parcourir la fenêtre autour du pixel (i, j)
    //         for (int x = max(0, i - taille / 2); x <= min(m - 1, i + taille / 2); ++x) {
    //             for (int y = max(0, j - taille / 2); y <= min(n - 1, j + taille / 2); ++y) {
    //                 fenetre.push_back(imageIn.getPixel(x, y));
    //             }
    //         }

    //         // Trier les valeurs de la fenêtre
    //         sort(fenetre.begin(), fenetre.end());

    //         // Remplacer la valeur du pixel par la médiane
    //         int indiceMedian = fenetre.size() / 2;
    //         imageOut.setPixel(i, j, fenetre[indiceMedian]);
    //     }
    // }

     for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            // Créer le tableau fenetre
            int fenetre[20];
            int indice = 0; // Indice pour suivre la position actuelle dans le tableau

            // Parcourir la fenêtre autour du pixel (i, j)
            for (int x = max(0, i - taille / 2); x <= min(m - 1, i + taille / 2); x++) {
                for (int y = max(0, j - taille / 2); y <= min(n - 1, j + taille / 2); y++) {
                    fenetre[indice] = imageIn.getPixel(x, y);
                    indice++;
                }
            }

            // Trier les valeurs de la fenêtre
            sort(fenetre, fenetre + indice);

            // Remplacer la valeur du pixel par la médiane
            int indiceMedian = indice / 2;
            imageOut.setPixel(i, j, fenetre[indiceMedian]);
        }
    }

    // Convertir la valeur de la taille en chaîne de caractères
	ostringstream oss;
	oss << taille;
	string tailleString = oss.str();

	// Utiliser strncpy pour copier la chaîne dans un tableau de caractères
	char tstr[10]; 
	strncpy(tstr, tailleString.c_str(), sizeof(tstr));
	tstr[sizeof(tstr) - 1] = '\0'; // Assurer la null-termination

	// Concaténer la chaîne avec le nom de l'image
	char nomImagetaille[100];
	snprintf(nomImagetaille, sizeof(nomImagetaille), "%s-taille%s", imageOut.getNom(), tstr);

	imageOut.setNom(nomImagetaille);

	return imageOut;

}

ImageNG Traitements::Erosion(const ImageNG& imageIn, int taille)
{
    #ifdef DEBUG
        cout << "Méthode Erosion de la classe Traitements" << endl;
    #endif

    int largeur = imageIn.getDimension().getLargeur();
    int hauteur = imageIn.getDimension().getHauteur();

    ImageNG imageOut(imageIn.getId(),(string(imageIn.getNom()) + "-erode" + to_string(taille)).c_str(), imageIn.getDimension());

    int demiTaille = taille / 2;

    for (int x = 0; x < largeur; ++x) 
    {
        for (int y = 0; y < hauteur; ++y) 
        {
            int minimum = 255; // Initialiser le minimum à une valeur maximale

            // Parcourir les pixels voisins autour du pixel actuel
            for (int i = -demiTaille; i <= demiTaille; ++i) 
            {
                for (int j = -demiTaille; j <= demiTaille; ++j) 
                {
                    int newX = x + i;
                    int newY = y + j;

                    // Vérifier si les coordonnées sont valides
                    if (newX >= 0 && newX < largeur && newY >= 0 && newY < hauteur) 
                    {
                        // Mettre à jour la valeur minimale
                        int pixelValue = imageIn.getPixel(newX, newY);
                        if (pixelValue < minimum) {
                            minimum = pixelValue;
                        }
                    }
                }
            }

            // Affecter la valeur minimale au pixel dans l'image de sortie
            imageOut.setPixel(x, y, minimum);
        }
    }

    return imageOut;
}

ImageNG Traitements::Dilatation(const ImageNG& imageIn, int taille)
{
    #ifdef DEBUG
        cout << "Méthode Dilatation de la classe Traitements" << endl;
    #endif

    int largeur = imageIn.getDimension().getLargeur();
    int hauteur = imageIn.getDimension().getHauteur();

    ImageNG imageOut(imageIn.getId(),(string(imageIn.getNom()) + "-dilate" + to_string(taille)).c_str(), imageIn.getDimension());

    int demiTaille = taille / 2;

    for (int x = 0; x < largeur; ++x) 
    {
        for (int y = 0; y < hauteur; ++y) 
        {
            int maximum = 0; // Mettre à jour le maximum à une valeur minimale

            // Parcourir les pixels voisins autour du pixel actuel
            for (int i = -demiTaille; i <= demiTaille; ++i) 
            {
                for (int j = -demiTaille; j <= demiTaille; ++j) 
                {
                    int newX = x + i;
                    int newY = y + j;

                    // Vérifier si les coordonnées sont valides
                    if (newX >= 0 && newX < largeur && newY >= 0 && newY < hauteur) 
                    {
                        // Mettre à jour la valeur maximale
                        int pixelValue = imageIn.getPixel(newX, newY);
                        if (pixelValue > maximum) 
                        {
                            maximum = pixelValue;
                        }
                    }
                }
            }

            // Affecter la valeur maximale au pixel dans l'image de sortie
            imageOut.setPixel(x, y, maximum);
        }
    }

    return imageOut;
}

ImageNG Traitements::Negatif(const ImageNG& imageIn)
{
    #ifdef DEBUG
        cout << "Méthode Negatif de la classe Traitements" << endl;
    #endif

    int largeur = imageIn.getDimension().getLargeur();
    int hauteur = imageIn.getDimension().getHauteur();
    ImageNG monImage(imageIn.getId(), (string(imageIn.getNom()) + "-negatif").c_str(), imageIn.getDimension());

    for (int i = 0; i < largeur; i++) 
    {
        for (int j = 0; j < hauteur; j++) 
        {
            int valeurPixel = imageIn.getPixel(i, j);
            int valeurNegatif = 255 - valeurPixel;

            monImage.setPixel(i, j, valeurNegatif);
        }
    }

    return monImage;
}
