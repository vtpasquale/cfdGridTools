# Usage:
# make        # compile Plt and members
# make clean  # remove Plt and memeber objects

.PHONY = all

CPP = g++

MEM_SRCS := $(wildcard ./members/*.cpp)
MEM_OBJ := $(MEM_SRCS:%.cpp=%.o)

CLS_SRCS := $(wildcard *.cpp)
CLS_OBJ := $(CLS_SRCS:%.cpp=%.o)

BINS := $(SRCS:%.cpp=%)

# Build Ugrid class object
all: ${MEM_OBJ} ${CLS_OBJ}

# Build Ugrid class object from source
CLS_OBJ: ${CLS_SRCS}
	${CPP} -c $<

# Build Ugrid member objects from source
MEM_OBJ: ${MEM_SRCS}
	${CPP} -c $<

clean:
	@echo "Cleaning up..."
	rm -rvf ./members/*.o
	rm -rvf *.o
