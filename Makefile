# Makefile

CC = gcc
CFLAGS = -Wall -Werror

CSRC = hw2.c tdlist.c
HSRC = tdlist.h

OBJ = $(CSRC:.c=.o)

%o:%c $(HSRC)
	$(CC) $(CFLAGS) -c $<

# Additional targets
.PHONY: clean

# Target rules

hw2: $(OBJ)
	$(CC) $(CFLAGS) -o hw2 $(OBJ)

clean:
	rm -f $(OBJ)
