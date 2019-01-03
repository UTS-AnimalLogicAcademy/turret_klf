find_package(Turret REQUIRED)
find_package(ZeroMQ REQUIRED)

find_package(Boost
        COMPONENTS
        filesystem
        serialization
        REQUIRED
        )

include_directories(
        ${TURRET_INCLUDES}
        ${CMAKE_SOURCE_DIR}/AutoLookfileAssign/
        ${Boost_INCLUDE_DIRS}
        )

add_library(AutoLookfileAssign MODULE src/autoLookfileAssignOp.cpp)

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
