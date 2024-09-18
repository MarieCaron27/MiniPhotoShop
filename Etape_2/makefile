Test2:	Test2.cpp ImageNG.o Dimension.o
		g++ Test2.cpp ImageNG.o Dimension.o -o Test2

ImageNG.o:	ImageNG.h ImageNG.cpp
	g++ ImageNG.cpp -c

Dimension.o:	Dimension.h Dimension.cpp
	g++ Dimension.cpp -c

clean:
	rm *.o	