#pragma once

#include <string>
#include <memory>
#include <exception>
#include <chrono>

namespace stb
{
	// Interface for api response
	struct transfer_protocol_response
	{
		virtual ~transfer_protocol_response() = default;

		virtual std::string data() const = 0;

	protected:

		transfer_protocol_response(const transfer_protocol_response&) = default;
		transfer_protocol_response(transfer_protocol_response&&) = default;

		transfer_protocol_response& operator=(const transfer_protocol_response&) = default;
		transfer_protocol_response& operator=(transfer_protocol_response&&) = default;

		transfer_protocol_response() = default;
	};

	using transfer_protocol_response_ptr = std::unique_ptr<transfer_protocol_response>;

	// Interface for data communication protocol for api
	class transfer_protocol
	{
	public:

		virtual transfer_protocol_response_ptr send(
			std::string_view address,
			std::string_view content = "",
			std::chrono::milliseconds timeout = std::chrono::milliseconds::zero()) = 0;

	protected:

		transfer_protocol(const transfer_protocol&) = default;
		transfer_protocol(transfer_protocol&&) = default;

		transfer_protocol& operator=(const transfer_protocol&) = default;
		transfer_protocol& operator=(transfer_protocol&&) = default;

		transfer_protocol() = default;
	};

	using transfer_protocol_ptr = std::unique_ptr<transfer_protocol>;

	class transfer_failure : public std::exception
	{
	public:

		transfer_failure(std::string_view message, int64_t code)
			: code_{ code }
		{
			message_ = "Transfer failure:";
			message_ += " Code: " + std::to_string(code_);
		}

		const char* what() const throw ()
		{
			return message_.c_str();
		}

		int64_t code() const
		{
			return code_;
		}

	private:

		std::string message_;
		int64_t code_;
	};
}