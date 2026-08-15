add_library(nastya STATIC
        machine.cpp
        object_type.cpp)
target_include_directories(nastya PUBLIC ${NASTYA_INCLUDE_DIR})

add_executable(nastya_repl main.cpp)
target_include_directories(nastya_repl PRIVATE ${NASTYA_INCLUDE_DIR})
target_link_libraries(nastya_repl PRIVATE nastya)