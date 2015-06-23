Chat Room 
===============
sockets programming in C 

this is a basic chat room design for practice linux sockets programming, for build the WPI CS513 project

it support handle multi-clients (multi processes) talk together.

every clientsend message to server. server get the time (function for handle system time), and save message into shared 
memory(implement shared memory for support IPC), then it send the message back into every client which connect with server.

every client has two processes, father process is recieve message, and child process is send message. it avoid the data-collsion.

for complie the code, rum the Makefile

make -f Makefile


whole program is test on WPI ccc machine(one server, two-three clients). and my own linux machine (unbuntu 12.04)

bugs need to fix:the server is infinate loop, so when terminate it, the log file will write some empty message.
