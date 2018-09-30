cmake_minimum_required(VERSION 3.2)
project(NexMotion_API)
# The project version number.
set(VERSION_MAJOR   1   CACHE STRING "Project major version number.")
set(VERSION_MINOR   4   CACHE STRING "Project minor version number.")
set(VERSION_PATCH   0   CACHE STRING "Project patch version number.")

#set(CMAKE_CXX_STANDARD 11)
#set(CXX_FLAGS "-g -Wall -Wextra")
#set(CMAKE_CXX_FLAGS ${CXX_FLAGS})


# Build Doxygen Document
find_package(Doxygen)
if(DOXYGEN_FOUND)
    message("You Have Doxygen!\n")
    set(BUILD_DOC_DIR ${CMAKE_SOURCE_DIR}/build/docs)
    if(NOT EXISTS ${BUILD_DOC_DIR})
        file(MAKE_DIRECTORY ${BUILD_DOC_DIR})
    endif()

    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    message("Doxygen build started")
    add_custom_target(Doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)

    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs/html
            DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/docs)
else(DOXYGEN_FOUND)
    message("No Doxygen, can't build Doc!\n")
endif(DOXYGEN_FOUND)
