set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        "/mnt/ala/software/pipeline/rez/lib/python2.6/site-packages/rez-2.2.0-py2.6.egg/rezplugins/build_system/cmake_files"
        "$ENV{REZ_UTSALA_CMAKE_MODULES_ROOT}/cmake/Modules"
        "${KATANA_HOME}/plugins/Src/cmake"
        )

#file(GLOB SOURCES src/zmqClient.h src/zmqClient.cpp)
include_directories($ENV{ZMQ_CLIENT_INCLUDE} $ENV{BOOST_ROOT}/include)
add_library(AutoLookfileAssign MODULE src/autoLookfileAssignOp.cpp)

# to do - link against libzmq library
# link_directories($ENV{REZ_LIBZMQ_ROOT}/lib)
# link against libzmq.so

target_link_libraries(AutoLookfileAssign
    PRIVATE
    #/mnt/ala/software/ext_packages/libzmq/4.2.3/lib/libzmq.so
    $ENV{ZMQ_CLIENT_LIB}/libzmq_client_cpp.so
    Katana::FnAttribute
    Katana::FnGeolibOpPlugin
    Katana::FnGeolibServices
)

set_target_properties(AutoLookfileAssign PROPERTIES PREFIX "")

install(FILES RegisterAutoLookfileAssignNode.py DESTINATION Resources/Plugins)
install(TARGETS AutoLookfileAssign DESTINATION Resources/Ops)
