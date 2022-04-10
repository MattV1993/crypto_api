cmake_minimum_required(VERSION 3.15)
project(stock_trading_bot C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set_property(GLOBAL PROPERTY USE_FOLDERS on)

set(SRC_DIR "${CMAKE_CURRENT_LIST_DIR}")

# stock_api -----------------------------------------

set(SOURCE_STOCK_API
    "${SRC_DIR}/source/public/stock_api/stock_api.h"
    "${SRC_DIR}/source/private/stock_api/stock_api.cpp"
    "${SRC_DIR}/source/public/stock_api/stock_api_cdc.h"
    "${SRC_DIR}/source/private/stock_api/stock_api_cdc.cpp"
    "${SRC_DIR}/source/public/stock_api/stock_api_utils.h"
    "${SRC_DIR}/source/private/stock_api/stock_api_utils.cpp"
    "${SRC_DIR}/source/public/socket/socket.h"
    "${SRC_DIR}/source/private/socket/socket.cpp"
    "${SRC_DIR}/source/public/socket/socket_curl.h"
    "${SRC_DIR}/source/private/socket/socket_curl.cpp"
    "${SRC_DIR}/source/public/socket/socket_utils.h"
    "${SRC_DIR}/source/private/socket/socket_utils.cpp"
    "${SRC_DIR}/source/public/transfer_protocol/transfer_protocol.h"
    "${SRC_DIR}/source/public/chart/chart.h"
    "${SRC_DIR}/source/private/chart/chart.cpp"
)

add_library(stock_trading_bot STATIC "${SOURCE_STOCK_API}")

target_include_directories(stock_trading_bot PUBLIC
    "${SRC_DIR}/source/public/"
)

set(SOURCE_STOCK_API_EXE
    "${SRC_DIR}/source/main.cpp"
)

add_executable(stock_trading_bot_exe "${SOURCE_STOCK_API_EXE}")

# Third party ----------------------------------------

target_include_directories(stock_trading_bot PUBLIC "${SRC_DIR}/third_party")

target_link_libraries(stock_trading_bot_exe stock_trading_bot)

set(CURL_NO_CURL_CMAKE on)
	  
set(CURL_LIBRARY "${SRC_DIR}/third_party/lib/curl/libcurl-vc-x64-debug-static-ipv6-sspi-schannel/lib/libcurl_a_debug.lib")
set(CURL_INCLUDE_DIR "${SRC_DIR}/third_party/lib/curl/libcurl-vc-x64-debug-static-ipv6-sspi-schannel/include")

find_package(CURL REQUIRED)

target_include_directories(stock_trading_bot PUBLIC ${CURL_INCLUDE_DIR})
target_link_libraries(stock_trading_bot ${CURL_LIBRARIES})

target_include_directories(stock_trading_bot PUBLIC "${SRC_DIR}/third_party/json/single_include")

target_include_directories(stock_trading_bot PUBLIC 
    "${SRC_DIR}/source/public"
)

target_include_directories(stock_trading_bot PUBLIC "${SRC_DIR}/third_party/cryptopp")
target_link_libraries(stock_trading_bot "${SRC_DIR}/third_party/lib/cryptopp/Debug/cryptlib.lib")

target_include_directories(stock_trading_bot PUBLIC "${SRC_DIR}/third_party/di/include")

target_include_directories(stock_trading_bot PUBLIC "${SRC_DIR}/third_party/skia/")
target_include_directories(stock_trading_bot PUBLIC "${SRC_DIR}/third_party/skia/skia/")

target_link_libraries(stock_trading_bot
    "${SRC_DIR}/third_party/skia/libs/Debug/skia.lib"
    opengl32.lib
)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

target_link_libraries(stock_trading_bot ${SDL2_LIBRARIES})

add_custom_command(TARGET stock_trading_bot_exe POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        "${CMAKE_SOURCE_DIR}/third_party/lib/SDL2/x64/SDL2.dll"
        $<TARGET_FILE_DIR:stock_trading_bot_exe>)  

# Tests ---------------------------------------------

set(TEST_SOURCE
"${SRC_DIR}/source/tests/api_crypto_dot_com_test_vars.h"
    "${SRC_DIR}/source/tests/api_crypto_dot_com_tests.cpp"
    "${SRC_DIR}/source/tests/api_crypto_dot_com_api_tests.cpp"
)

add_subdirectory("${SRC_DIR}/third_party/googletest" "${CMAKE_CURRENT_BINARY_DIR}/googletest")
add_executable(stock_trading_bot_tests "${TEST_SOURCE}")

target_link_libraries(
    stock_trading_bot_tests
    stock_trading_bot
    gtest
    gtest_main
    ${Pthread}
)
