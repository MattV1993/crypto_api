#pragma once

#include "stock_api.h"

#include "nlohmann/json.hpp"

#include <variant>

const std::string api_key = "KqPUQDxMfUqQTzHdbkF157";
const std::string secret_key = "bYX6twYoi2ekf1b82bvMiy";

const std::string rest_api_sandbox = "https://uat-api.3ona.co/v2/";
const std::string rest_api_production = "https://api.crypto.com/v2/";

// api key: KqPUQDxMfUqQTzHdbkF157
// secret key: bYX6twYoi2ekf1b82bvMiy

/*
UAT Sandbox
REST API v2
https://uat-api.3ona.co/v2/{method}

REST API v1
https://uat-api.3ona.co/v1/{method}

Production
REST API v2
https://api.crypto.com/v2/{method}

REST API v1
https://api.crypto.com/v1/{method}



The Websocket is available across two servers -- the User API Websocket (for authenticated requests and subscriptions), and Market Data Websocket:

UAT Sandbox
Websocket (User API and Subscriptions)
wss://uat-stream.3ona.co/v2/user

Websocket (Market Data Subscriptions)
wss://uat-stream.3ona.co/v2/market

Production
Websocket (User API and Subscriptions)
wss://stream.crypto.com/v2/user

Websocket (Market Data Subscriptions)
wss://stream.crypto.com/v2/market
*/



namespace stb::stock_api::cdc
{
	enum class message_code : uint32_t
	{
		NONE = 0,
		SYS_ERROR = 10001,
		UNAUTHORIZED = 10002,
		IP_ILLEGAL = 10003,
		BAD_REQUEST = 10004,
		USER_TIER_INVALID = 10005,
		TOO_MANY_REQUESTS = 10006,
		INVALID_NONCE = 10007,
		METHOD_NOT_FOUND = 10008,
		INVALID_DATE_RANGE = 10009,
		DUPLICATE_RECORD = 20001,
		NEGATIVE_BALANCE = 20002,
		SYMBOL_NOT_FOUND = 30003,
		SIDE_NOT_SUPPORTED = 30004,
		ORDERTYPE_NOT_SUPPORTED = 30005,
		MIN_PRICE_VIOLATED = 30006,
		MAX_PRICE_VIOLATED = 30007,
		MIN_QUANTITY_VIOLATED = 30008,
		MAX_QUANTITY_VIOLATED = 30009,
		MISSING_ARGUMENT = 30010,
		INVALID_PRICE_PRECISION = 30013,
		INVALID_QUANTITY_PRECISION = 30014,
		MIN_NOTIONAL_VIOLATED = 30016,
		MAX_NOTIONAL_VIOLATED = 30017,
		MIN_AMOUNT_VIOLATED = 30023,
		MAX_AMOUNT_VIOLATED = 30024,
		AMOUNT_PRECISION_OVERFLOW = 30025,
		MG_INVALID_ACCOUNT_STATUS = 40001,
		MG_TRANSFER_ACTIVE_LOAN = 40002,
		MG_INVALID_LOAN_CURRENCY = 40003,
		MG_INVALID_REPAY_AMOUNT = 40004,
		MG_NO_ACTIVE_LOAN = 40005,
		MG_BLOCKED_BORROW = 40006,
		MG_BLOCKED_NEW_ORDER = 40007,
		DW_CREDIT_LINE_NOT_MAINTAINED = 50001
	};

	struct request_params_none
	{

	};

	void to_json(nlohmann::json& j, const request_params_none& par);
	void from_json(const nlohmann::json& j, request_params_none& req);

	struct request_params_auth
	{
		std::string api_key;	// API key
		std::string sig;		// Digital Signature
	};

	void to_json(nlohmann::json& j, const request_params_auth& par);
	void from_json(const nlohmann::json& j, request_params_auth& req);

	struct request_params_create_withdrawal
	{
		std::string client_wid;		// Optional Client withdrawal ID
		std::string currency;		// E.g. BTC, CRO
		double amount;
		std::string address;
		std::string address_tag;	//Secondary address identifier for coins like XRP, XLM etc. Also known as memo or tags.
	};

