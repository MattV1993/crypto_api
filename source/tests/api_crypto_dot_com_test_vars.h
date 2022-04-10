#pragma once

#include "stock_api/stock_api_cdc.h"

#include <string>

const std::string test_api_key = "test_api_key";
const std::string test_secret_key = "test_private_key";
const std::string test_sig = "test_sig";
const int64_t test_id = 111;
const std::string test_method = "test_method";
const int64_t test_nonce = 999;

const std::string test_instrument_name = "test_name";
const std::string test_quote_currency = "test_quote_currency";
const std::string test_base_currency = "test_base_currency";;
const int32_t test_price_decimals = 3;
const int32_t test_quantity_decimals = 2;
const bool test_margin_trading_enabled = false;

const stb::stock_api::cdc::message_code test_code = stb::stock_api::cdc::message_code::METHOD_NOT_FOUND;
const std::string test_message = "test_message";
const std::string test_original = "test_original";

const std::string test_currency1 = "cur1";
const std::string test_currency2 = "cur2";
const std::string test_currency3 = "cur3";
const std::string test_currency4 = "cur4";

const int64_t test_t = 12345678;
const int32_t test_o = 2;
const int32_t test_h = 3;
const int32_t test_l = 5;
const int32_t test_c = 7;
const int32_t test_v = 9;

const std::string test_interval = "test_interval";