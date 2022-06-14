#include "include/Server.hpp"
#include "include/Utils.hpp"

#include "parser_request/include/ParserRe.hpp"
#include "parser_request/include/RequestInfo.hpp"
#include "response/Response.hpp"

// ================= Constructor =============== //
Server::Server(std::vector<ServerSetup> servers) : _address_len(sizeof(_address)), opt(1)
{

	std::vector<ServerSetup>::iterator it(servers.begin());
	size_t size = servers.size();

	for (size_t i = 0; i < size; i++)
	{
		if ((_server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
			std::cerr << "cannot creat socket" << std::endl;
			exit(EXIT_FAILURE);
		}
		_v_server_fd.push_back(_server_fd);

		memset(&_address, 0, _address_len);
		_address.sin_family = AF_INET; // use IPv4
		_address.sin_port = htons((*it).getListen().first);
		_address.sin_addr.s_addr = (*it).getListen().second;
		it++;
		_v_address.push_back(_address);

		// Control socket descriptors
		if (fcntl(_server_fd, F_SETFL, O_NONBLOCK) < 0)
		{
			std::cerr << "non_blocking error" << std::endl;
			exit(EXIT_FAILURE);
		}

		if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		{
			std::cerr << "setsockpt error" << std::endl;
			exit(EXIT_FAILURE);
		}

		if (!samePort(_v_address))
		{
			if (bind(_server_fd, (struct sockaddr *)&_address, _address_len) < 0)
			{
				std::cerr << "bind does not working" << std::endl;
				exit(EXIT_FAILURE);
			}
		}

		// limit backlog is 128
		if (listen(_server_fd, 128) < 0)
		{
			std::cerr << "In listen" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
}

// ================ Getter ===================== //

std::vector<int> Server::GetServerFds()
{
	return _v_server_fd;
}

// ============= Member function ============== //

int Server::acceptNewConnection(std::pair<int, size_t> pair)
{
	// pair<server, possition>
	int new_socket;
	if ((new_socket = accept(pair.first, (struct sockaddr *)&_v_address[pair.second], (socklen_t *)&_address_len)) < 0)
	{
		std::cerr << "In accept" << std::endl;
		exit(EXIT_FAILURE);
	}
	return new_socket;
}

void Server::addNewRequest(int fd)
{
	_requests.insert(std::pair<int, Request>(fd, Request()));
}

void Server::removeRequest(int fd)
{
	if (_requests.find(fd) != _requests.end())
		_requests.erase(fd);
}

bool Server::isRequestExist(int fd)
{
	return _requests.find(fd) != _requests.end();
}

bool Server::handleConnection(ServerSetup server_setup, int new_socket)
{
	// ---------------------- Reading Request --------------------------- //
	std::string request = receiveRequest(new_socket);

	// --------------------- Parsing The Request ------------------------- //
	if (request.empty())
		return false;
	LexerRe lexer(request);
	ParserRe parser(lexer);
	RequestInfo request_info = parser.parse();
	// ----------------------- Print Request ------------------------------ //

	// std::cout << "<< ================== Start Request =================== >>" << std::endl;
	// std::cout << request << std::endl;
	// std::cout << "<< =================== End Request ==================== >>" << std::endl;

	if (request_info.getHeaders().find("Content-Length") != request_info.getHeaders().end())
	{
		std::cout << "<< ================== Request Info ============== >>" << std::endl;
		std::cout << "Content Lenght :" << request_info.getHeaders()["Content-Length"] << std::endl;
		std::cout << "Lenght Body :" << request_info.getBody().length() << std::endl;
		std::cout << "<< ==================================================== >>" << std::endl;
	}

	// ----------------------- Handle and Send Response ----------------------------- //
	Response resp(new_socket, request_info, server_setup);
	resp.handleResponse();

	_requests.erase(new_socket); // request completed
	// check if the request is keep-alive to close it
	std::cout << "\n================ Response sent ===============\n" << std::endl;
	return (true);
}

std::string Server::receiveRequest(int fd_socket)
{
	char buffer[LENGTH_RECV_BUFFER] = {0};
	long valread = 0;

	// is First read
	if (!_requests[fd_socket].isHeaderReaded())
	{
		valread = recv(fd_socket, buffer, LENGTH_RECV_BUFFER, 0);
		if (valread > 0)
			_requests[fd_socket].appandBuffer(buffer, valread);	// set content body + buffer string + set isHeaderReaded = true
		_requests[fd_socket].setHeaders(buffer);			// set content length + chanked
		if (_requests[fd_socket].isChanked())
			_requests[fd_socket].deleteDelimeter(true);
		if (_requests[fd_socket].getContentLength() == 0)		// if the content length is 0 then the request is Complete
			return std::string(buffer, valread);
	}
	// appand the buffer
	while ((valread = recv(fd_socket, buffer, LENGTH_RECV_BUFFER, 0)) > 0)
	{
		_requests[fd_socket].appandBuffer(buffer, valread);
		memset(buffer, 0, LENGTH_RECV_BUFFER);
	}	
	if (_requests[fd_socket].isChanked())
		_requests[fd_socket].deleteDelimeter(true);
	
	// if Finished Request
	if (_requests[fd_socket].getReadBody() == _requests[fd_socket].getContentLength())
		return (_requests[fd_socket].getBuffer());
	return ("");
}