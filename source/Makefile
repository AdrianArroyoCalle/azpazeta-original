#Makefile de Visual Divel Start
#(C) Adrián Arroyo Calle 2012
# Macros

CC = g++
CFLAGS = `wx-config --cppflags` `pkg-config --cflags glib-2.0 gtk+-2.0`
SRC = inicio.cpp
OBJ = VarGlobal.o Inicio.o save.o tren.o chr_taskbar.o
EXIT = Azpazeta
LIBFLAGS = `wx-config --libs` `pkg-config --libs glib-2.0 gtk+-2.0` -lnotify


# Reglas explicitas

all: $(OBJ)
	g++ -o Azpazeta $(OBJ) $(LIBFLAGS) 
Inicio.o:
	g++ -c inicio.cpp -o Inicio.o -DIDIOMA=ES $(CFLAGS)
VarGlobal.o:
	g++ -c VarGlobal.cpp -o VarGlobal.o $(CFLAGS)
save.o:
	g++ -c save.cpp -o save.o -DIDIOMA=ES $(CFLAGS)
tren.o:
	g++ -c tren.cpp -o tren.o -DIDIOMA=ES $(CFLAGS)
chr_taskbar.o:
	g++ -c chr_taskbar.cpp -o chr_taskbar.o $(CFLAGS)
manual:
	g++ -c inicio.cpp $(CFLAGS) -DIDIOMA=ES -o inicio.o
	g++ -o Azpazeta inicio.o $(LIBFLAGS) 

clean:
	$(RM) $(OBJ)

# Reglas implicitas



