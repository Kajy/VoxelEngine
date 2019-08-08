# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required(VERSION 3.8)

project("Ucraft")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_STANDARD 14)

function(clone)
    execute_process(COMMAND git clone --recursive https://github.com/ManuelTrambert/nanogui.git ${CMAKE_CURRENT_SOURCE_DIR}/uSrc/Includes/nanogui)
endfunction()

function(afterEvent)
    ## "sample" is the name of the executable
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/uSrc/Includes/nanogui)

    if (NOT UCRAFT_EIGEN3_INCLUDE_DIR)
        # Grab or find the Eigen3 include directory.
        find_package(Eigen3 QUIET)
        if (EIGEN3_INCLUDE_DIR)
            set(UCRAFT_EIGEN3_INCLUDE_DIR ${EIGEN3_INCLUDE_DIR})
        else ()
            # use the internal NanoGUI copy of Eigen
            set(UCRAFT_EIGEN3_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/uSrc/Includes/ext/eigen)
        endif ()
    endif ()
    message(STATUS "Using Eigen3 from directory: ${UCRAFT_EIGEN3_INCLUDE_DIR}")

    if (NOT WIN32)
        find_package(Boost 1.65 COMPONENTS system filesystem REQUIRED)
        set(CMAKE_MODULE_PATH /usr/local/lib/cmake /usr/local/lib/x86_64-linux-gnu/cmake)
        set(CMAKE_PREFIX_PATH /usr/local/lib/cmake/glfw)
    endif (NOT WIN32)

    find_package(OpenGL REQUIRED)
    if (WIN32)
        include_directories(${Boost_INCLUDE_DIR} "uSrc/Includes/nanogui/include" "uSrc/Includes/nanogui/ext" "uSrc/Includes/nanogui/ext/eigen" "C:/Program Files/OpenSSL-Win64/include" "uSrc/Includes/pluginEditor" "Libraries/libwebsockets/include" "uSrc/Includes/nanogui/ext/glad/include/glad" "uSrc/Includes/nanogui/ext/glad/include/KHR" "uSrc/Includes/nanogui/ext/nanovg/src" "uSrc/Includes/nanogui/ext/pybind11/include/pybind11" "Libraries/GLFW/include" "Libraries/json-develop/include" "Libraries/libcurl/include" "Libraries/glm" "Libraries/glew/include" "Libraries/DevIL/include" "Libraries/ziplib/Source" "uSrc/Includes" "uSrc/Includes/GUI" "uSrc/Includes/rapidxml-1.13" "uSrc/Includes/protocol" "C:/local/boost_1_67_0")
        link_directories("Libraries/glew/lib/Release/x64" "Libraries/libwebsockets/lib" "Libraries/GLFW/lib-vc2015" "Libraries/DevIL/lib/x64/Release" "C:/local/boost_1_67_0/lib64-msvc-14.1" "Libraries/ziplib/Bin/x86/Debug")
    else (WIN32)
        include_directories(${Boost_INCLUDE_DIR} ${UCRAFT_EIGEN3_INCLUDE_DIR} "uSrc/Includes/nanogui/include" "uSrc/Includes/pluginEditor"  "uSrc/Includes/nanogui/ext" "uSrc/Includes/nanogui/ext/eigen" "uSrc/Includes/nanogui/ext/glad/include/glad" "uSrc/Includes/nanogui/ext/glad/include/KHR" "uSrc/Includes/nanogui/ext/nanovg/src" "/usr/local/include" "/opt/X11/include" "uSrc/Includes" "uSrc/Includes/GUI" "uSrc/Includes/rapidxml-1.13" "/usr/local/Cellar/boost/1.68.0/include/boost" "uSrc/Includes/protocol" "/usr/local/Cellar/boost/1.67.0_1/include/boost/asio" "/usr/local/Cellar/boost/1.67.0_1/include/boost/asio/ip" "Libraries/json-develop/include" "Libraries/libcurl/include" "Libraries/ziplib/Source")
        link_directories("/usr/local/lib" "/usr/local/Cellar/boost/1.68.0")
    endif (WIN32)

    if(APPLE)
        include_directories("/usr/local/Cellar/openssl/1.0.2p/include/")
        set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl")
    endif()
    find_package(OpenSSL REQUIRED)
 
    set(SOURCE_FILES "uSrc/Sources/Main.cpp"
            "uSrc/Sources/Cube.cpp"
            "uSrc/Sources/CubeFactory.cpp"
            "uSrc/Sources/CubesContainer.cpp"
            "uSrc/Sources/Event.cpp"
            "uSrc/Sources/PlayerInfos.cpp"
            "uSrc/Sources/Renderer.cpp"
            "uSrc/Sources/Texture.cpp"
            "uSrc/Sources/UOptions.cpp"
            "uSrc/Sources/Viewer.cpp"
            "uSrc/Sources/UViewer.cpp"
            "uSrc/Sources/USection.cpp"
            "uSrc/Sources/Window.cpp"
            "uSrc/Sources/World.cpp"
            "uSrc/Sources/Network.cpp"
			"uSrc/Sources/protocol/PkgHandShakeIn.cpp"
			"uSrc/Sources/PluginSocket.cpp"
			"uSrc/Sources/WebSocketServer.cpp"
            "uSrc/Sources/protocol/CMDHandlerIn.cpp"
            "uSrc/Sources/protocol/CMDHandlerOut.cpp"
            "uSrc/Sources/protocol/PkgString.cpp"
            "uSrc/Sources/protocol/PkgString.cpp"
            "uSrc/Sources/protocol/PkgHandShakeIn.cpp"
            "uSrc/Sources/protocol/UCurl.cpp"
            "uSrc/Sources/protocol/UZipPack.cpp"
            "uSrc/Sources/GUI/GUI.cpp"
            "uSrc/Sources/GUI/Inventory.cpp"
            "uSrc/Sources/GUI/GuiText.cpp"
            "uSrc/Sources/GUI/History.cpp"
            "uSrc/Sources/GUI/ButtonGUI.cpp"
            "uSrc/Sources/GUI/InputTextGUI.cpp"
            "uSrc/Sources/GUI/WindowGUI.cpp"
            "uSrc/Sources/GUI/Slider.cpp"
            "uSrc/Sources/GUI/PopupButtonGUI.cpp"
            "uSrc/Sources/UEntity.cpp"
            "uSrc/Sources/AABBBox.cpp"
            "uSrc/Sources/UAtlas.cpp")


    ##set_property(TARGET nanogui PROPERTY FOLDER "dependencies")
    add_executable("Ucraft" ${SOURCE_FILES})
    target_link_libraries("Ucraft"
            ${GLFW3_LIBRARY}
            ${OPENSSL_LIBRARIES}
            ${OPENGL_LIBRARIES}
            ${GLEW_LIBRARY} ${COCOA_LIBRARY} ${COREVID_LIBRARY} ${IOKIT_LIBRARY} ${EIGEN3_INCLUDE_DIR} ${Boost_FILESYSTEM_LIBRARY}
            ${Boost_SYSTEM_LIBRARY} nanogui ${NANOGUI_EXTRA_LIBS})
    if (WIN32)
        target_link_libraries("Ucraft"
                ${OPENGL_LIBRARIES} ${OPENSSL_LIBRARIES} ${LIB_WEBSOCKETS_LIBRARIES} websockets glfw3 glew32s glu32 opengl32 DevIL ILU ILUT
				"${CMAKE_CURRENT_SOURCE_DIR}/Libraries/ziplib/Bin/x64/Release/ZipLib.lib"
				"${CMAKE_CURRENT_SOURCE_DIR}/Libraries/ziplib/Bin/x64/Release/zlib.lib"
				"${CMAKE_CURRENT_SOURCE_DIR}/Libraries/ziplib/Bin/x64/Release/lzma.lib"
				"${CMAKE_CURRENT_SOURCE_DIR}/Libraries/ziplib/Bin/x64/Release/bzip2.lib"
				"${CMAKE_CURRENT_SOURCE_DIR}/Libraries/libcurl/lib/libcurl.dll.a")
    else (WIN32)
        target_include_directories("Ucraft" INTERFACE ${OPENSSL_INCLUDE_DIR} ${LIB_WEBSOCKETS_INCLUDE_DIRS})
        target_link_libraries("Ucraft"
                ${OPENGL_LIBRARIES} ${LIB_WEBSOCKETS_LIBRARIES} ${OPENSSL_LIBRARIES} websockets GLEW IL ILU ILUT 
                "${CMAKE_CURRENT_SOURCE_DIR}/Libraries/ziplib/Bin/libzip.so"
                "${CMAKE_CURRENT_SOURCE_DIR}/Libraries/libcurl/lib/libcurl.dll.a")
    endif (WIN32)
    if (APPLE)
        target_link_libraries("Ucraft"
                "${CMAKE_CURRENT_SOURCE_DIR}/Libraries/libcurl/lib/libcurl.dylib")
    endif (APPLE)
endfunction()

clone()
afterEvent()
