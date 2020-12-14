get_filename_component(LIB_INCLUDE_PATH ".." ABSOLUTE)
get_filename_component(LIB_PATH "." ABSOLUTE)

find_package(OpenMP REQUIRED)
set(MAIN_LIB_DEPENDENCY OpenMP::OpenMP_CXX)

file(GLOB_RECURSE LIB_CXX_SOURCES ${LIB_PATH}/*.cpp)
file(GLOB_RECURSE LIB_HEADERS ${LIB_PATH}/*.h)
add_library(${MAIN_LIB_NAME} STATIC ${LIB_CXX_SOURCES} ${LIB_HEADERS})
target_include_directories(${MAIN_LIB_NAME} PUBLIC ${LIB_INCLUDE_PATH})

target_link_libraries(${MAIN_LIB_NAME} PRIVATE ${MAIN_LIB_DEPENDENCY})
