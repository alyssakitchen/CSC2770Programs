CC = gcc
CFLAGS = -Wall -pthread

SRCS = HTTP_Server.c HTTP_Client.c
OBJS = $(SRCS:.c=.o)
TARGET = HTTP_Server HTTP_Client

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)