CC = gcc
CFLAGS = -Wall -pthread

SRCS = Finding_Time.c
OBJS = $(SRCS:.c=.o)
TARGET = Finding_Time

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)