#include "socket/socket_curl.h"

namespace
{
	size_t write_callback(char* contents, size_t size, size_t nmemb, void* user_data)
	{
		((std::string*)user_data)->append((char*)contents, size * nmemb);
		return size * nmemb;
	}
}

stb::http::socket_impl::socket_impl()
{
	curl = std::unique_ptr<CURL, std::function<void(CURL*)>>
	{
		curl_easy_init(),
		[](CURL* c) { curl_easy_cleanup(c); }
	};

	if (curl == nullptr)
	{
		throw socket_implementation_uninitialised{};
	}
}

stb::transfer_protocol_response_ptr stb::http::socket_impl::send(
	std::string_view address,
	std::string_view content,
	std::chrono::milliseconds timeout)
{
	socket_result sock_res;

	curl_easy_setopt(curl.get(), CURLOPT_URL, address.data());

	std::string read_buffer;
	curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, &read_buffer);
	curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, write_callback);

	if (content.size() == 0)
	{
		curl_easy_setopt(curl.get(), CURLOPT_HTTPGET, 1L);
	}
	else
	{
		curl_easy_setopt(curl.get(), CURLOPT_POSTFIELDSIZE, static_cast<long>(content.length()));
		curl_easy_setopt(curl.get(), CURLOPT_POSTFIELDS, content.data());

		struct curl_slist* headers = nullptr;

		curl_easy_setopt(curl.get(), CURLOPT_HEADER, true);
		headers = curl_slist_append(headers, "Accept: application/json");
		headers = curl_slist_append(headers, "Content-Type: application/json");
		headers = curl_slist_append(headers, "charset: utf-8");


		curl_easy_setopt(curl.get(), CURLOPT_HTTPHEADER, headers);
	}

	curl_easy_setopt(curl.get(), CURLOPT_TIMEOUT_MS, timeout.count());

	const CURLcode curl_res = curl_easy_perform(curl.get());

	if (curl_res == CURLE_OK)
	{
		long response_code;
		curl_easy_getinfo(curl.get(), CURLINFO_RESPONSE_CODE, &response_code);
	

		sock_res.status_code = to_status_code(response_code);
		sock_res.result = read_buffer;
	}
	else if (curl_res == CURLE_OPERATION_TIMEDOUT)
	{
		sock_res.status_code = status_code::SOCKET_TIMED_OUT;
	}

	if (sock_res.status_code != status_code::STATUS_OK)
	{
		throw transfer_failure{ sock_res.result, static_cast<int64_t>(sock_res.status_code) };
	}

	return std::make_unique<socket_result>(std::move(sock_res));
}

stb::http::status_code stb::http::to_status_code(long code)
{
	return static_cast<status_code>(code);
}
