#include "chart/chart.h"

namespace
{
	void draw_rect(stb::stock_api::frect& r, SkCanvas& canvas, SkPaint paint)
	{
		SkPath path;

		path.moveTo(r.min.x, r.min.y);
		path.lineTo(r.max.x, r.min.y);
		path.lineTo(r.max.x, r.max.y);
		path.lineTo(r.min.x, r.max.y);
		path.lineTo(r.min.x, r.min.y);
		
		canvas.drawPath(path, paint);
	}

	void draw_candle_stick(const stb::stock_api::candlestick& c, float x, float thickness, float scale, SkCanvas& canvas)
	{
		SkPaint paint;

		if (c.open > c.close)
		{
			paint.setColor({ 1.f, 0.f, 0.f, 1.f });
		}
		else
		{
			paint.setColor({ 0.f, 1.f, 0.f, 1.f });
		}

		paint.setStyle(SkPaint::kFill_Style);

		stb::stock_api::currency miny = std::min(c.close, c.open);
		stb::stock_api::currency maxy = std::max(c.close, c.open);

		draw_rect(
			stb::stock_api::frect{ { x, miny * scale }, { x + thickness, maxy * scale } },
			canvas, paint);
	}
}

stb::stock_api::chart::chart(const frect& bounds, const std::vector<candlestick> candlesticks)
	: bounds{ bounds }, candlesticks{ candlesticks }
{
	if (candlesticks.size() == 0)
	{
		return;
	}

	currency min = candlesticks.front().low;
	currency max = candlesticks.front().high;

	for (const auto& candlestick : candlesticks)
	{
		min = std::min(min, candlestick.low);
		max = std::max(max, candlestick.high);
	}
}

void stb::stock_api::chart::chart::draw(SkCanvas& canvas)
{
	SkPaint paint;
	paint.setAntiAlias(true);

	paint.setStrokeWidth(1);
	paint.setStyle(SkPaint::kStroke_Style);
	paint.setColor({ 0, 0, 0, 1 });

	draw_rect(bounds, canvas, paint);

	if (candlesticks.size() == 0)
	{
		return;
	}

	float scale = 0.01;
	float thickness = 5;
	float x = 0;

	for (const auto& candlestick : candlesticks)
	{
		draw_candle_stick(candlestick, x, thickness, scale, canvas);
		x += thickness;
	}
}