cmake_minimum_required(VERSION 3.5)

project(data_structure)

add_subdirectory(doubly_linked_list)
add_subdirectory(sequence_list)
add_subdirectory(stack)
add_subdirectory(string)
add_subdirectory(haffman_tree)
add_subdirectory(binary_tree)
add_subdirectory(graph)
add_subdirectory(io)


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

#add_subdirectory(third-party/google-test)

#enable_testing()
#add_subdirectory(tests)
