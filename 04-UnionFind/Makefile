CC = gcc

#  -Wall       give verbose compiler warnings
#  -O0         do not optimize generated code
#  -std=gnu99  use the GNU99 standard language definition
CFLAGS = -Wall -O0 -std=gnu99

unionfind: main.c unionfind.c 
	$(CC) $(CFLAGS) -o unionfind main.c unionfind.c

.PHONY: clean

clean:
	rm -f unionfind *.o