	using request_params_var = std::variant<
		request_params_none,
		request_params_auth,
		request_params_create_withdrawal>;

	std::string to_string(const request_params_var& params);

	void to_json(nlohmann::json& j, const request_params_var& req);
	request_params_var to_param(const nlohmann::json& j, const std::string& method);

	class request
	{
	public:

		int64_t id;					// Response message will contain the same id
		std::string method;			// The method to be invoked
		request_params_var params;	// Parameters for the methods
		std::string api_key;		// API key
		std::string sig;			// Digital signature
		int64_t nonce;				// Current timestamp (milliseconds since the Unix epoch)
	};

	void to_json(nlohmann::json& j, const request& req);
	void from_json(const nlohmann::json& j, request& req);

	void sign_request(request& req, std::string_view secret_key);

	struct response_attributes_get_instruments
	{
		std::string instrument_name;	// e.g. BTC_USDT
		std::string quote_currency;		// e.g. USDT
		std::string base_currency;		// e.g. BTC
		int32_t price_decimals;			// Maximum decimal places for specifying price
		int32_t quantity_decimals;		// Maximum decimal places for specifying quantity
		bool margin_trading_enabled;	// true or false
	};

	void to_json(nlohmann::json& j, const response_attributes_get_instruments& res);
	void from_json(const nlohmann::json& j, response_attributes_get_instruments& res);

	struct response_attributes_get_candlestick_data
	{
		int64_t t;	//End time of candlestick(Unix timestamp)
		float o;	// Open
		float h;	// High
		float l;	// Low
		float c;	// Close
		float v;	// Volume
	};

	void to_json(nlohmann::json& j, const response_attributes_get_candlestick_data& res);
	void from_json(const nlohmann::json& j, response_attributes_get_candlestick_data& res);

	using response_attributes_get_candlestick_data_array = std::vector<response_attributes_get_candlestick_data>;

	void to_json(nlohmann::json& j, const response_attributes_get_candlestick_data_array& res);
	void from_json(const nlohmann::json& j, response_attributes_get_candlestick_data_array& res);

	struct response_attributes_get_candlestick
	{
		std::string instrument_name;							// e.g. ETH_CRO, BTC_USDT
		std::string interval;									// The period (e.g. 5m)
		response_attributes_get_candlestick_data_array data;
	};

	void to_json(nlohmann::json& j, const response_attributes_get_candlestick& res);
	void from_json(const nlohmann::json& j, response_attributes_get_candlestick& res);

	using response_attributes_get_instruments_array = std::vector<response_attributes_get_instruments>;

	void to_json(nlohmann::json& j, const response_attributes_get_instruments_array& res);
	void from_json(const nlohmann::json& j, response_attributes_get_instruments_array& res);

	using response_attributes_var = std::variant<
		response_attributes_get_instruments_array,
		response_attributes_get_candlestick
		>;

	void to_json(nlohmann::json& j, const response_attributes_var& req);
	response_attributes_var to_response(const nlohmann::json& j, const std::string& method);

	struct response
	{
		int64_t id;						// Original request identifier
		std::string method;				// Method invoked
		response_attributes_var result;	// Result object
		message_code code;				// 0 for success
		std::string message;			// (optional) For server or error messages
		std::string original;			// (optional) Original request as a string, for error cases
	};

	void to_json(nlohmann::json& j, const response& res);
	void from_json(const nlohmann::json& j, response& res);

	struct api_params
	{

	};

	std::string to_string(view_period period);

	class api : public stb::stock_api::api
	{
	public:

		api(const api_params& params, transfer_protocol_ptr&& protocol);

		std::vector<stock_item> get_available_stock() override;

		std::vector<candlestick> get_candlestick(const stock_item& item, view_period period) override;

	private:

	};

	stb::transfer_protocol_response_ptr post(request& req, transfer_protocol& protocol);
}
