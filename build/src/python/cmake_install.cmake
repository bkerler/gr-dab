# Install script for directory: /home/bjk/gnuradio/gr-dab/src/python

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages/gnuradio/dab" TYPE FILE FILES
    "/home/bjk/gnuradio/gr-dab/src/python/__init__.py"
    "/home/bjk/gnuradio/gr-dab/src/python/fic.py"
    "/home/bjk/gnuradio/gr-dab/src/python/ofdm.py"
    "/home/bjk/gnuradio/gr-dab/src/python/ofdm_sync_dab.py"
    "/home/bjk/gnuradio/gr-dab/src/python/ofdm_sync_dab2.py"
    "/home/bjk/gnuradio/gr-dab/src/python/detect_null.py"
    "/home/bjk/gnuradio/gr-dab/src/python/parameters.py"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages/gnuradio/dab" TYPE FILE FILES
    "/home/bjk/gnuradio/gr-dab/build/src/python/__init__.pyc"
    "/home/bjk/gnuradio/gr-dab/build/src/python/fic.pyc"
    "/home/bjk/gnuradio/gr-dab/build/src/python/ofdm.pyc"
    "/home/bjk/gnuradio/gr-dab/build/src/python/ofdm_sync_dab.pyc"
    "/home/bjk/gnuradio/gr-dab/build/src/python/ofdm_sync_dab2.pyc"
    "/home/bjk/gnuradio/gr-dab/build/src/python/detect_null.pyc"
    "/home/bjk/gnuradio/gr-dab/build/src/python/parameters.pyc"
    "/home/bjk/gnuradio/gr-dab/build/src/python/__init__.pyo"
    "/home/bjk/gnuradio/gr-dab/build/src/python/fic.pyo"
    "/home/bjk/gnuradio/gr-dab/build/src/python/ofdm.pyo"
    "/home/bjk/gnuradio/gr-dab/build/src/python/ofdm_sync_dab.pyo"
    "/home/bjk/gnuradio/gr-dab/build/src/python/ofdm_sync_dab2.pyo"
    "/home/bjk/gnuradio/gr-dab/build/src/python/detect_null.pyo"
    "/home/bjk/gnuradio/gr-dab/build/src/python/parameters.pyo"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

