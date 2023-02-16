CC = gcc
CFLAGS = -Wall
LDFLAGS = -lm -O3 -Ofast
OBJFILES = galsim.o
TARGET = galsim

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) 