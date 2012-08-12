#Makefile de Visual Divel Start
#(C) Adrián Arroyo Calle 2012
# Macros

CC = g++
CFLAGS = `wx-config --cppflags` `pkg-config --cflags glib-2.0 gtk+-2.0`
PRE = -DIDIOMA=ES -DLINUX
SRC = inicio.cpp
OBJ = VarGlobal.o Inicio.o save.o tren.o chr_taskbar.o dkey.o police.o hiper.o golf.o dialogbox.o
EXIT = Azpazeta
LIBFLAGS = `wx-config --libs` `pkg-config --libs glib-2.0 gtk+-2.0` -L. -lnotify -lmodloader -lazpupdater


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
golf.o:
	g++ -c golf.cpp -o golf.o $(PRE) $(CFLAGS)
dialogbox.o:
	g++ -c dialogbox.cpp -o dialogbox.o $(PRE) $(CFLAGS)
chr_taskbar.o:
	g++ -c chr_taskbar.cpp -o chr_taskbar.o $(PRE) $(CFLAGS)
manual:
	g++ -c inicio.cpp $(CFLAGS) -DIDIOMA=ES -o inicio.o
	g++ -o Azpazeta inicio.o $(LIBFLAGS) 
modloader:
	g++ -fPIC -c -o libmodloader.o libmodloader.cpp $(CFLAGS)
	g++ -shared -fPIC -o libmodloader.so libmodloader.o
	sudo cp libmodloader.so /opt/extras.ubuntu.com/azpazeta/lib/
azpupdater:
	g++ -fPIC -c -o libazpupdater.o libazpupdater.cpp $(CFLAGS)
	g++ -shared -fPIC -o libazpupdater.so libazpupdater.o
	sudo cp libazpupdater.so /opt/extras.ubuntu.com/azpazeta/lib/



clean:
	$(RM) $(OBJ)

# Reglas implicitas



