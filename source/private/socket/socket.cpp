#include "socket/socket.h"
#include "socket/socket_curl.h"

stb::http::socket::socket() :
	impl{ std::make_unique<socket_impl>() }
{
	
}

stb::http::socket::~socket()
{
}

stb::transfer_protocol_response_ptr stb::http::socket::send(std::string_view address, std::string_view content, std::chrono::milliseconds timeout)
{
	return impl->send(address, content, timeout);
}
