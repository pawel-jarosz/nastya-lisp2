add_executable(compute_primitives compute_primitives.cpp)
target_link_libraries(compute_primitives nastya GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(compute_primitives)
