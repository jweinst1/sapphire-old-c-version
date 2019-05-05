# Cmake file for the utils library

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SAPPHIRE_UTILS_SOURCES
   sapphire-io.c
)

add_library(sapphireutils STATIC "${SAPPHIRE_UTILS_SOURCES}")

add_subdirectory(tests)
