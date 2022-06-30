# Usage:
# make	# compile grid tools
# make clean  # remove object files

.PHONY = all

CPP = g++

SRCS := $(wildcard *.cpp)
OBJ := $(SRCS:%.cpp=%.o)
BINS := $(SRCS:%.cpp=%)

all: ${OBJ}
	$(MAKE) -C Ugrid/ '.RECIPEPREFIX+='
	$(MAKE) -C Plt/ '.RECIPEPREFIX+='
	$(MAKE) -C Gamma/ '.RECIPEPREFIX+='
	$(MAKE) -C Ugr/ '.RECIPEPREFIX+='
	${CPP} -o convertPltToVtk convertPltToVtk.o Plt/Var.o Plt/Plt.o Plt/members/*.o
	${CPP} -o readGammaWriteGamma readGammaWriteGamma.o Gamma/Gamma.o Gamma/members/*.o Gamma/libMeshb/*.o
	${CPP} -o convertPltToGamma convertPltToGamma.o Plt/Plt.o Plt/members/*.o Gamma/Gamma.o Gamma/members/*.o Gamma/libMeshb/*.o
	${CPP} -o convertGammaToPlt convertGammaToPlt.o Plt/Plt.o Plt/members/*.o Gamma/Gamma.o Gamma/members/*.o Gamma/libMeshb/*.o
	${CPP} -o convertUgrToGamma convertUgrToGamma.o Ugr/Ugr.o Ugr/members/*.o Gamma/Gamma.o Gamma/members/*.o Gamma/libMeshb/*.o
	${CPP} -o scaleUgrid scaleUgrid.o Ugrid/Ugrid.o Ugrid/members/*.o
	${CPP} -o convertGridToVtk convertGridToVtk.o Gamma/Gamma.o Gamma/members/*.o Gamma/libMeshb/*.o Plt/Plt.o Plt/members/*.o Ugrid/Ugrid.o Ugrid/members/*.o Ugr/Ugr.o Ugr/members/*.o

OBJ: ${SRCS}
	${CPP} -c $<

clean:
	$(MAKE) -C Ugrid/ 'clean' '.RECIPEPREFIX+='
	$(MAKE) -C Plt/ 'clean' '.RECIPEPREFIX+='
	$(MAKE) -C Gamma/ 'clean' '.RECIPEPREFIX+='
	$(MAKE) -C Ugr/ 'clean' '.RECIPEPREFIX+='
	rm -rvf *.o
	rm -rvf convertPltToVtk
	rm -rvf readGammaWriteGamma
	rm -rvf convertPltToGamma
	rm -rvf convertGammaToPlt
	rm -rvf convertUgrToGamma
	rm -rvf scaleUgrid
	rm -rvf convertGridToVtk
