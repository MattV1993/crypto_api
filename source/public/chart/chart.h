#pragma once

#include "stock_api/stock_api.h"

#include "skia/include/core/SKCanvas.h"
#include "skia/include/core/SkPaint.h"
#include "skia/include/core/SkPath.h"

namespace stb::stock_api
{
	template<class T>
	struct vec2
	{
		T x;
		T y;
	};

	template<class T>
	struct rect
	{
		vec2<T> min;
		vec2<T> max;
	};

	using ivec2 = vec2<int64_t>;
	using fvec2 = vec2<float>;

	using irect = rect<int64_t>;
	using frect = rect<float>;


	class chart
	{
	public:

		chart(const frect& bounds, const std::vector<candlestick> candlesticks);
		void draw(SkCanvas& paint);

	private:

		frect bounds;
		std::vector<candlestick> candlesticks;
	};

}