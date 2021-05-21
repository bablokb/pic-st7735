all: fc_subset

CC     = gcc
CFLAGS = -Wall -I/usr/local/include/freetype2 -I/usr/include/freetype2 -I/usr/include
LIBS   = -lfreetype

fc_subset: fc_subset.c
	$(CC) $(CFLAGS) $< $(LIBS) -o $@
	strip $@

clean:
	rm -f fc_subset
