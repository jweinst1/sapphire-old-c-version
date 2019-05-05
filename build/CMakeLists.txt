# This cmake is responsible for installing cmake config and other version
# files.

# This sets the package specific versioning
set(LIBSAPPHIRE_MAJOR_VERSION 1)
set(LIBSAPPHIRE_MINOR_VERSION 0)
set(LIBSAPPHIRE_PATCH_VERSION 0)

# This allows easy creation of the directories within /usr/local or another install
# prefix
set(LIBSAPPHIRE_NAMED_VERSION libsapphire-${LIBSAPPHIRE_MAJOR_VERSION}.${LIBSAPPHIRE_MINOR_VERSION})
set(LIBSAPPHIRE_NAMED_VERSION ${LIBSAPPHIRE_NAMED_VERSION} PARENT_SCOPE)
# For the config header
set(LIBSAPPHIRE_AUTHOR "Joshua Weinstein")
string(TIMESTAMP LIBSAPPHIRE_BUILD_TIME)

file(READ ${PROJECT_SOURCE_DIR}/LICENSE.txt LIBSAPPHIRE_LICENSE)

# These statements will create the directories needed for installs
install(DIRECTORY DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${LIBSAPPHIRE_NAMED_VERSION})
install(DIRECTORY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/${LIBSAPPHIRE_NAMED_VERSION})

# This tracks the name of the in files used to generate the package cmake files
set(LIBSAPPHIRE_CONFIG_FILE libsapphire-config.cmake.in)
set(LIBSAPPHIRE_CONFIG_VERSION_FILE libsapphire-config-version.cmake.in)
set(LIBSAPPHIRE_CONFIG_HEADER_FILE libsapphire-config.h.in)

# The configure_file statements will exchange the variables for the values in this cmake file.
configure_file(${LIBSAPPHIRE_CONFIG_FILE} libsapphire-config.cmake @ONLY)
configure_file(${LIBSAPPHIRE_CONFIG_VERSION_FILE} libsapphire-config-version.cmake @ONLY)
configure_file(${LIBSAPPHIRE_CONFIG_HEADER_FILE} libsapphire-config.h @ONLY)

# Installs to the output locations so they can be found with find_package()
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libsapphire-config-version.cmake DESTINATION include/${LIBSAPPHIRE_NAMED_VERSION})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libsapphire-config.cmake DESTINATION lib/${LIBSAPPHIRE_NAMED_VERSION})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libsapphire-config.h DESTINATION include/${LIBSAPPHIRE_NAMED_VERSION})
