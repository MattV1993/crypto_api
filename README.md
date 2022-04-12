crypto_api
==========

Project Aims
------------

- Create system which will communicate with various crypto trading platforms
- Display stock price data

Current Project Status
----------------------

- Communicates with Crypto.com api to retreive stock data
- Displays stock data visually (Currently in progress)

Prerequisites
-------------
- Visual Studio
- CMake 3.15 or above

Setup
-----
- run: git submodule update --init --recursive
- run: mkdir build
- run: cd build
- run: cmake ..

Limitations
-----------
- Currently only works in release due to large debug library sizes
