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
	${CPP} -o convertUgridToVtk convertUgridToVtk.o Ugrid/Ugrid.o Ugrid/members/*.o
	${CPP} -o convertPltToVtk convertPltToVtk.o Plt/Plt.o Plt/members/*.o
	${CPP} -o convertGammaToVtk convertGammaToVtk.o Gamma/Gamma.o Gamma/members/*.o Gamma/libMeshb/*.o
	${CPP} -o readGammaWriteGamma readGammaWriteGamma.o Gamma/Gamma.o Gamma/members/*.o Gamma/libMeshb/*.o
	${CPP} -o convertPltToGamma convertPltToGamma.o Plt/Plt.o Plt/members/*.o Gamma/Gamma.o Gamma/members/*.o Gamma/libMeshb/*.o
	${CPP} -o convertGammaToPlt convertGammaToPlt.o Plt/Plt.o Plt/members/*.o Gamma/Gamma.o Gamma/members/*.o Gamma/libMeshb/*.o       
	${CPP} -o convertCbsToVtk convertCbsToVtk.o Plt/*.o Plt/members/*.o
	${CPP} -o scaleUgrid scaleUgrid.o Ugrid/Ugrid.o Ugrid/members/*.o

OBJ: ${SRCS}
	${CPP} -c $<

clean:
	$(MAKE) -C Ugrid/ 'clean' '.RECIPEPREFIX+='
	$(MAKE) -C Plt/ 'clean' '.RECIPEPREFIX+='
	$(MAKE) -C Gamma/ 'clean' '.RECIPEPREFIX+='
	rm -rvf *.o
	rm -rvf convertUgridToVtk
	rm -rvf convertPltToVtk
	rm -rvf convertGammaToVtk
	rm -rvf readGammaWriteGamma
	rm -rvf convertPltToGamma
	rm -rvf convertGammaToPlt
	rm -rvf convertCbsToVtk
	rm -rvf scaleUgrid
