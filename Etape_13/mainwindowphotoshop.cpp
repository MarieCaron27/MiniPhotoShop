#include "mainwindowphotoshop.h"
#include "ui_mainwindowphotoshop.h"

#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QScreen>
#include <QRect>
#include <QPixmap>
#include <QColorDialog>
#include <string>


#include "ImageNG.h"
#include "ImageRGB.h"
#include "ImageB.h"
#include "PhotoShop.h"
#include "Iterateur.h"
#include "Traitements.h"
#include "XYException.h"


MainWindowPhotoShop::MainWindowPhotoShop(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindowPhotoShop)
{
    ui->setupUi(this);
    setTitre("Mini-PhotoShop  en C++");

    // Centrage de la fenetre
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->availableGeometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);
    setFixedSize(1021,845);

    // Configuration de la table des images
    ui->tableWidgetImages->setColumnCount(4);
    ui->tableWidgetImages->setRowCount(0);
    QStringList labelsTableOptions;
    labelsTableOptions << "Id" << "Type" << "Dimension" << "Nom";
    ui->tableWidgetImages->setHorizontalHeaderLabels(labelsTableOptions);
    ui->tableWidgetImages->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetImages->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetImages->horizontalHeader()->setVisible(true);
    ui->tableWidgetImages->horizontalHeader()->setDefaultSectionSize(100);
    ui->tableWidgetImages->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetImages->verticalHeader()->setVisible(false);
    ui->tableWidgetImages->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Intialisation des scrollArea
    /*
    setImageNG("selection");
    setImageNG("operande1");
    setImageNG("operande2");
    setImageNG("resultat");
    */

    // ComboBox des traitements disponibles
    ajouteTraitementDisponible("Eclaircir (+ val)");
    ajouteTraitementDisponible("Eclaircir (++)");
    ajouteTraitementDisponible("Assombrir (- val)");
    ajouteTraitementDisponible("Assombrir (--)");
    ajouteTraitementDisponible("Différence");
    ajouteTraitementDisponible("Comparaison (==)");
    ajouteTraitementDisponible("Comparaison (<)");
    ajouteTraitementDisponible("Comparaison (>)");
    ajouteTraitementDisponible("Seuillage");
    ajouteTraitementDisponible("Filtre moyenneur");
    ajouteTraitementDisponible("Filtre médian");
    ajouteTraitementDisponible("Erosion");
    ajouteTraitementDisponible("Dilatation");
    ajouteTraitementDisponible("Négatif");

    // Etape 14 (TO DO)
    // Restauration bibliothèque via fichier de sauvegarde
}

