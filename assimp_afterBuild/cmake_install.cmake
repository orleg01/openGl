# Install script for directory: C:/Users/Orleg/Desktop/openGlSelfLearning/assimp-3.1.1

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Assimp")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "libassimp3.1.1-dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Orleg/Desktop/openGlSelfLearning/assimp_afterBuild/assimp.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "libassimp3.1.1-dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/assimp-3.1" TYPE FILE FILES
    "C:/Users/Orleg/Desktop/openGlSelfLearning/assimp_afterBuild/assimp-config.cmake"
    "C:/Users/Orleg/Desktop/openGlSelfLearning/assimp_afterBuild/assimp-config-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/Orleg/Desktop/openGlSelfLearning/assimp_afterBuild/contrib/zlib/cmake_install.cmake")
  include("C:/Users/Orleg/Desktop/openGlSelfLearning/assimp_afterBuild/code/cmake_install.cmake")
  include("C:/Users/Orleg/Desktop/openGlSelfLearning/assimp_afterBuild/tools/assimp_view/cmake_install.cmake")
  include("C:/Users/Orleg/Desktop/openGlSelfLearning/assimp_afterBuild/tools/assimp_cmd/cmake_install.cmake")
  include("C:/Users/Orleg/Desktop/openGlSelfLearning/assimp_afterBuild/test/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/Users/Orleg/Desktop/openGlSelfLearning/assimp_afterBuild/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
