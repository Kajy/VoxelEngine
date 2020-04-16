# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BINARY_7Z "")
set(CPACK_BINARY_BUNDLE "")
set(CPACK_BINARY_CYGWIN "")
set(CPACK_BINARY_DEB "")
set(CPACK_BINARY_DRAGNDROP "")
set(CPACK_BINARY_FREEBSD "")
set(CPACK_BINARY_IFW "")
set(CPACK_BINARY_NSIS "")
set(CPACK_BINARY_OSXX11 "")
set(CPACK_BINARY_PACKAGEMAKER "")
set(CPACK_BINARY_PRODUCTBUILD "")
set(CPACK_BINARY_RPM "")
set(CPACK_BINARY_STGZ "")
set(CPACK_BINARY_TBZ2 "")
set(CPACK_BINARY_TGZ "")
set(CPACK_BINARY_TXZ "")
set(CPACK_BINARY_TZ "")
set(CPACK_BINARY_WIX "")
set(CPACK_BINARY_ZIP "")
set(CPACK_BUILD_SOURCE_DIRS "C:/Users/Admin/Documents/ucraft-client/Libraries/libwebsockets;C:/Users/Admin/CMakeBuilds/3d816f3b-2d14-3436-a6c0-8de57df3fd21/build/x64-Release")
set(CPACK_CMAKE_GENERATOR "Ninja")
set(CPACK_COMPONENTS_ALL "dev;dev_headers;examples;libraries")
set(CPACK_COMPONENT_DEV_DISPLAY_NAME "Development files")
set(CPACK_COMPONENT_EXAMPLES_DISPLAY_NAME "Example files")
set(CPACK_COMPONENT_LIBRARIES_DISPLAY_NAME "Libraries")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_GENERATOR "TGZ")
set(CPACK_IGNORE_FILES "$(CPACK_SOURCE_IGNORE_FILES);/.git/;/build/;\\.tgz$;\\.tar\\.gz$")
set(CPACK_INSTALLED_DIRECTORIES "C:/Users/Admin/Documents/ucraft-client/Libraries/libwebsockets;/")
set(CPACK_INSTALL_CMAKE_PROJECTS "")
set(CPACK_INSTALL_PREFIX "C:/Users/Admin/CMakeBuilds/3d816f3b-2d14-3436-a6c0-8de57df3fd21/install/x64-Release")
set(CPACK_MODULE_PATH "C:/Users/Admin/Documents/ucraft-client/Libraries/libwebsockets/cmake/")
set(CPACK_NSIS_DISPLAY_NAME "libwebsockets 3.1.99")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES64")
set(CPACK_NSIS_PACKAGE_NAME "libwebsockets 3.1.99")
set(CPACK_OUTPUT_CONFIG_FILE "C:/Users/Admin/CMakeBuilds/3d816f3b-2d14-3436-a6c0-8de57df3fd21/build/x64-Release/CPackConfig.cmake")
set(CPACK_PACKAGE_CONTACT "andy@warmcat.com")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION_FILE "C:/Program Files (x86)/Microsoft Visual Studio/2017/Professional/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-3.11/Templates/CPack.GenericDescription.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "libwebsockets ")
set(CPACK_PACKAGE_FILE_NAME "libwebsockets-3.1.99")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "libwebsockets 3.1.99")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "libwebsockets 3.1.99")
set(CPACK_PACKAGE_NAME "libwebsockets")
set(CPACK_PACKAGE_RELEASE "1")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "andy@warmcat.com")
set(CPACK_PACKAGE_VERSION "3.1.99")
set(CPACK_PACKAGE_VERSION_MAJOR "3")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "99")
set(CPACK_RESOURCE_FILE_LICENSE "C:/Program Files (x86)/Microsoft Visual Studio/2017/Professional/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-3.11/Templates/CPack.GenericLicense.txt")
set(CPACK_RESOURCE_FILE_README "C:/Program Files (x86)/Microsoft Visual Studio/2017/Professional/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-3.11/Templates/CPack.GenericDescription.txt")
set(CPACK_RESOURCE_FILE_WELCOME "C:/Program Files (x86)/Microsoft Visual Studio/2017/Professional/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-3.11/Templates/CPack.GenericWelcome.txt")
set(CPACK_RPM_PACKAGE_SOURCES "ON")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_7Z "")
set(CPACK_SOURCE_CYGWIN "")
set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_SOURCE_IGNORE_FILES "$(CPACK_SOURCE_IGNORE_FILES);/.git/;/build/;\\.tgz$;\\.tar\\.gz$")
set(CPACK_SOURCE_INSTALLED_DIRECTORIES "C:/Users/Admin/Documents/ucraft-client/Libraries/libwebsockets;/")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "C:/Users/Admin/CMakeBuilds/3d816f3b-2d14-3436-a6c0-8de57df3fd21/build/x64-Release/CPackSourceConfig.cmake")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "libwebsockets-3.1.99")
set(CPACK_SOURCE_RPM "")
set(CPACK_SOURCE_TBZ2 "")
set(CPACK_SOURCE_TGZ "")
set(CPACK_SOURCE_TOPLEVEL_TAG "win64-Source")
set(CPACK_SOURCE_TXZ "")
set(CPACK_SOURCE_TZ "")
set(CPACK_SOURCE_ZIP "")
set(CPACK_STRIP_FILES "")
set(CPACK_SYSTEM_NAME "win64")
set(CPACK_TOPLEVEL_TAG "win64-Source")
set(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "C:/Users/Admin/CMakeBuilds/3d816f3b-2d14-3436-a6c0-8de57df3fd21/build/x64-Release/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()