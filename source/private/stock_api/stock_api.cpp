#include "stock_api/stock_api.h"

stb::stock_api::stock_item::stock_item(std::string_view id, std::string_view name)
	: id_{ id }, name_ { name }
{

}

std::string_view stb::stock_api::stock_item::id() const
{
	return id_;
}

std::string_view stb::stock_api::stock_item::name() const
{
	return name_;
}

stb::stock_api::api::api(transfer_protocol_ptr&& protocol)
	: protocol_{ std::move(protocol) }
{
}

stb::transfer_protocol& stb::stock_api::api::protocol()
{
	return *protocol_;
}
