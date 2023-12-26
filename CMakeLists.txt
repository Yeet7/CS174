cmake_minimum_required(VERSION 3.27)
project(cpp_fun)

set(CMAKE_CXX_STANDARD 14)

include_directories(usr/include
        lib)

find_package(SFML 2.5 COMPONENTS graphics audio system window network REQUIRED)

add_executable(cpp_fun
        lib/SFML/Debug/sfml-audio-s-d.pdb
        lib/SFML/Debug/sfml-audio-s.pdb
        lib/SFML/Debug/sfml-audio.pdb
        lib/SFML/Debug/sfml-graphics-s-d.pdb
        lib/SFML/Debug/sfml-graphics-s.pdb
        lib/SFML/Debug/sfml-graphics.pdb
        lib/SFML/Debug/sfml-main-d.pdb
        lib/SFML/Debug/sfml-main-s.pdb
        lib/SFML/Debug/sfml-network-s-d.pdb
        lib/SFML/Debug/sfml-network-s.pdb
        lib/SFML/Debug/sfml-network.pdb
        lib/SFML/Debug/sfml-system-s-d.pdb
        lib/SFML/Debug/sfml-system-s.pdb
        lib/SFML/Debug/sfml-system.pdb
        lib/SFML/Debug/sfml-window-s-d.pdb
        lib/SFML/Debug/sfml-window-s.pdb
        lib/SFML/Debug/sfml-window.pdb
        lib/SFML/SFML/SFMLConfig.cmake
        lib/SFML/SFML/SFMLConfigDependencies.cmake
        lib/SFML/SFML/SFMLConfigVersion.cmake
        lib/SFML/SFML/SFMLSharedTargets-debug.cmake
        lib/SFML/SFML/SFMLSharedTargets-release.cmake
        lib/SFML/SFML/SFMLSharedTargets.cmake
        lib/SFML/SFML/SFMLStaticTargets-debug.cmake
        lib/SFML/SFML/SFMLStaticTargets-release.cmake
        lib/SFML/SFML/SFMLStaticTargets.cmake
        lib/SFML/flac.lib
        lib/SFML/freetype.lib
        lib/SFML/ogg.lib
        lib/SFML/openal32.lib
        lib/SFML/sfml-audio-d.lib
        lib/SFML/sfml-audio-s-d.lib
        lib/SFML/sfml-audio-s.lib
        lib/SFML/sfml-audio.lib
        lib/SFML/sfml-graphics-d.lib
        lib/SFML/sfml-graphics-s-d.lib
        lib/SFML/sfml-graphics-s.lib
        lib/SFML/sfml-graphics.lib
        lib/SFML/sfml-main-d.lib
        lib/SFML/sfml-main.lib
        lib/SFML/sfml-network-d.lib
        lib/SFML/sfml-network-s-d.lib
        lib/SFML/sfml-network-s.lib
        lib/SFML/sfml-network.lib
        lib/SFML/sfml-system-d.lib
        lib/SFML/sfml-system-s-d.lib
        lib/SFML/sfml-system-s.lib
        lib/SFML/sfml-system.lib
        lib/SFML/sfml-window-d.lib
        lib/SFML/sfml-window-s-d.lib
        lib/SFML/sfml-window-s.lib
        lib/SFML/sfml-window.lib
        lib/SFML/vorbis.lib
        lib/SFML/vorbisenc.lib
        lib/SFML/vorbisfile.lib
        test/main.cpp)

target_link_libraries(cpp_fun sfml-graphics sfml-audio sfml-window sfml-network sfml-system)