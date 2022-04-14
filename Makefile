# Usage:
# make        # compile grid tools
# make clean  # remove object files

.PHONY = all

CPP = g++

SRCS := $(wildcard *.cpp)
OBJ := $(SRCS:%.cpp=%.o)
BINS := $(SRCS:%.cpp=%)

# Call Ugrid make - this should only be conditional on no executables

all: ${OBJ}
        $(MAKE) -C Ugrid/ '.RECIPEPREFIX+='
        ${CPP} -o convertUgridToVtk convertUgridToVtk.o Ugrid/Ugrid.o Ugrid/members/*.o

OBJ: ${SRCS}
        ${CPP} -c $<

clean:
        $(MAKE) -C Ugrid/ 'clean' '.RECIPEPREFIX+='
        rm -rvf *.o
