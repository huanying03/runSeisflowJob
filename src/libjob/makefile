HEAD=job.h
SOURCE=job.cpp

LIB=libjob.so

INC_DIR=../../include
LIB_DIR=../../lib

all:
	g++  ${SOURCE} -o ${LIB} -g -shared -fPIC -I${INC_DIR}  

install:
	cp ${HEAD} ${INC_DIR}
	cp ${LIB} ${LIB_DIR}
clean:
	rm ${INC_DIR}/${HEAD}
	rm ${LIB_DIR}/${LIB}

