cmake_minimum_required(VERSION 3.22)
project(SimpleHardwareDaemon)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SOURCE_FILES main.cpp miscFunctions.cpp essentialFunctions.cpp userVariables.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

