.SILENT:

Test5:	Test5.cpp Image.o Couleur.o ImageNG.o Dimension.o MyQT.o ImageRGB.o ImageB.o
	echo "Création de Test5"
	g++ Test5.cpp -o Test5 MyQT.o ImageB.o ImageRGB.o Image.o Couleur.o ImageNG.o Dimension.o -lSDL -lpthread -Wl,-O1 -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so

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

MyQT.o:	MyQT.cpp MyQT.h
	echo "Création de MyQT.o"
	g++ MyQT.cpp -c -o MyQT.o -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++

clean:
	rm *.o
