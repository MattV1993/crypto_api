#include "stock_api/stock_api_cdc.h"
#include "stock_api/stock_api_utils.h"

void stb::stock_api::cdc::to_json(nlohmann::json& j, const request_params_none& par)
{
	j = nlohmann::json{
	};
}

void stb::stock_api::cdc::from_json(const nlohmann::json& j, request_params_none& req)
{
}

void stb::stock_api::cdc::to_json(nlohmann::json& j, const request_params_auth& par)
{
	j = nlohmann::json {
		{ "api_key", par.api_key },
		{ "sig", par.sig },
	};
}

void stb::stock_api::cdc::from_json(const nlohmann::json& j, request_params_auth& req)
{
	j.at("api_key").get_to(req.api_key);
	j.at("sig").get_to(req.sig);
}

std::string stb::stock_api::cdc::to_string(const request_params_var& params)
{
	return std::string();
}

void stb::stock_api::cdc::to_json(nlohmann::json& j, const request_params_var& req)
{
	// auto lambda to convert all possible request_params_var types to json
	std::visit([&j](auto&& arg)
		{
			j = arg;
		}, req);
}

stb::stock_api::cdc::request_params_var stb::stock_api::cdc::to_param(const nlohmann::json& j, const std::string& method)
{
	request_params_var ret;

	if (method == "public/auth")
	{
		request_params_auth req = j;
		ret = req;
	}
	else if (method == "private/create-withdrawal")
	{
		//request_params_create_withdrawal req = j;
		//ret = req;
	}
	else if (method == "public/get-instruments")
	{
		request_params_none req = j;
		ret = req;
	}
	else
	{
		throw std::invalid_argument{ "Invalid method" };
	}

	return ret;
}

void stb::stock_api::cdc::to_json(nlohmann::json& j, const request& req)
{
	j = nlohmann::json {
		{ "id", req.id },
		{ "method", req.method },
		{ "params", req.params },
		{ "api_key", req.api_key },
		{ "sig", req.sig },
		{ "nonce", req.nonce }
	};
}

void stb::stock_api::cdc::from_json(const nlohmann::json& j, request& req)
{
	j.at("id").get_to(req.id);
	j.at("method").get_to(req.method);
	req.params = to_param(j.at("params"), req.method);
	j.at("api_key").get_to(req.api_key);
	j.at("sig").get_to(req.sig);
	j.at("nonce").get_to(req.nonce);
}

void stb::stock_api::cdc::sign_request(request& req, std::string_view secret_key)
{
	// TODO: sort params
	std::string sig_pay_load = req.method + std::to_string(req.id) + req.api_key + to_string(req.params) + std::to_string(req.nonce);
	req.sig = generate_hmac_sha256(sig_pay_load, secret_key);
	req.sig = encode_hex(req.sig);
}

void stb::stock_api::cdc::to_json(nlohmann::json& j, const response_attributes_get_instruments& res)
{
	j = nlohmann::json {
		{ "instrument_name", res.instrument_name },
		{ "quote_currency", res.quote_currency },
		{ "base_currency", res.base_currency },
		{ "price_decimals", res.price_decimals },
		{ "quantity_decimals", res.quantity_decimals },
		{ "margin_trading_enabled", res.margin_trading_enabled }
	};
}

void stb::stock_api::cdc::from_json(const nlohmann::json& j, response_attributes_get_instruments& res)
{
	j.at("instrument_name").get_to(res.instrument_name);
	j.at("quote_currency").get_to(res.quote_currency);
	j.at("base_currency").get_to(res.base_currency);
	j.at("price_decimals").get_to(res.price_decimals);
	j.at("quantity_decimals").get_to(res.quantity_decimals);
	j.at("margin_trading_enabled").get_to(res.margin_trading_enabled);
}

void stb::stock_api::cdc::to_json(nlohmann::json& j, const response_attributes_get_candlestick_data_array& res)
{
	nlohmann::json j_arr;

	for (const auto& attr : res)
	{
		nlohmann::json j_item = attr;
		j_arr.push_back(j_item);
	}

	j = j_arr;
}

void stb::stock_api::cdc::from_json(const nlohmann::json& j, response_attributes_get_candlestick_data_array& res)
{
	for (const auto& j_item : j)
	{
		res.push_back(j_item);
	}
}

void stb::stock_api::cdc::to_json(nlohmann::json& j, const response_attributes_get_candlestick_data& res)
{
	j = nlohmann::json{
		{ "t", res.t },
		{ "o", res.o },
		{ "h", res.h },
		{ "l", res.l },
		{ "c", res.c },
		{ "v", res.v }
	};
}

void stb::stock_api::cdc::from_json(const nlohmann::json& j, response_attributes_get_candlestick_data& res)
{
	j.at("t").get_to(res.t);
	j.at("o").get_to(res.o);
	j.at("h").get_to(res.h);
	j.at("l").get_to(res.l);
	j.at("c").get_to(res.c);
	j.at("v").get_to(res.v);
}

void stb::stock_api::cdc::to_json(nlohmann::json& j, const response_attributes_get_candlestick& res)
{
	j = nlohmann::json{
		{ "instrument_name", res.instrument_name },
		{ "interval", res.interval },
		{ "data", res.data }
	};
}

