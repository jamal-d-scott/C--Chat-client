all: client server

client: lab13.c
	gcc lab13.c -o client
	
server: server.c
	gcc server.c -o server

clean:
	rm -f Lab13
