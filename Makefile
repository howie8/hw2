# Makefile

CC = gcc
CFLAGS = -Wall -Werror -g

CSRC = hw2.c tdlist.c
HSRC = tdlist.h

OBJ = $(CSRC:.c=.o)

%o:%c $(HSRC)
	$(CC) $(CFLAGS) -c $<

# Additional targets
.PHONY: clean
.PHONY: test

# Target rules

hw2: $(OBJ)
	$(CC) $(CFLAGS) -o hw2 $(OBJ)

clean:	hw2
	rm -f $(OBJ)

test:	hw2
	./hw2 < s1.in > s1.out
	./hw2 < s2.in > s2.out
	./hw2 < s3.in > s3.out
	./hw2 < s4.in > s4.out
	./hw2 < s5.in > s5.out
	./hw2 < s6.in > s6.out
	./hw2 < s7.in > s7.out
