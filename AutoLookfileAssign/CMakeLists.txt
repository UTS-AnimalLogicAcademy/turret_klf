find_package(Turret REQUIRED)
find_package(ZeroMQ REQUIRED)

find_package(Boost
        COMPONENTS
        filesystem
        serialization
        REQUIRED
)

set(TBB_ROOT_DIR $ENV{REZ_TBB_ROOT})
set(TBB_INCLUDE_DIR $ENV{REZ_TBB_ROOT}/include)
set(TBB_LIBRARY $ENV{TBB_LIBRARIES})

find_package(TBB REQUIRED COMPONENTS tbb)
add_definitions(${TBB_DEFINITIONS})

include_directories(
        ${TURRET_INCLUDES}
        ${CMAKE_SOURCE_DIR}/AutoLookfileAssign/
        ${Boost_INCLUDE_DIRS}
        ${TBB_INCLUDE_DIR}
)

add_library(AutoLookfileAssign MODULE src/autoLookfileAssignOp.cpp)

target_link_libraries(AutoLookfileAssign
    PRIVATE
    ${ZeroMQ_LIBRARY}
    ${Boost_LIBRARIES}
    ${TBB_LIBRARIES}
    ${TURRET_LIBRARY}
    Katana::FnAttribute
    Katana::FnGeolibOpPlugin
    Katana::FnGeolibServices
)

set_target_properties(AutoLookfileAssign PROPERTIES PREFIX "")

install(FILES RegisterAutoLookfileAssignNode.py DESTINATION Resources/Plugins)
install(TARGETS AutoLookfileAssign DESTINATION Resources/Ops)
