flags=-Wall -lbsd -lc
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
	 $(src)map.o \
	 $(src)utils.o \

all: compile clean

compile: $(objs)
	@[ -d "$(build)" ] || { mkdir "$(build)"; }
	$(out)$(target) $(objs) $(flags)

example%:
	$(target) $@.txt

clean:
		rm $(objs)

run: all
	$(target)
