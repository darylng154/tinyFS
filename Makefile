.PHONY: all clean

CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g
LD = gcc
LDFLAGS = -Wall -Wextra -pedantic

PROG = tinyFsDemo
OBJS = libDisk.o libTinyFS.o tinyFsDemo.o safeutil.o
SRCS = libDisk.c libTinyFS.c tinyFsDemo.c safeutil.c
HDRS = libDisk.c libTinyFS.c

all: $(PROG)

$(PROG): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

depends:
	@echo Regenerating local dependencies.
	makedepend -Y $(SRCS)

run: clean all
	./$(PROG)

clean:
	-rm -f $(OBJS)
	-rm -f $(PROG)