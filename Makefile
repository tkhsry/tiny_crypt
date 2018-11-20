# tiny crypt of Makefile
#
OBJS = main.o system.o
BACK = Makefile~ main.c~ sys_io.h~ system.c~ sys_file.h~
CC = gcc
tinycrypt:$(OBJS)
	$(CC) -o tinycrypt $(OBJS) -lm
main.o:main.c
	$(CC) -c main.c
system.o:system.c
	$(CC) -c system.c
clean:
	rm -f $(OBJS) $(BACK)

