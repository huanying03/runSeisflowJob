HEAD=addnoise.h
SOURCE=addnoise.cpp

LIB=libaddnoise.so

INC_DIR=../../include
LIB_DIR=../../lib

all:
	g++  ${SOURCE} -o ${LIB} -I${INC_DIR} -std=c++11 -g -shared -fPIC

install:
	cp ${HEAD} ${INC_DIR}
	cp ${LIB} ${LIB_DIR}
clean:
	rm ${INC_DIR}/${HEAD}
	rm ${LIB_DIR}/${LIB}

