#!/bin/sh
# default : LD_LIBRARY_PATH=~/.c9/local/lib

# new:

#setenv LD_LIBRARY_PATH ~/workspace/runSeisflowJob/lib:${LD_LIBRARY_PATH}
LD_LIBRARY_PATH=~/workspace/runSeisflowJob/lib:${LD_LIBRARY_PATH}
export LD_LIBRARY_PATH