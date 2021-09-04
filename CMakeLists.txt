cmake_minimum_required(VERSION 3.13.0)
project(pkm)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(nfs)

file(GLOB_RECURSE hpp "include/*.hpp")
file(GLOB_RECURSE cpp "src/*.cpp")

# Link library

add_library(
	pkm STATIC
	${hpp}
	${cpp}
	CMakeLists.txt
)

target_include_directories(pkm PUBLIC include)
target_include_directories(pkm PUBLIC nfs)
target_link_libraries(pkm PUBLIC nfs)

if(MSVC)

	add_compile_options(
		"$<$<CONFIG:DEBUG>:/MDd>"
		"$<$<CONFIG:RELEASE>:/MD>"
	)

    target_compile_options(pkm PRIVATE /W4 /WX /MP /wd26812 /wd4201 /EHsc /GR)
else()
    target_compile_options(pkm PRIVATE -Wall -fms-extensions -Wextra -Werror)
endif()