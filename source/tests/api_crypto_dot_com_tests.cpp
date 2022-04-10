#include <gtest/gtest.h>

#include "api_crypto_dot_com_test_vars.h"

using namespace stb;
using namespace stb::stock_api::cdc;
using namespace nlohmann;

TEST(api_crypto_dot_com, request_params_none_to_json)
{
	request_params_none params;

	json j = params;

	EXPECT_EQ(j.size(), 0);
}

TEST(api_crypto_dot_com, request_params_none_from_json)
{
	json j = {
	};

	EXPECT_NO_THROW(request_params_none params = j);
}

TEST(api_crypto_dot_com, request_params_var_none_to_json)
{
	request_params_none params;
	request_params_var params_var = params;

	json j = params_var;

	EXPECT_EQ(j.size(), 0);
}

TEST(api_crypto_dot_com, request_params_var_none_from_json)
{
	json j = {
	};

	request_params_var params_var = to_param(j, "public/get-instruments");

	EXPECT_NO_THROW(auto params = std::get<request_params_none>(params_var););
	
}

TEST(api_crypto_dot_com, request_params_auth_to_json)
{
	request_params_auth params;
	params.api_key = test_api_key;
	params.sig = test_sig;

	json j = params;

	EXPECT_EQ(j["api_key"], test_api_key);
	EXPECT_EQ(j["sig"], test_sig);
}

TEST(api_crypto_dot_com, request_params_auth_from_json)
{
	json j = {
		{ "api_key", test_api_key },
		{ "sig", test_sig }
	};

	request_params_auth params = j;

	EXPECT_EQ(params.api_key, test_api_key);
	EXPECT_EQ(params.sig, test_sig);
}

TEST(api_crypto_dot_com, request_params_var_auth_to_json)
{
	request_params_auth params;
	params.api_key = test_api_key;
	params.sig = test_sig;

	request_params_var params_var = params;

	json j = params_var;

	EXPECT_EQ(j["api_key"], test_api_key);
	EXPECT_EQ(j["sig"], test_sig);
}

TEST(api_crypto_dot_com, request_params_var_auth_from_json)
{
	json j = {
		{ "api_key", test_api_key },
		{ "sig", test_sig }
	};

	request_params_var params_var = to_param(j, "public/auth");
	auto params = std::get<request_params_auth>(params_var);

	EXPECT_EQ(params.api_key, test_api_key);
	EXPECT_EQ(params.sig, test_sig);
}

TEST(api_crypto_dot_com, request_to_json)
{
	request_params_auth params;
	params.api_key = test_api_key;
	params.sig = test_sig;

	request req
	{ 
		test_id,
		test_method,
		params,
		test_api_key,
		"",
		test_nonce
	};

	json j = req;

	EXPECT_EQ(j["id"], test_id);
	EXPECT_EQ(j["method"], test_method);
	EXPECT_EQ(j["params"]["api_key"], test_api_key);
	EXPECT_EQ(j["params"]["sig"], test_sig);
	EXPECT_EQ(j["api_key"], test_api_key);
	EXPECT_EQ(j["sig"], "");
	EXPECT_EQ(j["nonce"], test_nonce);
}

TEST(api_crypto_dot_com, request_from_json)
{
	json j = {
		{ "id", test_id },
		{ "method", "public/auth" },
		{ "params", {
			{ "api_key", test_api_key },
			{ "sig", test_sig }
		}},
		{ "api_key", test_api_key },
		{ "sig", test_sig },
		{ "nonce", test_nonce }
	};

	request req = j;

	EXPECT_EQ(req.id, test_id);
	EXPECT_EQ(req.method, "public/auth");

	EXPECT_TRUE(std::holds_alternative<request_params_auth>(req.params));

	auto params = std::get<request_params_auth>(req.params);

	EXPECT_EQ(params.api_key, test_api_key);
	EXPECT_EQ(params.sig, test_sig);

	EXPECT_EQ(req.api_key, test_api_key);
	EXPECT_EQ(req.sig, test_sig);
	EXPECT_EQ(req.nonce, test_nonce);
}

