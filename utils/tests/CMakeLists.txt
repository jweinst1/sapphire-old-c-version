# Cmake file for the utils tests

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(test_sapphiremem test_sapphiremem.c)
# Turns on debugger mode.
target_compile_definitions(test_sapphiremem PRIVATE -DSAPPHIRE_MEMORY_DEBUG_MODE)
add_test(test_sapphiremem test_sapphiremem)

add_executable(test_sapphireio test_sapphireio.c)
target_link_libraries(test_sapphireio sapphireutils)
add_test(test_sapphireio test_sapphireio)
