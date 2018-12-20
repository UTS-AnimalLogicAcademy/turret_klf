set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        "/mnt/ala/software/pipeline/cmake/modules/rez"
        ${CMAKE_SOURCE_DIR}/cmake/modules
        "$ENV{REZ_UTSALA_CMAKE_MODULES_ROOT}/cmake/Modules"
        "${KATANA_HOME}/plugins/Src/cmake"        
)

find_package(Turret REQUIRED)
find_package(ZeroMQ REQUIRED)

find_package(Boost
        COMPONENTS
        filesystem
        serialization
        REQUIRED
        )

link_directories($ENV{REZ_USD_ROOT}/lib
        $ENV{REZ_TBB_ROOT}/lib/intel64/gcc4.4/
        ${TURRET_LIBRARY}
)

target_include_directories(turret PRIVATE
        ${TURRET_INCLUDES}
        ${CMAKE_SOURCE_DIR}/AutoLookfileAssign/
#        ${PC_LIBZMQ_INCLUDE_DIRS}
        ${Boost_INCLUDE_DIRS}
#        ${CPPZMQ_INCLUDE_DIRS}
        )

add_library(AutoLookfileAssign MODULE src/autoLookfileAssignOp.cpp)

target_link_libraries(turret
        ${ZeroMQ_LIBRARY}
        ${Boost_LIBRARIES}
        )

target_link_libraries(AutoLookfileAssign
    PRIVATE
    ${ZeroMQ_LIBRARY}
    ${Boost_LIBRARIES}
    ${TURRET_LIBRARY}
    Katana::FnAttribute
    Katana::FnGeolibOpPlugin
    Katana::FnGeolibServices
)

set_target_properties(AutoLookfileAssign PROPERTIES PREFIX "")

install(FILES RegisterAutoLookfileAssignNode.py DESTINATION Resources/Plugins)
install(TARGETS AutoLookfileAssign DESTINATION Resources/Ops)
