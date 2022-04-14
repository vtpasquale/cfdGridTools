# Usage:
# make        # compile grid tools
# make clean  # remove object files

.PHONY = all

CPP = g++

SRCS := $(wildcard *.cpp)
OBJ := $(SRCS:%.cpp=%.o)
BINS := $(SRCS:%.cpp=%)

all: ${OBJ}
        $(MAKE) -C Ugrid/ '.RECIPEPREFIX+='
        $(MAKE) -C Plt/ '.RECIPEPREFIX+='
        ${CPP} -o convertUgridToVtk convertUgridToVtk.o Ugrid/Ugrid.o Ugrid/members/*.o
        ${CPP} -o convertPltToVtk convertPltToVtk.o Plt/Plt.o Plt/members/*.o

OBJ: ${SRCS}
        ${CPP} -c $<

clean:
        $(MAKE) -C Ugrid/ 'clean' '.RECIPEPREFIX+='
        $(MAKE) -C Plt/ 'clean' '.RECIPEPREFIX+='
        rm -rvf *.o
        rm -rvf convertUgridToVtk
        rm -rvf convertPltToVtk
