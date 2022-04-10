#include "socket/socket_utils.h"

std::string stb::http::socket_result::data() const
{
	return result;
}

const char* stb::http::socket_implementation_uninitialised::what() const throw()
{
	return "socket implementation uninitialised";
}