void stb::stock_api::cdc::from_json(const nlohmann::json& j, response_attributes_get_candlestick& res)
{
	j.at("instrument_name").get_to(res.instrument_name);
	j.at("interval").get_to(res.interval);
	j.at("data").get_to(res.data);
}

void stb::stock_api::cdc::to_json(nlohmann::json& j, const response_attributes_get_instruments_array& res)
{
	nlohmann::json j_arr;

	for (const auto& attr : res)
	{
		nlohmann::json j_item = attr;
		j_arr.push_back(j_item);
	}

	j = j_arr;
}

void stb::stock_api::cdc::from_json(const nlohmann::json& j, response_attributes_get_instruments_array& res)
{
	for (const auto& j_item : j.at("instruments"))
	{
		res.push_back(j_item);
	}
}

void stb::stock_api::cdc::to_json(nlohmann::json& j, const response_attributes_var& res)
{
	std::visit([&j](auto&& arg)
		{
			j = arg;
		}, res);
}

stb::stock_api::cdc::response_attributes_var stb::stock_api::cdc::to_response(const nlohmann::json& j, const std::string& method)
{
	response_attributes_var ret;

	if (method == "public/get-instruments")
	{
		response_attributes_get_instruments_array res = j;
		ret = res;
	}
	else if (method == "public/get-candlestick")
	{
		response_attributes_get_candlestick res = j;
		ret = res;
	}
	else
	{
		throw std::invalid_argument{ "Invalid method" };
	}

	return ret;
}

void stb::stock_api::cdc::to_json(nlohmann::json& j, const response& res)
{
	j = nlohmann::json
	{
		{ "id", res.id },
		{ "method", res.method },
		{ "result", res.result },
		{ "code", res.code },
		{ "message", res.message },
		{ "original", res.original }
	};
}

void stb::stock_api::cdc::from_json(const nlohmann::json& j, response& res)
{
	if (j.find("id") != j.end())
	{
		j.at("id").get_to(res.id);
	}

	j.at("method").get_to(res.method);
	res.result = to_response(j.at("result"), res.method);
	j.at("code").get_to(res.code);

	if (j.find("message") != j.end())
	{
		j.at("message").get_to(res.message);
	}

	if (j.find("original") != j.end())
	{
		j.at("original").get_to(res.original);
	}
}

std::string stb::stock_api::cdc::to_string(view_period period)
{
	switch (period)
	{
	case view_period::minutes_1:
		return "1m";
	case view_period::minutes_5:
		return "5m";
	case view_period::minutes_15:
		return "15m";
	case view_period::minutes_30:
		return "30m";
	case view_period::hours_1:
		return "1h";
	case view_period::hours_4:
		return "4h";
	case view_period::hours_6:
		return "6h";
	case view_period::hours_12:
		return "12h";
	case view_period::days_one:
		return "1D";
	case view_period::weeks_one:
		return "7D";
	case view_period::weeks_two:
		return "14";
	case view_period::months_one:
		return "1M";
	default:
		throw std::invalid_argument{ "Invalid Period" };
	}
}

stb::stock_api::cdc::api::api(const api_params& params, transfer_protocol_ptr&& protocol)
	: stb::stock_api::api{ std::move(protocol) }
{

}

std::vector<stb::stock_api::stock_item> stb::stock_api::cdc::api::get_available_stock()
{
	const std::string name = "public/get-instruments";

	stb::transfer_protocol_response_ptr res_ptr = protocol().send(rest_api_sandbox + name, "");

	auto response_json = nlohmann::json::parse(res_ptr->data());
	response res = response_json;
	auto res_attribs = std::get<response_attributes_get_instruments_array>(res.result);

	std::vector<stock_item> ret;

	for (const auto& attrib : res_attribs)
	{
		if (attrib.quote_currency == "USDT")
		{
			stock_item item{ attrib.instrument_name, attrib.base_currency };
			ret.push_back(item);
		}
	}

	return ret;
}

std::vector<stb::stock_api::candlestick> stb::stock_api::cdc::api::get_candlestick(const stock_item& item, view_period period)
{
	const std::string name = "public/get-candlestick";
	const std::string request_address =
		rest_api_sandbox + name + "?instrument_name=" +
		std::string{ item.id() } +
		"&timeframe=" +
		to_string(period);

	stb::transfer_protocol_response_ptr res_ptr = protocol().send(request_address, "");

	auto response_json = nlohmann::json::parse(res_ptr->data());
	response res = response_json;
	auto res_attribs = std::get<response_attributes_get_candlestick>(res.result);

	std::vector<candlestick> ret;

	for (const auto& attrib : res_attribs.data)
	{
		candlestick candle
		{
			std::chrono::system_clock::from_time_t({ attrib.t }),
			attrib.o,
			attrib.h,
			attrib.l,
			attrib.c,
			attrib.v
		};

		ret.push_back(candle);
	}

	return ret;
}

stb::transfer_protocol_response_ptr stb::stock_api::cdc::post(request& req, transfer_protocol& protocol)
{
	sign_request(req, rest_api_sandbox);

	nlohmann::json req_json = req;

	try
	{
		std::string data = req_json.dump();
		return protocol.send(rest_api_sandbox + req.method, req_json.dump());
	}
	catch (const stb::transfer_failure& e)
	{
		// TODO: Convert status code from protocol to crypto.com status message
		throw e ;
	}
}