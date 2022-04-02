add_library(array_tools STATIC src/array_tools.c)
target_include_directories(array_tools PUBLIC include)

add_library(parallel SHARED src/parallel_processing.c)
target_include_directories(parallel PUBLIC include)
target_link_libraries(parallel PUBLIC array_tools consistent)

add_library(consistent STATIC src/serial_processing.c)
target_include_directories(consistent PUBLIC include)
target_link_libraries(consistent PUBLIC array_tools)



