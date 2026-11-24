cmake_minimum_required(VERSION 3.16)

project(CE4703GroupAssignment LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(CE4703GroupAssignment main.c
    menu.c
    menu.h
    doubleLinkedList.c
    orderedIntSet.c
    doubleLinkedList.h
    orderedIntSet.h)

# Copy textInput.txt next to the executable so fopen("textInput.txt") finds it
configure_file(${CMAKE_SOURCE_DIR}/textInput.txt
               ${CMAKE_BINARY_DIR}/textInput.txt COPYONLY)

include(GNUInstallDirs)

install(TARGETS CE4703GroupAssignment
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Double linked list unit testing
add_executable(testDoubleLinkedList
    testDoubleLinkedList.c
    doubleLinkedList.c
)


# Person 4 function and menu regression tests (existing project sources).
enable_testing()
add_executable(testPerson4
    tests/testPerson4.c
    orderedIntSet.c
    doubleLinkedList.c
    menu.c
)
target_include_directories(testPerson4 PRIVATE ${CMAKE_SOURCE_DIR})
add_test(NAME Person4 COMMAND testPerson4)
add_test(NAME DoubleLinkedList COMMAND testDoubleLinkedList)