TEST(api_crypto_dot_com, response_attributes_get_instruments_to_json)
{
	response_attributes_get_instruments response;
	response.instrument_name = test_instrument_name;
	response.quote_currency = test_quote_currency;
	response.base_currency = test_base_currency;
	response.price_decimals = test_price_decimals;
	response.quantity_decimals = test_quantity_decimals;
	response.margin_trading_enabled = test_margin_trading_enabled;
	
	json j = response;

	EXPECT_EQ(j["instrument_name"], test_instrument_name);
	EXPECT_EQ(j["quote_currency"], test_quote_currency);
	EXPECT_EQ(j["base_currency"], test_base_currency);
	EXPECT_EQ(j["price_decimals"], test_price_decimals);
	EXPECT_EQ(j["quantity_decimals"], test_quantity_decimals);
	EXPECT_EQ(j["margin_trading_enabled"], test_margin_trading_enabled);
	
}

TEST(api_crypto_dot_com, response_attributes_get_instruments_from_json)
{
	json j = {
		{ "instrument_name", test_instrument_name },
		{ "quote_currency", test_quote_currency },
		{ "base_currency", test_base_currency },
		{ "price_decimals", test_price_decimals },
		{ "quantity_decimals", test_quantity_decimals },
		{ "margin_trading_enabled", test_margin_trading_enabled },
	};

	response_attributes_get_instruments response = j;

	EXPECT_EQ(response.instrument_name, test_instrument_name);
	EXPECT_EQ(response.quote_currency, test_quote_currency);
	EXPECT_EQ(response.base_currency, test_base_currency);
	EXPECT_EQ(response.price_decimals, test_price_decimals);
	EXPECT_EQ(response.quantity_decimals, test_quantity_decimals);
	EXPECT_EQ(response.margin_trading_enabled, test_margin_trading_enabled);
}

TEST(api_crypto_dot_com, response_attributes_var_get_instruments_array_to_json)
{
	response_attributes_get_instruments_array response_attr;

	response_attributes_get_instruments response_attr_item;
	response_attr_item.instrument_name = test_instrument_name;
	response_attr_item.quote_currency = test_quote_currency;
	response_attr_item.base_currency = test_base_currency;
	response_attr_item.price_decimals = test_price_decimals;
	response_attr_item.quantity_decimals = test_quantity_decimals;
	response_attr_item.margin_trading_enabled = test_margin_trading_enabled;

	response_attr.push_back(response_attr_item);

	response_attributes_var params_var = response_attr;

	json j = params_var;

	EXPECT_EQ(j.front()["instrument_name"], test_instrument_name);
	EXPECT_EQ(j.front()["quote_currency"], test_quote_currency);
	EXPECT_EQ(j.front()["base_currency"], test_base_currency);
	EXPECT_EQ(j.front()["price_decimals"], test_price_decimals);
	EXPECT_EQ(j.front()["quantity_decimals"], test_quantity_decimals);
	EXPECT_EQ(j.front()["margin_trading_enabled"], test_margin_trading_enabled);
}

TEST(api_crypto_dot_com, response_attributes_var_get_instruments_array_from_json)
{
	json j = {
		{ "instruments", {
		{
			{ "instrument_name", test_instrument_name },
			{ "quote_currency", test_quote_currency },
			{ "base_currency", test_base_currency },
			{ "price_decimals", test_price_decimals },
			{ "quantity_decimals", test_quantity_decimals },
			{ "margin_trading_enabled", test_margin_trading_enabled }
		}}}
	};

	response_attributes_var response_var = to_response(j, "public/get-instruments");
	auto params = std::get<response_attributes_get_instruments_array>(response_var);

	EXPECT_EQ(params.front().instrument_name, test_instrument_name);
	EXPECT_EQ(params.front().quote_currency, test_quote_currency);
	EXPECT_EQ(params.front().base_currency, test_base_currency);
	EXPECT_EQ(params.front().price_decimals, test_price_decimals);
	EXPECT_EQ(params.front().quantity_decimals, test_quantity_decimals);
	EXPECT_EQ(params.front().margin_trading_enabled, test_margin_trading_enabled);
}

// ----------------------------------------------------------------------------------
TEST(api_crypto_dot_com, response_attributes_get_candlesticks_data_to_json)
{
	response_attributes_get_candlestick_data response;
	response.t = test_t;
	response.o = test_o;
	response.h = test_h;
	response.l = test_l;
	response.c = test_c;
	response.v = test_v;

	json j = response;

	EXPECT_EQ(j["t"], test_t);
	EXPECT_EQ(j["o"], test_o);
	EXPECT_EQ(j["h"], test_h);
	EXPECT_EQ(j["l"], test_l);
	EXPECT_EQ(j["c"], test_c);
	EXPECT_EQ(j["v"], test_v);

}

