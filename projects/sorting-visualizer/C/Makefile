SRC=src/main.c src/sorting.c
TESTS=src/sorting.c tests/sorting_test.c
EXEC=SortingVisualizer.exe
TESTING=Tests.exe
CFLAGS=-g -Wall -Wextra -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -lm

all: $(EXEC) $(TESTING)

$(EXEC): $(SRC)
	gcc -o $(EXEC) $(SRC) $(CFLAGS) 

$(TESTING): $(TESTS)
	gcc -o $(TESTING) $(TESTS) $(CFLAGS) 
