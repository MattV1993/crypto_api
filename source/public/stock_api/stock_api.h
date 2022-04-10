#pragma once

#include "transfer_protocol/transfer_protocol.h"

#include <vector>
#include <memory>
#include <string>

namespace stb::stock_api
{
	class stock_item
	{
	public:

		stock_item(std::string_view id, std::string_view name);

		std::string_view id() const;
		std::string_view name() const;

	private:

		std::string id_;
		std::string name_;
	};

	using currency = float;

	class candlestick
	{
	public:

		std::chrono::time_point<std::chrono::system_clock> time;
		currency open;
		currency high;
		currency low;
		currency close;
		currency volume;
	};

	enum class view_period
	{
		minutes_1,
		minutes_5,
		minutes_15,
		minutes_30,
		hours_1,
		hours_4,
		hours_6,
		hours_12,
		days_one,
		weeks_one,
		weeks_two,
		months_one
	};

	class api
	{
	public:

		virtual ~api() = default;

		api(const api&) = delete;
		api(api&&) = delete;

		api& operator=(const api&) = delete;
		api& operator=(api&&) = delete;

		virtual std::vector<stock_item> get_available_stock() = 0;
		virtual std::vector<candlestick> get_candlestick(const stock_item& item, view_period period) = 0;

	protected:

		api(transfer_protocol_ptr&& protocol);

		transfer_protocol& protocol();

	private:

		transfer_protocol_ptr protocol_;

	};

	using api_ptr = std::unique_ptr<api>;
	
	template<class Params>
	api_ptr create_api(const Params& params, transfer_protocol_ptr&& protocol);

	template<class Api, class Params>
	inline api_ptr create_api(const Params& params, transfer_protocol_ptr&& protocol)
	{
		return std::make_unique<Api>(params, std::move(protocol));
	}
}