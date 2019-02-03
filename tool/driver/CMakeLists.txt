add_executable(lox main.c)

target_link_libraries(clox)

target_link_libraries(lox LINK_PUBLIC clox)