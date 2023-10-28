# por defecto CC es gcc salvo que se defina explicitamente al invocar a make.
# por ejemplo: make CC=clang

CC=gcc

# En SRC incluimos todos los ficheros fuente de la aplicacion
SRC = 


# en caso de que usemos gcc:
#	los objetos los guardamos con _gcc.o
#	el ejecutable termina en .gcc

CFLAGS = -Wall -Wextra -O3  -fopenmp 
LFLAGS = -lm -lmpfr -lgmp -fopenmp
OBJ = $(SRC:.c=_gcc.o)
EXE = $(patsubst %.c,%.gcc,$(SRC))

# en caso de que usemos clang:
# 	cambiamos flags 
#	los objetos los guardamos con _clang.o
#	el ejecutable termina en .clang

ifeq ($(CC),clang)
	CFLAGS = -Weverything -O3 -fopenmp -lmpfr -lgmp
	OBJ = $(SRC:.c=_clang.o)
	EXE = $(patsubst %.c,%.clang,$(SRC))
endif

all: $(EXE)

$(EXE): $(OBJ)
	$(CC)  -o $@ $^ $(LFLAGS)

%_gcc.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%_clang.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *_gcc.o  *_clang.o *.gcc *.clang

.PHONY: all clean
