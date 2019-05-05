cmake_minimum_required(VERSION 3.5)

project(sapphire)

# Sets the prefix for installations
set(CMAKE_INSTALL_PREFIX /usr/local)

add_subdirectory(build)
message("Building with version: ${LIBSAPPHIRE_NAMED_VERSION}")

add_subdirectory(include)

option(SAPPHIRE_WITH_TESTING "Builds libsapphire with testing." ON)

if(SAPPHIRE_WITH_TESTING)
    enable_testing()
endif()

add_subdirectory(utils)
add_subdirectory(core)
