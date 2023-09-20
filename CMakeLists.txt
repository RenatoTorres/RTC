cmake_minimum_required(VERSION 3.14)
project(RTC_API)

set(SOURCES
    src/RTC_API.c
)

# Create the static library target
add_library(RTC_API STATIC ${SOURCES})

# Specify the output directory for the static library
set_target_properties(RTC_API PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib
)

