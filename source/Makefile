#Makefile de Visual Divel Start
#(C) Adrián Arroyo Calle 2012
# Macros

CC = g++
CFLAGS = `wx-config --cppflags` `pkg-config --cflags glib-2.0 gtk+-2.0`
PRE = -DIDIOMA=ES -DLINUX
SRC = inicio.cpp
OBJ = VarGlobal.o Inicio.o save.o tren.o chr_taskbar.o dkey.o police.o hiper.o
EXIT = Azpazeta
LIBFLAGS = `wx-config --libs` `pkg-config --libs glib-2.0 gtk+-2.0` -lnotify


# Reglas explicitas

all: $(OBJ)
	g++ -o Azpazeta $(OBJ) $(LIBFLAGS) 
Inicio.o:
	g++ -c inicio.cpp -o Inicio.o $(PRE) $(CFLAGS)
dkey.o:
	g++ -c dkey.cpp -o dkey.o $(PRE) $(CFLAGS)
police.o:
	g++ -c police.cpp -o police.o $(PRE) $(CFLAGS)
VarGlobal.o:
	g++ -c VarGlobal.cpp -o VarGlobal.o $(PRE) $(CFLAGS)
save.o:
	g++ -c save.cpp -o save.o $(PRE) $(CFLAGS)
tren.o:
	g++ -c tren.cpp -o tren.o $(PRE) $(CFLAGS)
hiper.o:
	g++ -c hiper.cpp -o hiper.o $(PRE) $(CFLAGS)
chr_taskbar.o:
	g++ -c chr_taskbar.cpp -o chr_taskbar.o $(PRE) $(CFLAGS)
manual:
	g++ -c inicio.cpp $(CFLAGS) -DIDIOMA=ES -o inicio.o
	g++ -o Azpazeta inicio.o $(LIBFLAGS) 

clean:
	$(RM) $(OBJ)

# Reglas implicitas



