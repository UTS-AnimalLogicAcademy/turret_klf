cmake_minimum_required(VERSION 2.6)

include(RezBuild)

FILE(GLOB_RECURSE py_files "python/*.py")

rez_install_python(
	py_files
	FILES
	${py_files}
	DESTINATION .
    LOCAL_SYMLINK
)

rez_install_dirs(
    Resources
    DESTINATION .
)


set(KATANA_HOME "$ENV{KATANA_HOME}" CACHE PATH "Path to Katana")

find_package(Katana PATHS "${KATANA_HOME}/plugin_apis/cmake" REQUIRED)
add_compile_options(-Wall)

# Ensure we don't compile DSOs with undefined symbols.
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-undefined")
set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -Wl,--no-undefined")

add_subdirectory(AutoLookfileAssign)
