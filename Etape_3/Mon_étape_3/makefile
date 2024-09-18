.SILENT:

Test3.o:	Test3.cpp MyQT.o ImageNG.o Dimension.o
	echo "Création de Test3"
	g++ Test3.cpp -o Test3 MyQT.o ImageNG.o Dimension.o -lSDL -lpthread -Wl,-O1 -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++/usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so

MyQT.o:	MyQT.cpp
	echo "Création de MyQT"
	g++ -c MyQT.cpp -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++


ImageNG.o:	ImageNG.h ImageNG.cpp
	echo "Création de ImageNG"
	g++ ImageNG.cpp -c

Dimension.o:	Dimension.h Dimension.cpp
	echo "Création de Dimension"
	g++ Dimension.cpp -c

clean:
	rm *.o
