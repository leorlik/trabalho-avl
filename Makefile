#//GRR20195124 Leonardo Lima Dionizio

CC=gcc

CFLAGS= -Wall

PROJ_NAME=myavl

C_SOURCE=$(wildcard *.c)

H_SOURCE=$(wildcard *.h)

OBJ=$(H_SOURCE:.h=.o)

%.o: %.c %.h
	$(CC) -c $< $(CFLAGS)

all: $(PROJ_NAME)

$(PROJ_NAME): $(PROJ_NAME).c $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	-rm -f *~ *.o

purge: clean
	-rm -f $(PROJ_NAME)
