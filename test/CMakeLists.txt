include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

set(test_src
    AllTests.cpp
    tests.cpp)

add_executable(${PROJECT_NAME}.test ${test_src})

target_include_directories(${PROJECT_NAME}.test PRIVATE
    ${${PROJECT_NAME}_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME}.test PRIVATE
    ${PROJECT_NAME}
    GTest::gtest
    GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}.test)