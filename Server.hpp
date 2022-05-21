#include <iostream>
#include <sys/socket.h> // socket
#include <netinet/in.h> // sockaddr_in
#include <unistd.h> //read, write


class Server{

	private:

	int                 _server_fd;
	int                 _address_len;
	struct sockaddr_in  _address;

	public:

    // ------------------------ Constructors : ------------------------- >>

    // int server_socket = setup_server (port, addr, backlog)
	Server(uint16_t port, uint32_t addr) : _address_len(sizeof(_address)){
		if ((_server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
			std::cerr << "In Socket" << std::endl; 
			exit(EXIT_FAILURE);
		}

		_address.sin_family = AF_INET;
		_address.sin_addr.s_addr = addr;
		_address.sin_port = htons(port);

        // Add check(int fd, std::string error msg)
		if (bind(_server_fd, (struct sockaddr*)&_address, _address_len) < 0){
			std::cerr << "In Bind" << std::endl;
			exit(EXIT_FAILURE);
		}

		if (listen(_server_fd, 0) < 0){
			std::cerr << "In Listen" << std::endl;
			exit(EXIT_FAILURE);
		}
	}

    // ------------------------- Getter && Setters : ----------------------- >>
    int &getSocketFD()
    {
        return (this->_server_fd);
    }

    // ------------------------- Member Functions : ------------------------- >>
    int acceptNewConnection()
    {
        int client_socket;

        if ((client_socket = accept(_server_fd, (struct sockaddr*) &_address, (socklen_t*)&_address_len)) < 0){
			std::cerr << "In accept" << std::endl;
			exit(EXIT_FAILURE);
		}
        return (client_socket);
    }

	static void handleConnection(int client_socket){

		char response[100] = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
        char request[30000] = {0};

		long valread;

	
		valread = read(client_socket, request, 1024);

        if(valread < 0)
            std::cout << "No bytes are there to read" << std::endl;
		std::cout << request << std::endl;

		write(client_socket, response, strlen(response));
        std::cout << "\n+++++++ Hello message sent ++++++++\n" << std::endl;
		close(client_socket);
	}

};

int run(){

	Server server1(80, INADDR_ANY); // setup server 1
	Server server2(8080, INADDR_ANY); // setup server 1

    fd_set current_sockets, ready_sockets;

    //init current set
    FD_ZERO(&current_sockets);
    FD_SET(server1.getSocketFD(), &current_sockets);
    FD_SET(server2.getSocketFD(), &current_sockets);
    while (true)
    {
        std::cout << "\nWaiting For Connections... \n" << std::endl;
        // select desruct all sockets
        ready_sockets = current_sockets;
        if (select(FD_SETSIZE, &ready_sockets, NULL, NULL, NULL) < 0) // FD_SETSIZE max fd socket can support
        {
            std::cerr << "In Select" << std::endl;
			exit(EXIT_FAILURE);
        }
        for (int i = 0; i < FD_SETSIZE ; i++)
        {
           if (FD_ISSET(i, &ready_sockets))
           {
               if (i == server1.getSocketFD()) // this is new connection from server 1
               {    
                    int client_socket = server1.acceptNewConnection();
                    FD_SET(client_socket, &current_sockets);
               }
               else if (i == server2.getSocketFD()) // this is new connection from server 2
               {    
                    int client_socket = server2.acceptNewConnection();
                    FD_SET(client_socket, &current_sockets);
               }

               else // client connection request
               {
                   Server::handleConnection(i);
                   FD_CLR(i, &current_sockets);
               }
           }
        }
        // close(server1.getSocketFD());
        // close(server2.getSocketFD());
    }
	
	return 0;
}
