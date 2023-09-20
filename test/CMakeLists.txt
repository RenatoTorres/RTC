cmake_minimum_required(VERSION 3.14)
project(test_RTC_API)

set(SOURCES
    src/test_RTC_API.c
    src/unittests.c
    src/unittest_framework.c
    src/unittest_main.c
)

# Specify the include directories for the target (my_static_lib in this case)
target_include_directories(test_RTC_API
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib/inc  # Include directories for public headers
)

add_executable(
  terminal_RTC_API
  src/terminal_RTC_API.c
)

target_link_libraries(
  terminal_RTC_API
  ${CMAKE_CURRENT_SOURCE_DIR}/../lib/libRTC_API.a
)