TEST(api_crypto_dot_com, response_attributes_get_candlesticks_data_from_json)
{
	json j = {
		{ "t", test_t },
		{ "o", test_o },
		{ "h", test_h },
		{ "l", test_l },
		{ "c", test_c },
		{ "v", test_v },
	};

	response_attributes_get_candlestick_data response = j;

	EXPECT_EQ(response.t, test_t);
	EXPECT_EQ(response.o, test_o);
	EXPECT_EQ(response.h, test_h);
	EXPECT_EQ(response.l, test_l);
	EXPECT_EQ(response.c, test_c);
	EXPECT_EQ(response.v, test_v);
}

TEST(api_crypto_dot_com, response_attributes_get_candlesticks_to_json)
{
	response_attributes_get_candlestick_data data;
	data.t = test_t;
	data.o = test_o;
	data.h = test_h;
	data.l = test_l;
	data.c = test_c;
	data.v = test_v;

	response_attributes_get_candlestick_data_array data_arr;
	data_arr.push_back(data);

	response_attributes_get_candlestick response;
	response.instrument_name = test_instrument_name;
	response.interval = test_interval;
	response.data = data_arr;

	json j = response;

	EXPECT_EQ(j["instrument_name"], test_instrument_name);
	EXPECT_EQ(j["interval"], test_interval);
	EXPECT_EQ(j["data"].front()["t"], test_t);
	EXPECT_EQ(j["data"].front()["o"], test_o);
	EXPECT_EQ(j["data"].front()["h"], test_h);
	EXPECT_EQ(j["data"].front()["l"], test_l);
	EXPECT_EQ(j["data"].front()["c"], test_c);
	EXPECT_EQ(j["data"].front()["v"], test_v);
}

TEST(api_crypto_dot_com, response_attributes_get_candlesticks_from_json)
{
	json j = {
		{ "instrument_name", test_instrument_name },
		{ "interval", test_interval },
		{ "data", {
		{
			{ "t", test_t },
			{ "o", test_o },
			{ "h", test_h },
			{ "l", test_l },
			{ "c", test_c },
			{ "v", test_v }
		}}}
	};

	response_attributes_get_candlestick response = j;

	EXPECT_EQ(response.instrument_name, test_instrument_name);
	EXPECT_EQ(response.interval, test_interval);
	EXPECT_EQ(response.data.front().t, test_t);
	EXPECT_EQ(response.data.front().o, test_o);
	EXPECT_EQ(response.data.front().h, test_h);
	EXPECT_EQ(response.data.front().l, test_l);
	EXPECT_EQ(response.data.front().c, test_c);
	EXPECT_EQ(response.data.front().v, test_v);
}

TEST(api_crypto_dot_com, response_attributes_var_get_candlesticks_data_array_to_json)
{
	response_attributes_get_candlestick_data_array response_attr_data;

	response_attributes_get_candlestick_data data;
	data.t = test_t;
	data.o = test_o;
	data.h = test_h;
	data.l = test_l;
	data.c = test_c;
	data.v = test_v;

	response_attr_data.push_back(data);

	response_attributes_get_candlestick response_attr;
	response_attr.instrument_name = test_instrument_name;
	response_attr.interval = test_interval;
	response_attr.data = response_attr_data;

	response_attributes_var params_var = response_attr;

	json j = params_var;

	EXPECT_EQ(j["instrument_name"], test_instrument_name);
	EXPECT_EQ(j["interval"], test_interval);
	EXPECT_EQ(j["data"].front()["t"], test_t);
	EXPECT_EQ(j["data"].front()["o"], test_o);
	EXPECT_EQ(j["data"].front()["h"], test_h);
	EXPECT_EQ(j["data"].front()["l"], test_l);
	EXPECT_EQ(j["data"].front()["c"], test_c);
	EXPECT_EQ(j["data"].front()["v"], test_v);
}

