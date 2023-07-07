# Minitalk
The "Minitalk" project is a client-server application that allows for communication between two processes using only signals. The client sends messages to the server by converting them into signals, and the server receives and displays the messages.  
It demonstrates interprocess communication using signals and provides a simple example of client-server architecture.

## Features
- Client-server communication using signals
- Efficient and lightweight interprocess communication
- Supports sending and receiving messages of any length
- Simple and minimalistic implementation

## Prerequisites
- [GCC](https://gcc.gnu.org/) or C complier

## Installation
1. Clone the repository  
  `git clone https://github.com/MariamElSahhar/minitalk.git`  
2. Navigate to the directory  
  `cd minitalk`  
3. Compile the client and server programs
   `make`  

## Usage
1. Run the server  
   `./server`  
   The server will display its process ID.  
2. On another terminal, run the client  
  `./client [server_pid] [message]`  
The client converts the message to signals and sends them to the server, which displays it!

## Resources
- [Unix Signals](https://en.wikipedia.org/wiki/Signal_(IPC)) - Wikipedia article on Unix signals
- [Subject](https://github.com/Porrapat/42-bangkok-first-cadet-subjects/blob/master/minitalk.en.subject.pdf) - 42 project subject and requirements
