flags=-Wall -Wextra
libs=-lbsd -lglfw -lGL -lGLU -lm -lX11 -lGLEW -lEGL -lOpenGL
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

all: compile clean

compile: $(objs)
	@[ -d "$(build)" ] || { mkdir "$(build)"; }
	$(out)$(target) $(objs) $(flags) $(libs)

example%:
	$(target) $@.txt

clean:
		rm $(objs)

run: all
	$(target)
