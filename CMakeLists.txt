cmake_minimum_required(VERSION 2.8.3)
project(cpp_factory)


set(CMAKE_LIB_INSTALL_DIR "${PROJECT_SOURCE_DIR}/build_test/libs")
set(CMAKE_HEADERS_INSTALL_DIR "${PROJECT_SOURCE_DIR}/build_test/include")
set(BUILD_EXAMPLES "TRUE")

include_directories(libraries/include)



if(${BUILD_EXAMPLES})
    set(LIB_EXAMPLES_SRC_DIR libraries/src/examples)

    add_executable(ex_PreciseClock ${LIB_EXAMPLES_SRC_DIR}/ex_PreciseClock.cpp)
    target_link_libraries(ex_PreciseClock cpp_factory)
    add_dependencies(ex_PreciseClock cpp_factory)

    add_executable(ex_LoopInterface ${LIB_EXAMPLES_SRC_DIR}/ex_LoopInterface.cpp)
    target_link_libraries(ex_LoopInterface cpp_factory)
    add_dependencies(ex_LoopInterface cpp_factory)

    add_executable(ex_ConsoleUtils ${LIB_EXAMPLES_SRC_DIR}/ex_ConsoleUtils.cpp)
    target_link_libraries(ex_ConsoleUtils cpp_factory)
    add_dependencies(ex_ConsoleUtils cpp_factory)
endif(${BUILD_EXAMPLES})

##############################################
set(CPP_FACTORY_LIB_SRC
    libraries/src/PreciseClock.cpp
    libraries/src/PIDController.cpp
    libraries/src/LoopInterface.cpp
    )

add_library(cpp_factory ${CPP_FACTORY_LIB_SRC})
target_link_libraries(cpp_factory pthread)


add_subdirectory(examples)
##############################################
install(TARGETS cpp_factory DESTINATION ${CMAKE_LIB_INSTALL_DIR})
install(DIRECTORY libraries/include/cpp_factory DESTINATION ${CMAKE_HEADERS_INSTALL_DIR})
