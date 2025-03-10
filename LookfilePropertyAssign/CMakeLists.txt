set(TBB_ROOT_DIR $ENV{TBBROOT})
set(TBB_INCLUDE_DIR $ENV{TBB_INCLUDE_DIR})
set(TBB_LIBRARY $ENV{TBB_LIBRARIES})

find_package(TBB REQUIRED COMPONENTS tbb)
add_definitions(${TBB_DEFINITIONS})

include_directories(
        ${TURRET_INCLUDES}
        ${CMAKE_SOURCE_DIR}/LookfilePropertyAssign/
        ${TBB_INCLUDE_DIR}
)

add_library(LookfilePropertyAssignOp MODULE src/lookfilePropertyAssignOp.cpp)

target_link_libraries(LookfilePropertyAssignOp
    PRIVATE
    ${TBB_LIBRARIES}
    Katana::FnAttribute
    Katana::FnGeolibOpPlugin
    Katana::FnGeolibServices
)

set_target_properties(LookfilePropertyAssignOp PROPERTIES PREFIX "")

install(FILES RegisterLookfilePropertyAssignNode.py DESTINATION Resources/Plugins)
install(TARGETS LookfilePropertyAssignOp DESTINATION Resources/Ops)

if(TURRET_KLF_BUILD_USD_ENGINE)
    add_library(LookfilePropertyAssignUsdEngine MODULE src/lookfilePropertyAssignUsdEngine.cpp)

    target_link_libraries(LookfilePropertyAssignUsdEngine
        PRIVATE
        ${TBB_LIBRARIES}
        Katana::FnPluginSystem
        Fn::FdkBase
        Fn::UsdEngine
    )
    set_target_properties(LookfilePropertyAssignUsdEngine PROPERTIES PREFIX "")
    install(FILES RegisterLookfilePropertyAssignUSDNode.py DESTINATION Resources/Plugins)
    install(TARGETS LookfilePropertyAssignUsdEngine DESTINATION Resources/Engines)
endif()