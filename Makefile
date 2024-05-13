CC=gcc
CFLAGS=-Wall -O3

all: receiver sender

receiver: receiver.c
	$(CC) $(CFLAGS) receiver.c -o receiver -lrt

sender: sender.c
	$(CC) $(CFLAGS) sender.c -o sender -lrt

clean:
	rm -f sender receiver
	rm -f /dev/shm/my_shared_memory