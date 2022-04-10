set(SDL2_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/third_party/SDL/include")

if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
  set(SDL2_LIBRARIES "${CMAKE_SOURCE_DIR}/third_party/lib/SDL2/x64/SDL2.lib;${CMAKE_SOURCE_DIR}/third_party/lib/SDL2/x64/SDL2main.lib")
else ()
  set(SDL2_LIBRARIES "${CMAKE_SOURCE_DIR}/third_party/lib/SDL2/x86/SDL2.lib;${CMAKE_SOURCE_DIR}/third_partylib/SDL2/x86/SDL2main.lib")
endif ()

string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)