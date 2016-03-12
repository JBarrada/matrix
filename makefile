CFLAGS=-std=gnu99
LIBS=-Iinclude -lfreeglut -lopengl32

OBJFILES = matrix.o vector.o math.o gfx.o m.o

all: clean m.exe

%.o: %.c
	$(CC) -c $(CFLAGS) $(LIBS) $< -o $@

m.exe: $(OBJFILES)
	$(CC) $(OBJFILES) $(LIBS) -o $@

clean:
	del *.o *.exe