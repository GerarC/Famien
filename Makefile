flags=-Wall -Wextra
libs=-lbsd -lglfw -lGL -lGLU -lm -lX11 -lGLEW -lEGL -lOpenGL -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/harfbuzz -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/sysprof-6 -pthread
obj=gcc -c 
out=gcc -o 
name=famien
src=./src/
icd=./include/
build=./build/
target=$(build)$(name)

objs=src/main.o \
	 $(src)cpu6502.o \
	 $(src)bus.o \
	 $(src)window.o \
	 $(src)map.o \
	 $(src)utils.o \

all: compile clean run

compile: $(objs)
	@[ -d "$(build)" ] || { mkdir "$(build)"; }
	$(out)$(target) $(objs) $(flags) $(libs)

example%:
	$(target) $@.txt

clean:
		rm $(objs)

run: 
	$(target)
