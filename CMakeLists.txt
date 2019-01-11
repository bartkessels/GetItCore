cmake_minimum_required(VERSION 3.9)

project(GetItCore
        VERSION 0.1
        DESCRIPTION "HTTP Request library"
)

set(HEADERS
    src/Cookie.hpp
    src/Header.hpp
    src/Request.hpp
    src/RawRequest.hpp
    src/ResponseListener.hpp
)

set(PUBLIC_HEADERS
    include/Cookie
    include/Header
    include/Request
    include/RawRequest
    include/ResponseListener
    ${HEADERS}
)

set(SOURCES
    src/GetItCore.cpp
    src/Header.cpp
    src/Request.cpp
    src/RawRequest.cpp
)

include(GNUInstallDirs)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
        VERSION ${PROJECT_VERSION}
        OUTPUT_NAME ${PROJECT_NAME}
        PUBLIC_HEADER "${PUBLIC_HEADERS}"
)

configure_file(getitcore.pc.in getitcore.pc @ONLY)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE src)

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
)

install(FILES ${CMAKE_BINARY_DIR}/getitcore.pc
	DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
)

find_package(CURL REQUIRED)

include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})

# Install: cmake ../ -DCMAKE_INSTALL_PREFIX:PATH=/usr
