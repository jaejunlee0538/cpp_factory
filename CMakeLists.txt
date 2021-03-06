cmake_minimum_required(VERSION 2.8.3)
project(cpp_factory)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_LIB_INSTALL_DIR "/usr/lib")
set(CMAKE_HEADERS_INSTALL_DIR "/usr/include")
#set(CMAKE_LIB_INSTALL_DIR "${PROJECT_SOURCE_DIR}/build_test/libs")
#set(CMAKE_HEADERS_INSTALL_DIR "${PROJECT_SOURCE_DIR}/build_test/include")
set(BUILD_EXAMPLES "TRUE")

find_package(PCL 1.7 REQUIRED)
# TODO : find_package(PCL...) overwrites ${Boost_LIBRARIES}
find_package(Boost REQUIRED COMPONENTS filesystem thread system regex)

include_directories(
libraries/include
${Boost_INCLUDE_DIRS}
${PCL_INCLUDE_DIRS}
)

#message("${Boost_LIBRARIES}")
if(${BUILD_EXAMPLES})
    set(LIB_EXAMPLES_SRC_DIR libraries/src/examples)

    add_executable(ex_PreciseClock ${LIB_EXAMPLES_SRC_DIR}/ex_PreciseClock.cpp)
    target_link_libraries(ex_PreciseClock cpp_factory)
    add_dependencies(ex_PreciseClock cpp_factory)

    add_executable(ex_LoopInterface ${LIB_EXAMPLES_SRC_DIR}/ex_LoopInterface.cpp)
    target_link_libraries(ex_LoopInterface cpp_factory)
    add_dependencies(ex_LoopInterface cpp_factory)

    add_executable(ex_stringConversions ${LIB_EXAMPLES_SRC_DIR}/string/ex_stringConversions.cpp)
    target_link_libraries(ex_stringConversions cpp_factory)
    add_dependencies(ex_stringConversions cpp_factory)

    add_executable(ex_libProfiler
        ${LIB_EXAMPLES_SRC_DIR}/libProfiler/ex_libProfiler.cpp
        ${LIB_EXAMPLES_SRC_DIR}/libProfiler/libProfilerTestClass.cpp  )
    target_link_libraries(ex_libProfiler cpp_factory)
    add_dependencies(ex_libProfiler cpp_factory)

    add_executable(ex_FileLister  ${LIB_EXAMPLES_SRC_DIR}/ex_FileLister.cpp)
    target_link_libraries(ex_FileLister cpp_factory ${Boost_LIBRARIES})
    add_dependencies(ex_FileLister cpp_factory)

    add_executable(ex_CodeMarker
    ${LIB_EXAMPLES_SRC_DIR}/CodeMarker/ex_CodeMarker.cpp
    ${LIB_EXAMPLES_SRC_DIR}/CodeMarker/MyClass1.cpp
    ${LIB_EXAMPLES_SRC_DIR}/CodeMarker/MyClass2.cpp)
    target_link_libraries(ex_CodeMarker cpp_factory)
    add_dependencies(ex_CodeMarker cpp_factory)

    add_executable(ex_MemberCheck  ${LIB_EXAMPLES_SRC_DIR}/ex_MemberCheck.cpp)
    target_link_libraries(ex_MemberCheck cpp_factory)
    add_dependencies(ex_MemberCheck cpp_factory)

    add_executable(ex_BoostRandom  ${LIB_EXAMPLES_SRC_DIR}/random/ex_boost_random.cpp)
    target_link_libraries(ex_BoostRandom cpp_factory)
    add_dependencies(ex_BoostRandom cpp_factory)

    add_executable(ex_EasyCloudViewer  ${LIB_EXAMPLES_SRC_DIR}/pcl/ex_EasyCloudViewer.cpp)
    target_link_libraries(ex_EasyCloudViewer cpp_factory)
    add_dependencies(ex_EasyCloudViewer cpp_factory)

    #    add_executable(ex_simpleProfiler  ${LIB_EXAMPLES_SRC_DIR}/ex_simpleProfiler.cpp)
#    target_link_libraries(ex_simpleProfiler cpp_factory)
#    add_dependencies(ex_simpleProfiler cpp_factory)
endif(${BUILD_EXAMPLES})

##############################################
set(CPP_FACTORY_LIB_SRC
    libraries/src/PreciseClock.cpp
    libraries/src/PIDController.cpp
    libraries/src/LoopInterface.cpp
    libraries/src/FileUtils.cpp
    libraries/src/conio_linux.cpp
    )

add_library(cpp_factory ${CPP_FACTORY_LIB_SRC})
target_link_libraries(cpp_factory pthread ${Boost_LIBRARIES} ${PCL_LIBRARIES})


add_subdirectory(examples)
##############################################
install(TARGETS cpp_factory DESTINATION ${CMAKE_LIB_INSTALL_DIR})
install(DIRECTORY libraries/include/cpp_factory DESTINATION ${CMAKE_HEADERS_INSTALL_DIR})