MainWindowPhotoShop::~MainWindowPhotoShop()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Méthodes de la fenêtre (ne pas modifier) ///////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::setTitre(string titre)
{
  this->setWindowTitle(titre.c_str());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::setNomImage(string nom)
{
  ui->lineEditNom->setText(QString::fromStdString(nom));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string MainWindowPhotoShop::getNomImage() const
{
  return ui->lineEditNom->text().toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::setParametresImageNG(int max,int min,int luminance,float contraste)
{
  if (max == -1)
  {
    ui->lineEditMax->setText("");
    ui->lineEditMin->setText("");
    ui->lineEditLuminance->setText("");
    ui->lineEditContraste->setText("");
    return;
  }
  char tmp[20];
  sprintf(tmp,"%d",max);
  ui->lineEditMax->setText(tmp);
  sprintf(tmp,"%d",min);
  ui->lineEditMin->setText(tmp);
  sprintf(tmp,"%d",luminance);
  ui->lineEditLuminance->setText(tmp);
  sprintf(tmp,"%f",contraste);
  ui->lineEditContraste->setText(tmp);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindowPhotoShop::setImageNG(string destination,const ImageNG* imageng)
{
    QPixmap * pixmap = NULL;
    if (imageng != NULL)
    {
      // Creation du QPixmap
      int largeur = imageng->getDimension().getLargeur();
      int hauteur = imageng->getDimension().getHauteur();
      QImage im1(largeur,hauteur,QImage::Format_RGB32);
      for(int x=0 ; x<largeur ; x++)
        for(int y=0 ; y<hauteur ; y++)
        {
          int valeur = imageng->getPixel(x,y);
          im1.setPixel(x,y,qRgb(valeur,valeur,valeur));
        }
     pixmap = new QPixmap(QPixmap::fromImage(im1));
    }

    // Mise en place du QPixmap
    QLabel* label = new QLabel();
    label->setAlignment(Qt::AlignCenter);
    if (pixmap) label->setPixmap(*pixmap);
    else label->setText("vide");
    if (destination == "selection") ui->scrollAreaSelection->setWidget(label);
    if (destination == "operande1") ui->scrollAreaOperande1->setWidget(label);
    if (destination == "operande2") ui->scrollAreaOperande2->setWidget(label);
    if (destination == "resultat") ui->scrollAreaResultat->setWidget(label);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindowPhotoShop::setImageRGB(string destination,const ImageRGB* imagergb)
{
    QPixmap * pixmap = NULL;
    if (imagergb != NULL)
    {
      // Creation du QPixmap
      int largeur = imagergb->getDimension().getLargeur();
      int hauteur = imagergb->getDimension().getHauteur();
      QImage im1(largeur,hauteur,QImage::Format_RGB32);
      for(int x=0 ; x<largeur ; x++)
        for(int y=0 ; y<hauteur ; y++)
        {
          Couleur valeur = imagergb->getPixel(x,y);
          im1.setPixel(x,y,qRgb(valeur.getRouge(),valeur.getVert(),valeur.getBleu()));
        }
     pixmap = new QPixmap(QPixmap::fromImage(im1));
    }

    // Mise en place du QPixmap
    QLabel* label = new QLabel();
    label->setAlignment(Qt::AlignCenter);
    if (pixmap) label->setPixmap(*pixmap);
    else label->setText("vide");
    if (destination == "selection") ui->scrollAreaSelection->setWidget(label);
    if (destination == "operande1") ui->scrollAreaOperande1->setWidget(label);
    if (destination == "operande2") ui->scrollAreaOperande2->setWidget(label);
    if (destination == "resultat") ui->scrollAreaResultat->setWidget(label);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindowPhotoShop::setImageB(string destination,const ImageB* imageb)
{
    QPixmap * pixmap = NULL;
    if (imageb != NULL)
    {
      // Creation du QPixmap
      int largeur = imageb->getDimension().getLargeur();
      int hauteur = imageb->getDimension().getHauteur();
      QImage im1(largeur,hauteur,QImage::Format_RGB32);
      for(int x=0 ; x<largeur ; x++)
        for(int y=0 ; y<hauteur ; y++)
        {
          bool valeur = imageb->getPixel(x,y);
          if (valeur) im1.setPixel(x,y,qRgb(ImageB::couleurTrue.getRouge(),ImageB::couleurTrue.getVert(),ImageB::couleurTrue.getBleu()));
          else im1.setPixel(x,y,qRgb(ImageB::couleurFalse.getRouge(),ImageB::couleurFalse.getVert(),ImageB::couleurFalse.getBleu()));
        }
     pixmap = new QPixmap(QPixmap::fromImage(im1));
    }

    // Mise en place du QPixmap
    QLabel* label = new QLabel();
    label->setAlignment(Qt::AlignCenter);
    if (pixmap) label->setPixmap(*pixmap);
    else label->setText("vide");
    if (destination == "selection") ui->scrollAreaSelection->setWidget(label);
    if (destination == "operande1") ui->scrollAreaOperande1->setWidget(label);
    if (destination == "operande2") ui->scrollAreaOperande2->setWidget(label);
    if (destination == "resultat") ui->scrollAreaResultat->setWidget(label);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::setResultatBoolean(int val)
{
  if (val == 1) // vrai
  {
    ui->checkBoxResultat->setChecked(true);
    ui->checkBoxResultat->setText("VRAI");
    ui->checkBoxResultat->setStyleSheet("background-color: lightgreen;border: 1px solid black;");
    return;
  }
  if (val == 0) // faux
  {
    ui->checkBoxResultat->setChecked(false);
    ui->checkBoxResultat->setText("FAUX");
    ui->checkBoxResultat->setStyleSheet("background-color: red;border: 1px solid black;");
    return;
  }
  // ni vrai, ni faux
  ui->checkBoxResultat->setChecked(false);
  ui->checkBoxResultat->setText("Résultat");
  ui->checkBoxResultat->setStyleSheet("background-color: lightyellow;border: 1px solid black;");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles Table des Images (ne pas modifier) ////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::ajouteTupleTableImages(int id,string type,string dimension,string nom)
{
    char Id[20];
    sprintf(Id,"%d",id);

    char Type[20];
    strcpy(Type,type.c_str());

    char Dimension[20];
    strcpy(Dimension,dimension.c_str());

    char Nom[80];
    strcpy(Nom,nom.c_str());

    // Ajout possible
    int nbLignes = ui->tableWidgetImages->rowCount();
    nbLignes++;
    ui->tableWidgetImages->setRowCount(nbLignes);
    ui->tableWidgetImages->setRowHeight(nbLignes-1,20);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(Id);
    ui->tableWidgetImages->setItem(nbLignes-1,0,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(Type);
    ui->tableWidgetImages->setItem(nbLignes-1,1,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(Dimension);
    ui->tableWidgetImages->setItem(nbLignes-1,2,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(Nom);
    ui->tableWidgetImages->setItem(nbLignes-1,3,item);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::videTableImages()
{
    ui->tableWidgetImages->setRowCount(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MainWindowPhotoShop::getIndiceImageSelectionnee()
{
    QModelIndexList liste = ui->tableWidgetImages->selectionModel()->selectedRows();
    if (liste.size() == 0) return -1;
    QModelIndex index = liste.at(0);
    int indice = index.row();
    return indice;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Combox des traitements disponibles (ne pas modifier) ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::ajouteTraitementDisponible(string operation)
{
    ui->comboBoxTraitements->addItem(operation.c_str());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::videTraitementsDisponibles()
{
    ui->comboBoxTraitements->clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string MainWindowPhotoShop::getTraitementSelectionne() const
{
    return ui->comboBoxTraitements->currentText().toStdString();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions permettant d'afficher des boites de dialogue (ne pas modifier) ///////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::dialogueMessage(const char* titre,const char* message)
{
   QMessageBox::information(this,titre,message);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::dialogueErreur(const char* titre,const char* message)
{
   QMessageBox::critical(this,titre,message);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string MainWindowPhotoShop::dialogueDemandeTexte(const char* titre,const char* question)
{
    QString chaine = QInputDialog::getText(this,titre,question);
    return chaine.toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MainWindowPhotoShop::dialogueDemandeInt(const char* titre,const char* question)
{
    return QInputDialog::getInt(this,titre,question);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
float MainWindowPhotoShop::dialogueDemandeFloat(const char* titre,const char* question)
{
    return QInputDialog::getDouble(this,titre,question);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string MainWindowPhotoShop::dialogueDemandeFichierOuvrir(const char* question)
{
  QString fileName = QFileDialog::getOpenFileName(this,question, "", "Tous les fichiers (*.*)");
  return fileName.toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string MainWindowPhotoShop::dialogueDemandeFichierEnregistrer(const char* question)
{
  QString fileName = QFileDialog::getSaveFileName(this,question, "", "Tous les fichiers (*.*)");
  return fileName.toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::dialogueDemandeCouleur(const char* message,int* pRouge,int* pVert,int* pBleu)
{
  QColor color = QColorDialog::getColor(Qt::red,this,message);
  *pRouge = color.red();
  *pVert = color.green();
  *pBleu = color.blue();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Clic sur la croix de la fenêtre ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::closeEvent(QCloseEvent *event)
{
  if (event == NULL) {} // pour éviter le warning à la compilation
  // Etape 14 (TO DO)

  QApplication::exit();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les items de menu //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionQuitter_triggered()
{
  // Etape 14 (TO DO)

  QApplication::exit();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionCharger_ImageNB_triggered()
{
  string nom = dialogueDemandeFichierOuvrir("Entrez le nom de l'ImageNG à charger");

  if(nom == "")
  {
    dialogueErreur("Erreur", "Impossible de charger le fichier image.");
    return;
  }

  const char *NomFinal =  nom.c_str();

  ImageNG *ImageAjoutee = new ImageNG();

  ImageAjoutee->importFromFile(NomFinal);

  // Charger le fichier
  if(!ImageAjoutee)
  {
    dialogueErreur("Erreur","ImageNG non chargée !");
    delete ImageAjoutee;
    return;
  }

  ImageAjoutee->setNom(NomFinal);
  
  PhotoShop::getInstance().ajouteImage(ImageAjoutee);

  videTableImages();

  for (int i = 0; i < PhotoShop::getInstance().getImages().getNombreElements(); ++i)
  {
    Image *image = PhotoShop::getInstance().getImages().getElement(i);
    ajouteTupleTableImages(image->getId(), image->getTypeString(), image->getDimensionString(), image->getNom());
  }

  dialogueMessage("Chargement d'image", "L'image a été chargée avec succès.");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionCharger_ImageRGB_triggered()
{
  string nom = dialogueDemandeFichierOuvrir("Entrez le nom de l'ImageRGB à charger");

  if(nom == "")
  {
    dialogueErreur("Erreur", "Impossible de charger le fichier image.");
    return;
  }

  const char *NomFinal =  nom.c_str();

  ImageRGB *ImageAjoutee = new ImageRGB();

  ImageAjoutee->importFromFile(NomFinal);

  // Charger le fichier
  if(!ImageAjoutee)
  {
    dialogueErreur("Erreur","ImageRGB non chargée !");
    delete ImageAjoutee;
    return;
  }

  ImageAjoutee->setNom(NomFinal);
  
  PhotoShop::getInstance().ajouteImage(ImageAjoutee);

  videTableImages();

  for (int i = 0; i < PhotoShop::getInstance().getImages().getNombreElements(); ++i)
  {
    Image *image = PhotoShop::getInstance().getImages().getElement(i);
    ajouteTupleTableImages(image->getId(), image->getTypeString(), image->getDimensionString(), image->getNom());
  }

  dialogueMessage("Chargement d'image", "L'image a été chargée avec succès.");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionEnregistrer_ImageNB_triggered()
{
  // Etape 11 (TO DO)
  int indiceImageSelectionnee = getIndiceImageSelectionnee();

  if (indiceImageSelectionnee == -1)
  {
    dialogueErreur("Erreur", "Aucune image sélectionnée.");
    return;
  }

  Image *image = PhotoShop::getInstance().getImages().getElement(indiceImageSelectionnee);

  image = dynamic_cast<ImageNG *>(image);

  if (image == NULL)
  {
    dialogueErreur("Erreur", "Erreur de type image");
    return;
  }

  string nomFichier = dialogueDemandeFichierEnregistrer("Enregistrer l'ImageNG");

  if (nomFichier == "")
  {
    dialogueErreur("Erreur", "Pas de fichier");
    return;
  }

  string formatFichier = dialogueDemandeTexte("Format du fichier", "Entrez le format du fichier (JPG, BMP, PNG)");

  /*if(formatFichier!="JPG" || formatFichier!="BMP" || formatFichier!="PNG" || formatFichier!="jpg" 
  || formatFichier!="bmp" || formatFichier!="png")
  {
    dialogueErreur("Erreur","Format de l'image entrez incorrecte (JPG,BMP,PNG)");
  }*/

  dynamic_cast<ImageNG *>(image)->exportToFile(nomFichier.c_str(), formatFichier.c_str());

  dialogueMessage("Enregistrement d'image", "L'image a été enregistrée avec succès.");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionEnregistrer_ImageRGB_triggered()
{
  // Etape 11 (TO DO)
  int indiceImageSelectionnee = getIndiceImageSelectionnee();

  if (indiceImageSelectionnee == -1)
  {
    dialogueErreur("Erreur", "Aucune image sélectionnée.");
    return;
  }

  Image *image = PhotoShop::getInstance().getImages().getElement(indiceImageSelectionnee);

  image = dynamic_cast<ImageRGB *>(image);

  if (image == NULL)
  {
    dialogueErreur("Erreur", "Erreur de type image");
    return;
  }

  string nomFichier = dialogueDemandeFichierEnregistrer("Enregistrer l'ImageRGB");

  if (nomFichier == "")
  {
    dialogueErreur("Erreur", "Pas de fichier");
    return;
  }

  string formatFichier = dialogueDemandeTexte("Format du fichier", "Entrez le format du fichier (JPG, BMP, PNG)");

  /*if(formatFichier!="JPG" || formatFichier!="BMP" || formatFichier!="PNG" || formatFichier!="jpg" 
  || formatFichier!="bmp" || formatFichier!="png")
  {
    dialogueErreur("Erreur","Format de l'image entrez incorrecte (JPG,BMP,PNG)");
  }*/

  dynamic_cast<ImageRGB *>(image)->exportToFile(nomFichier.c_str(), formatFichier.c_str());

  dialogueMessage("Enregistrement d'image", "L'image a été enregistrée avec succès.");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionEnregistrer_ImageB_triggered()
{
  // Etape 11 (TO DO)
  int indiceImageSelectionnee = getIndiceImageSelectionnee();

  if (indiceImageSelectionnee == -1)
  {
    dialogueErreur("Erreur", "Aucune image sélectionnée.");
    return;
  }

  Image *image = PhotoShop::getInstance().getImages().getElement(indiceImageSelectionnee);

  image = dynamic_cast<ImageB *>(image);

  if (image == NULL)
  {
    dialogueErreur("Erreur", "Erreur de type image");
    return;
  }

  string nomFichier = dialogueDemandeFichierEnregistrer("Enregistrer l'ImageB");

  if (nomFichier == "")
  {
    dialogueErreur("Erreur", "Pas de fichier");
    return;
  }

  string formatFichier = dialogueDemandeTexte("Format du fichier", "Entrez le format du fichier (JPG, BMP, PNG)");

  /*if(formatFichier!="JPG" || formatFichier!="BMP" || formatFichier!="PNG" || formatFichier!="jpg" 
  || formatFichier!="bmp" || formatFichier!="png")
  {
    dialogueErreur("Erreur","Format de l'image entrez incorrecte (JPG,BMP,PNG)");
  }*/

  dynamic_cast<ImageB *>(image)->exportToFile(nomFichier.c_str(), formatFichier.c_str());

  dialogueMessage("Enregistrement d'image", "L'image a été enregistrée avec succès.");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionImage_selectionn_e_triggered()
{
  // Etape 11 (TO DO)
  int indiceImageSelectionnee = getIndiceImageSelectionnee();

  if (indiceImageSelectionnee == -1)
  {
    dialogueErreur("Erreur", "Aucune image sélectionnée.");
    return;
  }

  PhotoShop::getInstance().supprimeImageParIndice(indiceImageSelectionnee);

  videTableImages();

  for (int i = 0; i < PhotoShop::getInstance().getImages().getNombreElements(); ++i)
  {
    Image *image = PhotoShop::getInstance().getImages().getElement(i);
    ajouteTupleTableImages(image->getId(), image->getTypeString(), image->getDimensionString(), image->getNom());
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionImage_par_id_triggered()
{
  // Etape 11 (TO DO)
  int id = dialogueDemandeInt("Supprimer une image par ID", "Entrez l'ID de l'image à supprimer:");

  PhotoShop::getInstance().supprimeImageParId(id);

  videTableImages();

  for (int i = 0; i < PhotoShop::getInstance().getImages().getNombreElements(); ++i)
  {
    Image *image = PhotoShop::getInstance().getImages().getElement(i);
    ajouteTupleTableImages(image->getId(), image->getTypeString(), image->getDimensionString(), image->getNom());
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionCouleur_TRUE_pour_ImageB_triggered()
{
  // Etape 12 (TO DO)

  int rouge, vert, bleu;
  dialogueDemandeCouleur("Choissisez votre couleur TRUE", &rouge, &vert, &bleu);
  ImageB::couleurTrue.setRouge(rouge);
  ImageB::couleurTrue.setVert(vert);
  ImageB::couleurTrue.setBleu(bleu);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionCouleur_FALSE_pour_imageB_triggered()
{
  // Etape 12 (TO DO)

  int rouge, vert, bleu;
  dialogueDemandeCouleur("Choisissez votre couleur FALSE", &rouge, &vert, &bleu);
  ImageB::couleurFalse.setRouge(rouge);
  ImageB::couleurFalse.setVert(vert);
  ImageB::couleurFalse.setBleu(bleu);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionImporterCSV_triggered()
{
  // Etape 13 (TO DO)

  string nomFichier=dialogueDemandeFichierOuvrir("Entrez le nom du fichier");

  if(nomFichier=="")
  {
    dialogueErreur("Erreur","Entrez un nom de fichier!");
    return;
  }

  int mesImagesImportees=PhotoShop::getInstance().importeImages(nomFichier);

  videTableImages();

  for (int i = 0; i < PhotoShop::getInstance().getImages().getNombreElements(); ++i)
  {
    Image *image = PhotoShop::getInstance().getImages().getElement(i);
    ajouteTupleTableImages(image->getId(), image->getTypeString(), image->getDimensionString(), image->getNom());
  }

  string messageFinal = "Voici le nombre d'images importées :" + to_string(mesImagesImportees);
  dialogueMessage("Images importées",messageFinal.c_str());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionReset_triggered()
{
  // Etape 14 (TO DO)

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions selection sur la table des images ////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_tableWidgetImages_itemSelectionChanged()
{
  // Etape 11 (TO DO)
  int indiceImageSelectionnee = getIndiceImageSelectionnee();

  // Vérifier si une image est sélectionnée
  if (indiceImageSelectionnee == -1)
  {
    // Éviter la sélection automatique lorsque la bibliothèque est vide
    return;
  }

  Image *imageSelectionnee = PhotoShop::getInstance().getImages().getElement(indiceImageSelectionnee);

  setNomImage(imageSelectionnee->getNom());

  ImageNG *imageNG = dynamic_cast<ImageNG *>(imageSelectionnee);
  if (imageNG != nullptr)
  {
    // Si c'est une ImageNG, afficher ses paramètres
    setParametresImageNG(imageNG->getMaximum(), imageNG->getMinimum(), imageNG->getLuminance(), imageNG->getContraste());
  }
  else
  {
    // Si ce n'est pas une ImageNG, vider les champs
    setParametresImageNG();
  }

  if (imageSelectionnee->getTypeString() == "NG")
  {
    setImageNG("selection", dynamic_cast<ImageNG *>(imageSelectionnee));
  }
  else if (imageSelectionnee->getTypeString() == "RGB")
  {
    setImageRGB("selection", dynamic_cast<ImageRGB *>(imageSelectionnee));
  }
  else if (imageSelectionnee->getTypeString() == "B")
  {
    setImageB("selection", dynamic_cast<ImageB *>(imageSelectionnee));
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les boutons ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonModifierNom_clicked()
{
  int indiceImageSelectionnee = getIndiceImageSelectionnee();

  string nouveauNom = getNomImage();

  if (indiceImageSelectionnee == -1)
  {
    dialogueErreur("Erreur", "Aucune image sélectionnée.");
    return;
  }

  Image *imageSelectionnee = PhotoShop::getInstance().getImages().getElement(indiceImageSelectionnee);

  imageSelectionnee->setNom(nouveauNom.c_str());

  videTableImages();

  for (int i = 0; i < PhotoShop::getInstance().getImages().getNombreElements(); ++i)
  {
    Image *image = PhotoShop::getInstance().getImages().getElement(i);
    ajouteTupleTableImages(image->getId(), image->getTypeString(), image->getDimensionString(), image->getNom());
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonOperande1_clicked()
{
  // Etape 12 (TO DO)

  int indice = getIndiceImageSelectionnee();

  if (indice == -1)
  {
    dialogueErreur("Erreur", "Aucune image sélectionnée !");
    return;
  }

  Image *imageSelectionnee = PhotoShop::getInstance().getImages().getElement(indice);

  PhotoShop::getInstance().operande1 = imageSelectionnee;

  if (dynamic_cast<ImageNG *>(imageSelectionnee) != nullptr)
  {
    setImageNG("operande1", dynamic_cast<ImageNG *>(imageSelectionnee));
  }
  else if (dynamic_cast<ImageRGB *>(imageSelectionnee) != nullptr)
  {
    setImageRGB("operande1", dynamic_cast<ImageRGB *>(imageSelectionnee));
  }
  else if (dynamic_cast<ImageB *>(imageSelectionnee) != nullptr)
  {
    setImageB("operande1", dynamic_cast<ImageB *>(imageSelectionnee));
  }
  else
  {
    dialogueErreur("Erreur", "Type d'image non pris en charge.");
  }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonSupprimeOperande1_clicked()
{
  // Etape 12 (TO DO)
  PhotoShop::getInstance().operande1 = NULL;

  setImageNG("operande1", NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonOperande2_clicked()
{
  // Etape 12 (TO DO)

  int indice = getIndiceImageSelectionnee();

  if (indice == -1)
  {
    dialogueErreur("Erreur", "Aucune image sélectionnée !");
    return;
  }

  Image *imageSelectionnee = PhotoShop::getInstance().getImages().getElement(indice);

  PhotoShop::getInstance().operande2 = imageSelectionnee;

  if (dynamic_cast<ImageNG *>(imageSelectionnee) != nullptr)
  {
    setImageNG("operande2", dynamic_cast<ImageNG *>(imageSelectionnee));
  }
  else if (dynamic_cast<ImageRGB *>(imageSelectionnee) != nullptr)
  {
    setImageRGB("operande2", dynamic_cast<ImageRGB *>(imageSelectionnee));
  }
  else if (dynamic_cast<ImageB *>(imageSelectionnee) != nullptr)
  {
    setImageB("operande2", dynamic_cast<ImageB *>(imageSelectionnee));
  }
  else
  {
    dialogueErreur("Erreur", "Type d'image non pris en charge.");
  }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonSupprimerOperande2_clicked()
{
  // Etape 12 (TO DO)
  PhotoShop::getInstance().operande2 = NULL;

  setImageNG("operande2", NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonResultat_clicked()
{
  // Etape 12 (TO DO)

  if (PhotoShop::getInstance().resultat != nullptr)
  {
    // Ajouter l'image "résultat" à la bibliothèque (PhotoShop)
    PhotoShop::getInstance().ajouteImage(PhotoShop::getInstance().resultat);

    // Mettre à jour la table des images
    videTableImages();

    for (int i = 0; i < PhotoShop::getInstance().getImages().getNombreElements(); ++i)
    {
      Image *image = PhotoShop::getInstance().getImages().getElement(i);
      ajouteTupleTableImages(image->getId(), image->getTypeString(), image->getDimensionString(), image->getNom());
    }

    // Remettre le pointeur resultat de PhotoShop à NULL

    PhotoShop::getInstance().resultat = nullptr;

    // Effacer l'image "résultat" en appelant la méthode setImageXXX()
    setImageNG("resultat", nullptr); // Remplacez ceci par la méthode appropriée si nécessaire
  }
  else
  {
    dialogueErreur("Erreur", "Pas d'image résultat à ajouter.");
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonSupprimerResultat_clicked()
{
  // Etape 12 (TO DO)

  if (PhotoShop::getInstance().resultat != NULL)
  {
    string Leresultat = PhotoShop::getInstance().resultat->getTypeString();

    delete PhotoShop::getInstance().resultat;

    PhotoShop::getInstance().resultat =NULL;

    if (Leresultat == "NG")
    {
      setImageNG("resultat",NULL);
      return;
    }
    if (Leresultat == "RGB")
    {
      setImageRGB("resultat", NULL);
      return;
    }
    if (Leresultat == "B")
    {
      setImageB("resultat",NULL);
      return;
    }
    else
    {
      dialogueErreur("Erreur", "Type d'image non pris en charge.");
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonTraitement_clicked()
{
  // Etape 12 (TO DO)
  string traitement = getTraitementSelectionne();
  int valeur = 0;

  if (PhotoShop::getInstance().resultat != NULL)
  {
    delete PhotoShop::getInstance().resultat;
    PhotoShop::getInstance().resultat = NULL;
  }
  setResultatBoolean(-1);

  if (PhotoShop::getInstance().operande1 != NULL)
  {
    try
    {
      if (traitement == "Eclaircir (+ val)")
      {
        valeur = dialogueDemandeInt("Eclaircir (+ val)", "Veuillez saisir la valeur à ajouter");

        ImageNG *operande1 = dynamic_cast<ImageNG *>(PhotoShop::getInstance().operande1);

        if (operande1 != nullptr && valeur != 0)
        {
          // Créer une copie de l'image
          PhotoShop::getInstance().resultat = new ImageNG(*operande1 + valeur);

          // Modifier le nom de la nouvelle image
          string nouveauNom = string(PhotoShop::getInstance().operande1->getNom()) + "+" + to_string(valeur);
          PhotoShop::getInstance().resultat->setNom(nouveauNom.c_str());

          // Mettre à jour l'interface
          setImageNG("resultat", dynamic_cast<ImageNG *>(PhotoShop::getInstance().resultat));
        }

        return;
      }

      if (traitement == "Eclaircir (++)")
      {
        ImageNG *imageNG = dynamic_cast<ImageNG *>(PhotoShop::getInstance().operande1);
        
        if (imageNG)
        {
          ImageNG result = (*imageNG)++;
          PhotoShop::getInstance().resultat = new ImageNG(result);
          setImageNG("resultat", dynamic_cast<ImageNG *>(PhotoShop::getInstance().resultat));
        }
        return;
      }

      if (traitement == "Assombrir (- val)")
      {
        valeur = dialogueDemandeInt("Assombrir (- val)", "Veuillez saisir la valeur à soustraire");

        ImageNG *operande1 = dynamic_cast<ImageNG *>(PhotoShop::getInstance().operande1);

        if (operande1 != NULL && valeur != 0)
        {
          // Créer une copie de l'image
          PhotoShop::getInstance().resultat = new ImageNG(*operande1 - valeur);

          // Modifier le nom de la nouvelle image
          string nouveauNom = string(PhotoShop::getInstance().operande1->getNom()) + "-" + to_string(valeur);
          PhotoShop::getInstance().resultat->setNom(nouveauNom.c_str());

          // Mettre à jour l'interface
          setImageNG("resultat", dynamic_cast<ImageNG *>(PhotoShop::getInstance().resultat));
        }

        return;
      }

      if (traitement == "Assombrir (--)")
      {
        ImageNG *imageNG = dynamic_cast<ImageNG *>(PhotoShop::getInstance().operande1);
        
        if (imageNG)
        {
          ImageNG result = (*imageNG)--;
          PhotoShop::getInstance().resultat = new ImageNG(result);
          setImageNG("resultat", dynamic_cast<ImageNG *>(PhotoShop::getInstance().resultat));
        }

        return;
      }

      if (traitement == "Différence")
      {
        // Vérifier si operande2 est bien défini
        if (PhotoShop::getInstance().operande2 != NULL)
        {
          ImageNG *operande1 = dynamic_cast<ImageNG *>(PhotoShop::getInstance().operande1);
          ImageNG *operande2 = dynamic_cast<ImageNG *>(PhotoShop::getInstance().operande2);

          if (operande1 != NULL && operande2 != NULL)
          {

            ImageNG resultatDifference = *operande1 - *operande2;
            PhotoShop::getInstance().resultat = new ImageNG(resultatDifference);
            setImageNG("resultat", &resultatDifference);
          }
        }
        else
        {
          dialogueErreur("Erreur", "Pas d'opérande 2");
        }

        return;
      }

      if (traitement == "Comparaison (==)")
      {
        if (PhotoShop::getInstance().operande2 != NULL)
        {
          if (PhotoShop::getInstance().operande1 == PhotoShop::getInstance().operande2)
          {
            setResultatBoolean(1);
          }
          else
          {
            setResultatBoolean(0);
          }
        }
        else
        {
          dialogueErreur("Erreur", "Pas d'opérande 2");
        }
        
        return;
      }

      if (traitement == "Comparaison (<)")
      {
        // Vérifier si operande2 est bien défini
        if (PhotoShop::getInstance().operande2 != NULL)
        {
          if (PhotoShop::getInstance().operande1 < PhotoShop::getInstance().operande2)
          {
            dialogueMessage("Comparaison", "L'opérande 1 est plus petit que l'opérande 2");
          }
          else if (PhotoShop::getInstance().operande1 > PhotoShop::getInstance().operande2)
          {
            dialogueMessage("Comparaison", "L'opérande 2 est plus petit que l'opérande 1");
          }
        }
        else
        {
          dialogueErreur("Erreur", "Pas d'opérande 2");
        }

        return;
      }
      if (traitement == "Comparaison (>)")
      {
        // Vérifier si operande2 est bien défini
        if (PhotoShop::getInstance().operande2 != nullptr)
        {
          if (PhotoShop::getInstance().operande1 > PhotoShop::getInstance().operande2)
          {
            dialogueMessage("Comparaison", "L'opérande 1 est plus grand que l'opérande 2");
          }
          else if (PhotoShop::getInstance().operande1 < PhotoShop::getInstance().operande2)
          {
            dialogueMessage("Comparaison", "L'opérande 2 est plus grand que l'opérande 1");
          }
        }
        else
        {
          dialogueErreur("Erreur", "Pas d'opérande 2");
        }

        return;
      }

      if (traitement == "Seuillage")
      {
        valeur = dialogueDemandeInt("Valeur", "Veuillez saisir la valeur du seuil");
        ImageB resultatSeuillage = Traitements::Seuillage(dynamic_cast<const ImageNG &>(*PhotoShop::getInstance().operande1),valeur);

        PhotoShop::getInstance().resultat = new ImageB(resultatSeuillage);
        setImageB("resultat", &resultatSeuillage);
        return;
      }

      if (traitement == "Filtre moyenneur")
      {
        valeur = dialogueDemandeInt("Filtre moyenneur", "Veuillez saisir la taille du filtre");
        ImageNG resultatFiltreMoyenneur = Traitements::FiltreMoyenneur(dynamic_cast<const ImageNG &>(*PhotoShop::getInstance().operande1),valeur);

        PhotoShop::getInstance().resultat = new ImageNG(resultatFiltreMoyenneur);
        setImageNG("resultat", &resultatFiltreMoyenneur);
        return;
      }

      if (traitement == "Filtre médian")
      {
          valeur = dialogueDemandeInt("Valeur", "Veuillez saisir la taille du filtre");
          ImageNG resultatFiltreMedian = Traitements::FiltreMedian(dynamic_cast<const ImageNG &>(*PhotoShop::getInstance().operande1), valeur);

          // Utiliser l'allocation sans new
          PhotoShop::getInstance().resultat = new ImageNG();
          *(PhotoShop::getInstance().resultat) = resultatFiltreMedian;

          // Mettre à jour l'interface
          setImageNG("resultat", dynamic_cast<ImageNG *>(PhotoShop::getInstance().resultat));

          return;
      }

      if (traitement == "Erosion")
      {
        valeur = dialogueDemandeInt("Erosion", "Veuillez saisir la taille du filtre");
        ImageNG resultatErosion = Traitements::Erosion(dynamic_cast<const ImageNG &>(*PhotoShop::getInstance().operande1),valeur);

        PhotoShop::getInstance().resultat = new ImageNG(resultatErosion);
        setImageNG("resultat", &resultatErosion);
        return;
      }

      if (traitement == "Dilatation")
      {
        valeur = dialogueDemandeInt("Dilatation", "Veuillez saisir la taille du filtre");
        ImageNG resultatDilatation = Traitements::Dilatation(dynamic_cast<const ImageNG &>(*PhotoShop::getInstance().operande1),valeur);

        PhotoShop::getInstance().resultat = new ImageNG(resultatDilatation);
        setImageNG("resultat", &resultatDilatation);
        return;
      }

      if (traitement == "Négatif")
      {
        ImageNG negatif;
        negatif = Traitements::Negatif(dynamic_cast<const ImageNG &>(*PhotoShop::getInstance().operande1));

        PhotoShop::getInstance().resultat = new ImageNG(negatif);
        setImageNG("resultat", &negatif);
        return;
      }
    }
    catch (const XYException &exception)
    {
      dialogueErreur("Erreur XYException", exception.getMessage().c_str());
    }
  }
  else
  {
    dialogueErreur("Erreur", "Pas d'opérande 1");
  }
}