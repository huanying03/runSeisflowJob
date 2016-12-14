HEAD=suhead.h sufile.h
SOURCE=sufile.cpp

LIB=libsufile.so

INC_DIR=../../include
LIB_DIR=../../lib

all:
	g++ -c ${SOURCE} -o ${LIB} -I${INC_DIR}


install:
	cp ${HEAD} ${INC_DIR}
	cp ${LIB} ${LIB_DIR}
clean:
	rm  ${LIB}

