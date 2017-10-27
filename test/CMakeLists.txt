add_definitions(-std=c++14)

include_directories( "../src" "googletest/include")

find_library(GTEST
    NAMES "gtest"
    PATHS "googletest/build"
    NO_DEFAULT_PATH
)

add_executable(chat_test main.cpp)

target_link_libraries(chat_test ${GTEST} pthread)
