cmake_minimum_required (VERSION 3.10.2)
set ( CMAKE_CXX_COMPILER clang++ )
SET ( CMAKE_CXX_FLAGS "-std=c++11" )
project ( papiris )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build)

# IMPORTANT: Set these correctly.
set( OPENSSL_SSL_LIBRARIES /usr/local/ssl/lib            )
set( OPENSSL_INCLUDE_DIR   /usr/loca/ssl/include/openssl )
set( OPEN_ROOT_DIR         /usr/local/ssl                )

# main sources
file(GLOB_RECURSE sources "src/*.cpp" "src/*.hpp")

file(GLOB_RECURSE libraries "lib/*.cpp" "lib/*.c" "lib/*.hpp" "lib/*.h")

find_package( PkgConfig REQUIRED )

# Boost
FIND_PACKAGE( Boost 1.66 COMPONENTS filesystem REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

# ImageMagick
FIND_PACKAGE( ImageMagick COMPONENTS Magick++ convert )
INCLUDE_DIRECTORIES( ${ImageMagick_INCLUDE_DIRS} )

# OpenSSL
FIND_PACKAGE( OpenSSL )
INCLUDE_DIRECTORIES( ${OPENSSL_INCLUDE_DIR} )

# Leptonica
#FIND_PACKAGE( Leptonica REQUIRED )
pkg_search_module( Leptonica REQUIRED lept )
INCLUDE_DIRECTORIES( ${Leptonica_INCLUDE_DIRS} )
link_directories( ${Leptonica_LIBRARY_DIRS} )

# Tesseract
FIND_PACKAGE( Tesseract 3.05 REQUIRED )
#pkg_search_module( TESSERACT 3.05 REQUIRED tesseract )
INCLUDE_DIRECTORIES( ${Tesseract_INCLUDE_DIRS} )
link_directories( ${Tesseract_LIBRARY_DIRS} )

add_executable ( papiris ${sources} ${libraries} )

# link Boost
TARGET_LINK_LIBRARIES( papiris LINK_PUBLIC ${Boost_LIBRARIES} )

# link ImageMagick
TARGET_LINK_LIBRARIES( papiris LINK_PUBLIC ${ImageMagick_LIBRARIES} )

# link OpenSSL
TARGET_LINK_LIBRARIES( papiris LINK_PUBLIC ${OPENSSL_CRYPTO_LIBRARY} )

# link Leptonica
TARGET_LINK_LIBRARIES( papiris LINK_PUBLIC ${Leptonica_LIBRARIES} )

# link Tesseract
TARGET_LINK_LIBRARIES( papiris LINK_PUBLIC ${Tesseract_LIBRARIES} )
