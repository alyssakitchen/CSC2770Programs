CC = gcc
CFLAGS = -Wall -pthread

SRCS = ThreadedMatrixMultiply.c
OBJS = $(SRCS:.c=.o)
TARGET = ThreadedMatrixMultiply

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)