#pragma once

#include "socket/socket_utils.h"

#define CURL_STATICLIB 1

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Wldap32.lib")
#pragma comment(lib, "Crypt32.lib")
#pragma comment(lib, "Normaliz.lib")

#include "curl/curl.h"

#include <memory>
#include <functional>

namespace stb::http
{
	class socket_impl : public transfer_protocol
	{
	public:

		socket_impl();

		transfer_protocol_response_ptr send(
			std::string_view address,
			std::string_view content = "",
			std::chrono::milliseconds timeout = std::chrono::milliseconds::zero()) override;

	private:

		std::unique_ptr<CURL, std::function<void(CURL*)>> curl;
	};

	status_code to_status_code(long code);
}