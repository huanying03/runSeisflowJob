#HEAD=suhead.h sufile.h
SOURCE=sujob.cpp

OBJ=sujob

INC_DIR=../../include
LIB_DIR=../../lib

all:
	g++ ${SOURCE} -o ${OBJ} -I${INC_DIR} -L${LIB_DIR} -lmsg -lsufile

BIN=../../bin

install:
	cp ${OBJ} ${BIN}
clean:
	rm ${OBJ} ${BIN}/${OBJ} 

