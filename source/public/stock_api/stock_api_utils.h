#include <string>

namespace stb::stock_api
{
	std::string generate_hmac_sha256(std::string_view data, std::string_view secret_key);

	int64_t generate_nonce();

	std::string encode_hex(std::string_view s);
}