TEST(api_crypto_dot_com, response_attributes_var_get_candlesticks_data_array_from_json)
{
	json j = {
	{ "instrument_name", test_instrument_name },
	{ "interval", test_interval },
	{ "data", {
	{
		{ "t", test_t },
		{ "o", test_o },
		{ "h", test_h },
		{ "l", test_l },
		{ "c", test_c },
		{ "v", test_v }
	}}}
	};

	response_attributes_var response_var = to_response(j, "public/get-candlestick");
	auto params = std::get<response_attributes_get_candlestick>(response_var);

	EXPECT_EQ(j["instrument_name"], test_instrument_name);
	EXPECT_EQ(j["interval"], test_interval);
	EXPECT_EQ(j["data"].front()["t"], test_t);
	EXPECT_EQ(j["data"].front()["o"], test_o);
	EXPECT_EQ(j["data"].front()["h"], test_h);
	EXPECT_EQ(j["data"].front()["l"], test_l);
	EXPECT_EQ(j["data"].front()["c"], test_c);
	EXPECT_EQ(j["data"].front()["v"], test_v);
}
// -----------------------------------------------------------------------------------------------

TEST(api_crypto_dot_com, response_to_json)
{
	response_attributes_get_instruments_array response_attr;

	response_attributes_get_instruments response_attr_item;
	response_attr_item.instrument_name = test_instrument_name;
	response_attr_item.quote_currency = test_quote_currency;
	response_attr_item.base_currency = test_base_currency;
	response_attr_item.price_decimals = test_price_decimals;
	response_attr_item.quantity_decimals = test_quantity_decimals;
	response_attr_item.margin_trading_enabled = test_margin_trading_enabled;

	response_attr.push_back(response_attr_item);

	response res;
	res.id = test_id;
	res.method = test_method;
	res.result = response_attr;
	res.code = test_code;
	res.message = test_message;
	res.original = test_original;

	json j = res;

	EXPECT_EQ(j["id"], test_id);
	EXPECT_EQ(j["method"], test_method);
	EXPECT_EQ((*j["result"].begin())["instrument_name"], test_instrument_name);
	EXPECT_EQ((*j["result"].begin())["quote_currency"], test_quote_currency);
	EXPECT_EQ((*j["result"].begin())["base_currency"], test_base_currency);
	EXPECT_EQ((*j["result"].begin())["price_decimals"], test_price_decimals);
	EXPECT_EQ((*j["result"].begin())["quantity_decimals"], test_quantity_decimals);
	EXPECT_EQ((*j["result"].begin())["margin_trading_enabled"], test_margin_trading_enabled);
	EXPECT_EQ(j["code"], test_code);
	EXPECT_EQ(j["message"], test_message);
	EXPECT_EQ(j["original"], test_original);
}

TEST(api_crypto_dot_com, response_from_json)
{
	json j = {
		{ "id", test_id },
		{ "method", "public/get-instruments" },
		{ "result", {
			{ "instruments", {
				{
					{ "instrument_name", test_instrument_name },
					{ "quote_currency", test_quote_currency },
					{ "base_currency", test_base_currency },
					{ "price_decimals", test_price_decimals },
					{ "quantity_decimals", test_quantity_decimals },
					{ "margin_trading_enabled", test_margin_trading_enabled }
				}
			}},		
		}},
		{ "code", test_code },
		{ "message", test_message },
		{ "original", test_original }
	};

	response res = j;

	EXPECT_EQ(res.id, test_id);
	EXPECT_EQ(res.method, "public/get-instruments");

	EXPECT_TRUE(std::holds_alternative<response_attributes_get_instruments_array>(res.result));

	auto attr = std::get<response_attributes_get_instruments_array>(res.result);

	EXPECT_EQ(attr.front().instrument_name, test_instrument_name);
	EXPECT_EQ(attr.front().quote_currency, test_quote_currency);
	EXPECT_EQ(attr.front().base_currency, test_base_currency);
	EXPECT_EQ(attr.front().price_decimals, test_price_decimals);
	EXPECT_EQ(attr.front().quantity_decimals, test_quantity_decimals);
	EXPECT_EQ(attr.front().margin_trading_enabled, test_margin_trading_enabled);

	EXPECT_EQ(res.code, test_code);
	EXPECT_EQ(res.message, test_message);
	EXPECT_EQ(res.original, test_original);
}
