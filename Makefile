CC = gcc
OBJS = cache_city.o
CFLAGS = -g -I./
TARGET = main


.SUFFIXES : .c .o

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf $(OBJS) $(TARGET)
