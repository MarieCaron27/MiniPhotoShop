.SILENT:

Test9:	Test9.cpp Traitements.o ArrayList.o Iterateur.o Image.o Couleur.o ImageNG.o Dimension.o MyQT.o ImageRGB.o ImageB.o Exception.o XYException.o RGBException.o
	echo "Création de Test9"
	g++ Test9.cpp -o Test9 Traitements.o MyQT.o Iterateur.o ArrayList.o Exception.o XYException.o RGBException.o ImageB.o ImageRGB.o Image.o Couleur.o ImageNG.o Dimension.o -lSDL -lpthread -Wl,-O1 -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so

Exception.o:	Exception.cpp Exception.h
	echo "Création d'Exception.o"
	g++ Exception.cpp -c -o Exception.o

XYException.o:	XYException.cpp XYException.h
	echo "Création d'XYException.o"
	g++ XYException.cpp -c -o XYException.o

RGBException.o:	RGBException.cpp RGBException.h
	echo "Création de RGBException.o"
	g++ RGBException.cpp -c -o RGBException.o

Image.o:	Image.cpp Image.h
	echo "Création de Image.o"
	g++ Image.cpp -c -o Image.o

ImageNG.o:	ImageNG.cpp ImageNG.h
	echo "Création de ImageNG.o"
	g++ ImageNG.cpp -c -o ImageNG.o

ImageRGB.o:	ImageRGB.cpp ImageRGB.h
	echo "Création de ImageRGB.o"
	g++ ImageRGB.cpp -c -o ImageRGB.o

ImageB.o:	ImageB.cpp ImageB.h
	echo "Création de ImageB.o"
	g++ ImageB.cpp -c -o ImageB.o

Couleur.o:	Couleur.cpp Couleur.h
	echo "Création de Couleur.o"
	g++ Couleur.cpp -c -o Couleur.o

Dimension.o:	Dimension.cpp Dimension.h
	echo "Création de Dimension.o"
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

MyQT.o:	MyQT.cpp MyQT.h
	echo "Création de MyQT.o"
	g++ MyQT.cpp -c -o MyQT.o -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++

clean:
	rm *.o
