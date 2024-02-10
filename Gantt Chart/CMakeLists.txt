cmake_minimum_required(VERSION 3.24)
project(GanttChar C)

set(CMAKE_C_STANDARD 99)

##add_executable(GantChar main.c inputAndDisplay.c ../../../../../BCassignment-2/inputAndDisplay.c ../../../../../BCassignment-2/main.c ../../../../../BCassignment-2/criticalPath.c criticalPath.c)
#
#add_executable(GantChar
#        /Users/cianboyle/Documents/BCassignment-2/main.c
#        /Users/cianboyle/Documents/BCassignment-2/inputAndDisplay.c
#        /Users/cianboyle/Documents/BCassignment-2/criticalPath.c
#        )

# Specify the source files
set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/main.c
        ${CMAKE_CURRENT_SOURCE_DIR}/inputAndDisplay.c
        ${CMAKE_CURRENT_SOURCE_DIR}/criticalPath.c
        )

# Add the executable target
add_executable(GantChar ${SOURCES})
