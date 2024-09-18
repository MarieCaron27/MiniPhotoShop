.SILENT:

ApplicPhotoShop:	moc_mainwindowphotoshop.o mainwindowphotoshop.o main.o PhotoShop.o Traitements.o ArrayList.o Iterateur.o Image.o Couleur.o ImageNG.o Dimension.o MyQT.o ImageRGB.o ImageB.o Exception.o XYException.o RGBException.o
	echo "Création d'ApplicPhotoShop"
	g++ -o ApplicPhotoShop moc_mainwindowphotoshop.o mainwindowphotoshop.o main.o PhotoShop.o Traitements.o ArrayList.o Iterateur.o Image.o Couleur.o ImageNG.o Dimension.o MyQT.o ImageRGB.o ImageB.o Exception.o XYException.o RGBException.o /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so -lpthread

Exception.o:	Exception.cpp Exception.h
	echo "Création d'Exception"
	g++ Exception.cpp -c -o Exception.o

XYException.o:	XYException.cpp XYException.h
	echo "Création d'XYException"
	g++ XYException.cpp -c -o XYException.o

RGBException.o:	RGBException.cpp RGBException.h
	echo "Création de RGBException"
	g++ RGBException.cpp -c -o RGBException.o

Image.o:	Image.cpp Image.h
	echo "Création de Image"
	g++ Image.cpp -c -o Image.o

ImageNG.o:	ImageNG.cpp ImageNG.h
	echo "Création de ImageNG"
	g++ ImageNG.cpp -c -o ImageNG.o

ImageRGB.o:	ImageRGB.cpp ImageRGB.h
	echo "Création de ImageRGB"
	g++ ImageRGB.cpp -c -o ImageRGB.o

ImageB.o:	ImageB.cpp ImageB.h
	echo "Création de ImageB"
	g++ ImageB.cpp -c -o ImageB.o

Couleur.o:	Couleur.cpp Couleur.h
	echo "Création de Couleur"
	g++ Couleur.cpp -c -o Couleur.o

Dimension.o:	Dimension.cpp Dimension.h
	echo "Création de Dimension"
	g++ Dimension.cpp -c -o Dimension.o

ArrayList.o:	ArrayList.cpp ArrayList.h
	echo "Création d'ArrayList"
	g++ ArrayList.cpp -c -o ArrayList.o

Iterateur.o:	Iterateur.cpp Iterateur.h
	echo "Création d'Iterateur"
	g++ Iterateur.cpp -c -o Iterateur.o

Traitements.o:	Traitements.cpp Traitements.h
	echo "Création de Traitements"
	g++ Traitements.cpp -c -o Traitements.o

PhotoShop.o:	PhotoShop.cpp PhotoShop.h
	echo "Création de PhotoShop"
	g++ PhotoShop.cpp -c -o PhotoShop.o

MyQT.o:	MyQT.cpp MyQT.h
	echo "Création de MyQT"
	g++ MyQT.cpp -c -o MyQT.o -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++

moc_mainwindowphotoshop.o:	moc_mainwindowphotoshop.cpp mainwindowphotoshop.h
	echo "Creation de moc_mainwindowphotoshop"
	g++ -c -pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ -o moc_mainwindowphotoshop.o moc_mainwindowphotoshop.cpp

mainwindowphotoshop.o:	mainwindowphotoshop.cpp mainwindowphotoshop.h ui_mainwindowphotoshop.h 	
	echo "Creation de mainwindowphotoshop"
	g++ -c -pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ -o mainwindowphotoshop.o mainwindowphotoshop.cpp

main.o:	main.cpp
	echo "Creation de main"
	g++ -c -pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ -o main.o main.cpp

clean:
	rm -f Classes/*.o core
	rm -f ../MyQT/*.o core
	rm -f Interface/*.o core
	echo "Suppression des fichiers .o"

clobber: clean
	rm ApplicPhotoShop
	echo "Suppression de l'executable ApplicPhotoShop"
