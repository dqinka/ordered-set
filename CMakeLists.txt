cmake_minimum_required(VERSION 3.16)

project(CE4703GroupAssignment LANGUAGES C)

add_executable(CE4703GroupAssignment main.c
    doubleLinkedList.c
    orderedIntSet.c
    doubleLinkedList.h
    orderedIntSet.h)

include(GNUInstallDirs)
install(TARGETS CE4703GroupAssignment
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
