#include "stock_api/stock_api_cdc.h"
#include "socket/socket.h"

#include "chart/chart.h"

#include "SDL.h"

#define SK_GL
#define NOMINMAX
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#define GR_GL_CHECK_ERROR 0
#define GR_GL_LOG_CALLS 0

#include "skia/include/core/SkSurface.h"
#include "skia/include/core/SkPaint.h"
#include "skia/include/core/SkPath.h"

#include <skia/include/gpu/GrDirectContext.h>
#include <skia/include/gpu/gl/GrGLTypes.h>
#include <skia/include/core/SkImageInfo.h>

#include <include/core/SkCanvas.h>
#include <include/gpu/gl/GrGLInterface.h>
#include <include/gpu/GrDirectContext.h>

#include "src/gpu/gl/GrGLUtil.h"

#ifdef _WIN32
#include <Windows.h>
#include <gl/GL.h>
#endif

#include <iostream>

int main(int argc, char* argv[])
{
	// Get candlesticks for BTC_USDT pair
	stb::stock_api::stock_item item{ "BTC_USDT", "BTC" };

	auto socket = std::make_unique<stb::http::socket>();
	stb::stock_api::cdc::api_params params;

	auto api = stb::stock_api::create_api<stb::stock_api::cdc::api>(params, std::move(socket));

	std::vector<stb::stock_api::candlestick> candlesticks = api->get_candlestick(item, stb::stock_api::view_period::hours_1);

	// Setup SDL Window
	std::string name{ "Stock Trading Bot" };

	int width{ 1600 };
	int height{ 900 };

	SDL_Window* window{ nullptr };
	SDL_GLContext context{ nullptr };

	int flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
	bool closed = false;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	if (SDL_Init(SDL_INIT_VIDEO))
	{
		std::cout << "SDL INITIALISATION FAILED" << std::endl;
		std::cout << "Error message: " << SDL_GetError() << std::endl;
		return false;
	}

	window = SDL_CreateWindow(
		name.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		flags);

	if (window == nullptr)
	{
		std::cout << "Failed to create window" << std::endl;
		std::cout << "Error message: " << SDL_GetError() << std::endl;
		return false;
	}

	std::cout << "Window created successfully" << std::endl;

	context = SDL_GL_CreateContext(window);

	if (context == nullptr)
	{
		std::cout << "Failed to create context" << std::endl;
		std::cout << "Error message: " << SDL_GetError() << std::endl;
		return false;
	}

	std::cout << "Context created successfully" << std::endl;

	// Setup Skia context
	uint32_t window_format = SDL_GetWindowPixelFormat(window);
	SkColorType colour_type;

	if (window_format == SDL_PIXELFORMAT_RGBA8888)
	{
		colour_type = kRGBA_8888_SkColorType;
	}
	else
	{
		colour_type = kBGRA_8888_SkColorType;
	}

	sk_sp<const GrGLInterface> native_gl_interface = GrGLMakeNativeInterface();
	sk_sp<GrDirectContext> gr_context_ = GrDirectContext::MakeGL(native_gl_interface);

	GrGLint gl_buffer;
	GR_GL_GetIntegerv(native_gl_interface.get(), GR_GL_RENDERBUFFER_BINDING, &gl_buffer);

	GrGLFramebufferInfo buffer_info;
	buffer_info.fFBOID = gl_buffer;

	if (colour_type == kRGBA_8888_SkColorType)
	{
		buffer_info.fFormat = GR_GL_RGBA8;
	}
	else
	{
		buffer_info.fFormat = GR_GL_RGBA8;
	}

	GrBackendRenderTarget backend_target{
		static_cast<int>(width),
		static_cast<int>(height),
		1,
		8,
		buffer_info };

	sk_sp<SkSurface> sk_surface_ = SkSurface::MakeFromBackendRenderTarget(
		gr_context_.get(),
		backend_target,
		kTopLeft_GrSurfaceOrigin,
		colour_type,
		nullptr,
		nullptr);

	SkCanvas* canvas_ = sk_surface_->getCanvas();
	SkPaint paint_;

    SDL_Event event;
    bool running = true;

	paint_.setAntiAlias(true);

	paint_.setStrokeWidth(1);
	paint_.setStyle(SkPaint::kStroke_Style);
	paint_.setColor({ 0, 0, 0, 1 });

	SkPath path;

	// Create chart from candlesticks
	stb::stock_api::chart chart{ { {5, 5}, { 1200, 800} }, candlesticks };

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            running = event.type != SDL_QUIT;
        }

		canvas_->clear(SK_ColorWHITE);

		chart.draw(*canvas_);

		canvas_->flush();
        SDL_GL_SwapWindow(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


