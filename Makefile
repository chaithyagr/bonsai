.SUFFIXES: .cu

NVCC = nvcc -g -use_fast_math -arch=sm_52 -rdc=true
LFLAGS = -lcudadevrt -Iinclude/
LFLAGS += -DMASS # Use all positive sources

SRC = thrust.cu serial.cu

OBJ = $(SRC:%.cu=%.o)

# Test for serial FMM
serial: $(OBJ)
	$(NVCC) $^ $(LFLAGS)
	./a.out

%.o: %.cu
	$(NVCC) -c $< $(LFLAGS)

clean:
	rm -f *.o *.out *.dat

