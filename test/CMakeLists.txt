add_executable(code_test code_test.cpp)
target_link_libraries(code_test PRIVATE GTest::gtest_main code)
include(GoogleTest)
gtest_discover_tests(code_test)