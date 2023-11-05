find_package(Turret REQUIRED)
find_package(ZeroMQ REQUIRED)

set(BOOST_LIBRARY_DIR $ENV{BOOST_ROOT})

find_package(Boost
        COMPONENTS
        filesystem
        serialization
        REQUIRED
)

set(TBB_ROOT_DIR $ENV{TBBROOT})
set(TBB_INCLUDE_DIR $ENV{TBB_INCLUDE_DIR})
set(TBB_LIBRARY $ENV{TBB_LIBRARIES})

find_package(TBB REQUIRED COMPONENTS tbb)
add_definitions(${TBB_DEFINITIONS})

include_directories(
        ${TURRET_INCLUDES}
        ${CMAKE_SOURCE_DIR}/LookfilePropertyAssign/
        ${Boost_INCLUDE_DIRS}
        ${TBB_INCLUDE_DIR}
)

add_library(LookfilePropertyAssign MODULE src/lookfilePropertyAssignOp.cpp)

target_link_libraries(LookfilePropertyAssign
    PRIVATE
    ${ZeroMQ_LIBRARY}
    ${Boost_LIBRARIES}
    ${TBB_LIBRARIES}
    ${TURRET_LIBRARY}
    Katana::FnAttribute
    Katana::FnGeolibOpPlugin
    Katana::FnGeolibServices
)

set_target_properties(LookfilePropertyAssign PROPERTIES PREFIX "")

install(FILES RegisterLookfilePropertyAssignNode.py DESTINATION Resources/Plugins)
install(TARGETS LookfilePropertyAssign DESTINATION Resources/Ops)
