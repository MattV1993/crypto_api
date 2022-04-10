#include "stock_api/stock_api_utils.h"

#include "cryptopp/filters.h"
#include "cryptopp/hmac.h"
#include "cryptopp/sha.h"
#include "cryptopp/osrng.h"

std::string stb::stock_api::generate_hmac_sha256(std::string_view data, std::string_view secret_key)
{
	CryptoPP::HMAC<CryptoPP::SHA256> hmac{ reinterpret_cast<CryptoPP::byte const*>(secret_key.data()), secret_key.size() };

	std::string calculated_hmac;
	auto sink = std::make_unique<CryptoPP::StringSink>(calculated_hmac);

	auto filter = std::make_unique<CryptoPP::HashFilter>(hmac, sink.get());
	sink.release();

	{
		CryptoPP::StringSource s{ reinterpret_cast<CryptoPP::byte const*>(data.data()), data.size(), true, filter.get() };
	}

	filter.release();
	
	return calculated_hmac;
}

int64_t stb::stock_api::generate_nonce()
{
	CryptoPP::SecByteBlock nonce_bytes(16);
	CryptoPP::AutoSeededRandomPool prng;

	prng.GenerateBlock(nonce_bytes, nonce_bytes.size());
	
	CryptoPP::Integer nonce;
	size_t encoded_size = nonce.MinEncodedSize(CryptoPP::Integer::UNSIGNED);
	
	nonce_bytes.resize(encoded_size);
	nonce.Decode(nonce_bytes.data(), nonce_bytes.size());

	return nonce.ConvertToLong();
}

std::string stb::stock_api::encode_hex(std::string_view s)
{
	static const std::vector<char> chars{ '0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f' };
	std::string ret;

	for (unsigned char c : s)
	{
		ret.push_back(chars[c >> 4]);
		ret.push_back(chars[c & 15]);
	}

	return ret;
}