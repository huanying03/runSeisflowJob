HEAD=msg.h
SOURCE=msg.cpp

LIB=libmsg.so

INC_DIR=../../include
LIB_DIR=../../lib

all:
	g++ -c ${SOURCE} -o ${LIB}

install:
	cp ${HEAD} ${INC_DIR}
	cp ${LIB} ${LIB_DIR}
clean:
	rm ${INC_DIR}/${HEAD}
	rm ${LIB_DIR}/${LIB}

