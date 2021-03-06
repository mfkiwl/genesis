# Copyright (C) Anthony Arnold 2015
#
# This file is part of Genesis.
#
# Genesis is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Genesis is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Genesis. If not, see <http://www.gnu.org/licenses/>.
#
cmake_minimum_required (VERSION 2.8)
project (genesis C CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)


option(MAKE_GENESIS "Make the genesis application" ON)
option(MAKE_GENESIS_PING "Make the genesis_ping application" ON)

if (MAKE_GENESIS)
  find_package(GFlags)

  if (NOT GFlags_FOUND)
    message (FATAL_ERROR "GFlags is required")
  endif (NOT GFlags_FOUND)
endif (MAKE_GENESIS)

# Find Boost
set (BOOST_COMPONENTS system)
if (MAKE_GENESIS)
  set(BOOST_COMPONENTS ${BOOST_COMPONENTS} thread date_time log filesystem serialization regex)
endif (MAKE_GENESIS)
find_package(Boost COMPONENTS ${BOOST_COMPONENTS} REQUIRED)

# Find threads
find_package (Threads)

# Compiler flags
set (MY_CXX_FLAGS_DEBUG "-DGENESIS_DEBUG")

if(CMAKE_COMPILER_IS_GNUCXX AND NOT WIN32)
  set(MY_CXX_FLAGS "${MY_CXX_FLAGS} -Wall -Wextra -std=c++11")
  set(MY_CXX_FLAGS_RELEASE "${MY_CXX_FLAGS_RELEASE} -Wno-unused")
endif(CMAKE_COMPILER_IS_GNUCXX AND NOT WIN32)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(MY_CXX_FLAGS "${MY_CXX_FLAGS} -stdlib=libc++ -std=c++11")
  set(MY_CXX_FLAGS_RELEASE "${MY_CXX_FLAGS_RELEASE} -Wno-unused-private-field")
endif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MY_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${MY_CXX_FLAGS_RELEASE}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${MY_CXX_FLAGS_DEBUG}")

add_subdirectory (src)
