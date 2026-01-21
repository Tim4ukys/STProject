project("arithmetic" C)

add_compile_options(-Zi)

file(GLOB SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
file(GLOB PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_executable(${PROJECT_NAME} ${SOURCE})
