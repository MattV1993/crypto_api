#include <gtest/gtest.h>

#include "api_crypto_dot_com_test_vars.h"
#include "socket/socket_utils.h"

using namespace stb;
using namespace stb::http;
using namespace stb::stock_api;
using namespace stb::stock_api::cdc;
using namespace nlohmann;

struct api_test_failure : public std::exception
{
	const char* what() const throw ()
	{
		"Test failure";
	}
};

class protocol_get_available_stock : public transfer_protocol
{
	virtual transfer_protocol_response_ptr send(
		std::string_view address,
		std::string_view content = "",
		std::chrono::milliseconds timeout = std::chrono::milliseconds::zero())
	{
		json req_json{ content };
		request req = req_json;

		response_attributes_get_instruments_array res_attribs;

		response_attributes_get_instruments res_attrib1;
		res_attrib1.instrument_name = test_currency1 + "_" + test_currency2;
		res_attrib1.quote_currency = test_currency2;
		res_attrib1.base_currency = test_currency1;
		res_attrib1.price_decimals = test_price_decimals;
		res_attrib1.quantity_decimals = test_quantity_decimals;
		res_attrib1.margin_trading_enabled = test_margin_trading_enabled;

		response_attributes_get_instruments res_attrib2;
		res_attrib1.instrument_name = test_currency3 + "_" + test_currency4;
		res_attrib1.quote_currency = test_currency4;
		res_attrib1.base_currency = test_currency3;
		res_attrib1.price_decimals = test_price_decimals;
		res_attrib1.quantity_decimals = test_quantity_decimals;
		res_attrib1.margin_trading_enabled = test_margin_trading_enabled;

		res_attribs.push_back(res_attrib1);
		res_attribs.push_back(res_attrib2);

		response res;
		res.id = req.id;
		res.method = "public/get-instruments";
		res.result = res_attribs;
		res.code = message_code::NONE;
		res.message = test_message;
		res.original = content;

		json ret = res;

		return ret;
	}
};

class protocol_get_available_stock_fail : public transfer_protocol
{
	virtual transfer_protocol_response_ptr send(
		std::string_view address,
		std::string_view content = "",
		std::chrono::milliseconds timeout = std::chrono::milliseconds::zero())
	{

	}
};

TEST(api_crypto_dot_com, api_crypto_dot_com_get_available_stock)
{
	api_params params;

	auto prot = std::make_unique<protocol_get_available_stock>();
	auto api = create_api<cdc::api>(params, std::move(prot));

	std::vector<stock_item> stock = api->get_available_stock();


}