#pragma once

#include "socket/socket_utils.h"

namespace stb::http
{
	class socket_impl;

	// http socket
	// uses pimp pattern
	class socket : public transfer_protocol
	{
	public:

		socket();
		~socket();

		socket(const socket&) = default;
		socket(socket&&) = default;

		socket& operator=(const socket&) = default;
		socket& operator=(socket&&) = default;
		
		transfer_protocol_response_ptr send(
			std::string_view address,
			std::string_view content = "",
			std::chrono::milliseconds timeout = std::chrono::milliseconds::zero()) override;

	private:

		std::unique_ptr<socket_impl> impl;
	};
}