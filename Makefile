# Usage:
# make	# compile grid tools
# make clean  # remove object files

.PHONY = all

CXX = g++
CXXFLAGS = -std=c++17 

SRCS := $(wildcard *.cpp)
OBJ := $(SRCS:%.cpp=%.o)
BINS := $(SRCS:%.cpp=%)

all: ${OBJ}
	$(MAKE) -C Ugrid/
	$(MAKE) -C Plt/
	$(MAKE) -C Gamma/
	$(MAKE) -C Ugr/
	${CXX} $(CXXFLAGS) -o convertPltToVtk convertPltToVtk.o Plt/Var.o Plt/Plt.o Plt/members/*.o
	${CXX} $(CXXFLAGS) -o readGammaWriteGamma readGammaWriteGamma.o Gamma/Gamma.o Gamma/members/*.o Gamma/libMeshb/*.o
	${CXX} $(CXXFLAGS) -o convertPltToGamma convertPltToGamma.o Plt/Plt.o Plt/members/*.o Gamma/Gamma.o Gamma/members/*.o Gamma/libMeshb/*.o
	${CXX} $(CXXFLAGS) -o convertGammaToPlt convertGammaToPlt.o Plt/Plt.o Plt/members/*.o Gamma/Gamma.o Gamma/members/*.o Gamma/libMeshb/*.o
	${CXX} $(CXXFLAGS) -o convertUgrToGamma convertUgrToGamma.o Ugr/Ugr.o Ugr/members/*.o Gamma/Gamma.o Gamma/members/*.o Gamma/libMeshb/*.o
	${CXX} $(CXXFLAGS) -o convertGammaToUgr convertGammaToUgr.o Ugr/Ugr.o Ugr/members/*.o Gamma/Gamma.o Gamma/members/*.o Gamma/libMeshb/*.o
	${CXX} $(CXXFLAGS) -o scaleUgrid scaleUgrid.o Ugrid/Ugrid.o Ugrid/members/*.o
	${CXX} $(CXXFLAGS) -o convertGridToVtk convertGridToVtk.o Gamma/Gamma.o Gamma/members/*.o Gamma/libMeshb/*.o Plt/Plt.o Plt/members/*.o Ugrid/Ugrid.o Ugrid/members/*.o Ugr/Ugr.o Ugr/members/*.o
	${CXX} $(CXXFLAGS) -o readGammaSolution readGammaSolution.o Gamma/Gamma.o Gamma/members/*.o Gamma/libMeshb/*.o
	${CXX} $(CXXFLAGS) -o sortRenumberGammaEdges sortRenumberGammaEdges.o Gamma/Gamma.o Gamma/members/*.o Gamma/libMeshb/*.o Ugrid/Mapbc.o Ugrid/members/blazekReadline.o
	${CXX} $(CXXFLAGS) -o combineSolb combineSolb.o Gamma/Gamma.o Gamma/members/*.o Gamma/libMeshb/*.o
	${CXX} $(CXXFLAGS) -o combineSolb3D combineSolb3D.o Gamma/Gamma.o Gamma/members/*.o Gamma/libMeshb/*.o
	${CXX} $(CXXFLAGS) -o removeFirstSolb removeFirstSolb.o Gamma/Gamma.o Gamma/members/*.o Gamma/libMeshb/*.o 

OBJ: ${SRCS}
	${CPP} $(CXXFLAGS) -c $<

clean:
	$(MAKE) -C Ugrid/ 'clean'
	$(MAKE) -C Plt/ 'clean'
	$(MAKE) -C Gamma/ 'clean'
	$(MAKE) -C Ugr/ 'clean'
	rm -rvf *.o
	rm -rvf convertPltToVtk
	rm -rvf readGammaWriteGamma
	rm -rvf convertPltToGamma
	rm -rvf convertGammaToPlt
	rm -rvf convertUgrToGamma
	rm -rvf convertGammaToUgr
	rm -rvf scaleUgrid
	rm -rvf convertGridToVtk
	rm -rvf readGammaSolution
	rm -rvf sortRenumberGammaEdges
	rm -rvf combineSolb
	rm -rvf combineSolb3D
	rm -rvf removeFirstSolb
