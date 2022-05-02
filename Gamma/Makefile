# Usage:
# make	# compile
# make clean  # remove object files

.PHONY = all

CPP = g++
CC = gcc

LBM_SRCS := $(wildcard ./libMeshb/*.c)
LBM_OBJ := $(LBM_SRCS:%.c=%.o)

MEM_SRCS := $(wildcard ./members/*.cpp)
MEM_OBJ := $(MEM_SRCS:%.cpp=%.o)

C_SRCS := $(wildcard *.c)
C_OBJ := $(C_SRCS:%.c=%.o)

CPP_SRCS := $(wildcard *.cpp)
CPP_OBJ := $(CPP_SRCS:%.cpp=%.o)

BINS := $(SRCS:%.c=%)

# Build Gamma class object
all: ${LBM_OBJ} ${MEM_OBJ} ${C_OBJ} ${CPP_OBJ}
	${CC} -o mshinfo mshinfo.o libMeshb/libmeshb7.o
	${CPP} -o mshinfop mshinfop.o libMeshb/libmeshb7.o
	${CC} -D 'TRANSMESH=1' -o transmesh transmesh.c libMeshb/libmeshb7.c -I../libMeshb/

# Build Gamma class object from source
C_OBJ: ${C_SRCS}
	${CC} -c $<

CPP_OBJ: ${CPP_SRCS}
	${CPP} -c $<

# Build Gamma member objects from source
LBM_OBJ: ${LBM_SRCS}
	${CC} -c $<

MEM_OBJ: ${MEM_SRCS}
	${CPP} -c $<

clean:
	@echo "Cleaning up..."
	rm -rvf ./libMeshb/*.o
	rm -rvf ./members/*.o
	rm -rvf *.o
	rm -rvf mshinfo mshinfop transmesh
