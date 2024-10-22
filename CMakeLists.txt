cmake_minimum_required(VERSION 3.2)

set (CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        ${CMAKE_SOURCE_DIR}/cmake/modules
        "${KATANA_HOME}/plugins/Src/cmake",
)

set(KATANA_HOME "$ENV{KATANA_HOME}" CACHE PATH "Path to Katana")

set(KATANA_ROOT "${KATANA_HOME}")

find_package(Katana PATHS "${KATANA_HOME}/plugin_apis/cmake" REQUIRED)
find_package(FdkBase PATHS "${KATANA_HOME}/plugin_apis/cmake" REQUIRED)
find_package(FnUsdEngine PATHS "${KATANA_HOME}/plugin_apis/cmake" REQUIRED)
add_compile_options(-Wall)

# Ensure we don't compile DSOs with undefined symbols.
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-undefined")
set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -Wl,--no-undefined")


if(DEFINED ENV{CXX11_ABI_IGNORE})
        set(CMAKE_CXX_FLAGS "-D_GLIBCXX_USE_CXX11_ABI=0 ${CMAKE_CXX_FLAGS}")
        message(INFO " CXX11_ABI_IGNORE set. Ignoring CXX11 flags.")
else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif(DEFINED ENV{CXX11_ABI_IGNORE})

add_subdirectory(AutoLookfileAssign)
add_subdirectory(LookfilePropertyAssign)
