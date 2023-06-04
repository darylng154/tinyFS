.PHONY: all clean

CC = gcc
CFLAGS = -Wall -Wextra -g
LD = gcc
LDFLAGS = -Wall -Wextra

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
	
# DO NOT DELETE

libDisk.o: libTinyFS.h libDisk.h safeutil.h
libTinyFS.o: libTinyFS.h libDisk.h safeutil.h
tinyFsDemo.o: libDisk.h libTinyFS.h safeutil.h
safeutil.o: safeutil.h
