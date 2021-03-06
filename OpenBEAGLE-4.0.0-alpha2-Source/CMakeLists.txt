# CMakeLists
# Configuration for generating build systen for Open BEAGLE
# Copyright (C) 2009
# by Christian Gagne <christian.gagne@gel.ulaval.ca>
#
# Date : 17/07/2009

# Minimum cmake version
cmake_minimum_required(VERSION 2.6)

if(COMMAND cmake_policy)
		   cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

# Set project variables
project(OpenBEAGLE C CXX)
set(BEAGLE_PACKAGE OpenBEAGLE)
set(BEAGLE_VERSION 4.0.0-alpha2)
if(APPLE)
	option(BEAGLE_CREATE_DMG "Do you want to create a pkg package for OpenBeagle?" OFF)
elseif(WIN32)
	option(BEAGLE_CREATE_WIN32_SETUP "Do you want to create a setup program for OpenBeagle (NSIS needed)?" OFF)
elseif(UNIX)
	option(BEAGLE_CREATE_UNIX_BIN "Do you want to create Unix universal binaries files for OpenBeagle?" OFF)
	option(BEAGLE_CREATE_DEB "Do you want to create a DEB package for OpenBeagle?" OFF)
	option(BEAGLE_CREATE_RPM "Do you want to create a RPM package for OpenBeagle (rpmbuild needed)?" OFF)
endif(APPLE)

# Define whether we build static or shared libs
if(NOT DEFINED LIBRARY_TYPE)
	if(NOT MSVC)
		message(STATUS "++ Building shared library (default)")
		option(BUILD_STATIC_LIB "Build static library instead of shared one?" OFF)
	else(NOT MSVC)
		message(STATUS "++ Building static library (default on Microsoft Visual C++)")
		option(BUILD_STATIC_LIB "Build static library instead of shared one?" ON)
	endif(NOT MSVC)
elseif(LIBRARY_TYPE MATCHES "static")
	message(STATUS "++ Building static library")
	option(BUILD_STATIC_LIB "Build static library instead of shared one?" ON)
else(NOT DEFINED LIBRARY_TYPE)
	message(STATUS "++ Building dynamic library")
	option(BUILD_STATIC_LIB "Build static library instead of shared one?" OFF)
endif(NOT DEFINED LIBRARY_TYPE)


if(BUILD_STATIC_LIB)
	set(BEAGLE_LIBRARY_TYPE "STATIC")
else(BUILD_STATIC_LIB)
	set(BEAGLE_LIBRARY_TYPE "SHARED")
endif(BUILD_STATIC_LIB)

if(NOT DEFINED BEAGLE_BUILD_EXAMPLES)
	option(BEAGLE_BUILD_EXAMPLES "Build OpenBeagle examples?" ON)
endif(NOT DEFINED BEAGLE_BUILD_EXAMPLES)

message(STATUS "++ Include CMake macros...")

# Files to include for testing
include(CheckIncludeFiles)
include(CheckFunctionExists)
include(CheckSymbolExists)
include(CheckLibraryExists)
include(CheckCXXCompilerFlag)

# Others macros to include
include(CMakeMacros/PerformTest.cmake)
include(CMakeMacros/FindPacc.cmake)
include(CMakeMacros/AllFilesInOne.cmake)
include(CMakeMacros/MoveConfigFiles.cmake)

message(STATUS "++ Begin configuration tests...")

# Check for some headers
check_include_files(inttypes.h BEAGLE_HAVE_INTTYPES_H)
check_include_files(stdint.h   BEAGLE_HAVE_STDINT_H)
check_include_files(stdlib.h   BEAGLE_HAVE_STDLIB_H)
check_include_files(unistd.h   BEAGLE_HAVE_UNISTD_H)

# Check for /dev/urandom
if(EXISTS /dev/urandom)
	set(BEAGLE_HAVE_DEV_URANDOM 1)
endif(EXISTS /dev/urandom)

# Directory and extension used to find test files
if(NOT DEFINED CMAKE_DIR_TEST)
	set(CMAKE_DIR_TEST CMakeTestCode)
endif(NOT DEFINED CMAKE_DIR_TEST)
if(NOT DEFINED CMAKE_TEST_SUFFIX)
	set(CMAKE_TEST_SUFFIX ".cmake.cpp")
endif(NOT DEFINED CMAKE_TEST_SUFFIX)


if(NOT DEFINED BEAGLE_USE_C0x)
	option(BEAGLE_USE_C0x "Use C++0x new headers?" OFF)
endif(NOT DEFINED BEAGLE_USE_C0x)


# Check for built-in bool type
PerformTest(CXX_HAVE_BOOL)
if(CXX_HAVE_BOOL)
	message(STATUS "++ C++ has built-in bool type")
	set(BEAGLE_HAVE_BOOL 1)
endif(CXX_HAVE_BOOL)

# Check for built-in long long type
PerformTest(CXX_HAVE_LONG_LONG)
if(CXX_HAVE_LONG_LONG)
	message(STATUS "++ C++ has built-in long long type")
	set(BEAGLE_HAVE_LONG_LONG 1)
endif(CXX_HAVE_LONG_LONG)


# Check for templates
PerformTest(CXX_HAVE_TEMPLATES)
if(CXX_HAVE_TEMPLATES)
	message(STATUS "++ C++ supports templates")
else(CXX_HAVE_TEMPLATES)
	message(SEND_ERROR "!! Sorry, templates support needed")
endif(CXX_HAVE_TEMPLATES)

# Check for built-in template scoped argument matching
PerformTest(CXX_HAVE_TEMPLATE_SCOPED_ARGUMENT_MATCHING)
if(CXX_HAVE_TEMPLATE_SCOPED_ARGUMENT_MATCHING)
	message(STATUS "++ C++ supports template scoped argument matching")
else(CXX_HAVE_TEMPLATE_SCOPED_ARGUMENT_MATCHING)
	message(SEND_ERROR "!! Sorry, template scoped argument matching support needed")
endif(CXX_HAVE_TEMPLATE_SCOPED_ARGUMENT_MATCHING)

# Check for default template parameters
PerformTest(CXX_HAVE_DEFAULT_TEMPLATE_PARAMETERS)
if(CXX_HAVE_DEFAULT_TEMPLATE_PARAMETERS)
	message(STATUS "++ C++ supports default template parameters")
else(CXX_HAVE_DEFAULT_TEMPLATE_PARAMETERS)
	message(SEND_ERROR "!! Sorry, default template parameters support needed")
endif(CXX_HAVE_DEFAULT_TEMPLATE_PARAMETERS)

# Check for typename
PerformTest(CXX_HAVE_TYPENAME)
if(CXX_HAVE_TYPENAME)
	message(STATUS "++ C++ has typename qualifier")
else(CXX_HAVE_TYPENAME)
	message(SEND_ERROR "!! Sorry, typename qualifier needed")
endif(CXX_HAVE_TYPENAME)

# Check for built-in exception handling
PerformTest(CXX_HAVE_EXCEPTIONS)
if(CXX_HAVE_EXCEPTIONS)
	message(STATUS "++ C++ supports exception handling")
else(CXX_HAVE_EXCEPTIONS)
	message(SEND_ERROR "!! Sorry, support for exception handling needed")
endif(CXX_HAVE_EXCEPTIONS)

# Check for namespaces support
PerformTest(CXX_HAVE_NAMESPACES)
if(CXX_HAVE_NAMESPACES)
	message(STATUS "++ C++ supports namespaces")
else(CXX_HAVE_NAMESPACES)
	message(SEND_ERROR "!! Sorry, namespaces support needed")
endif(CXX_HAVE_NAMESPACES)

# Check for hash_map C++ template
PerformTest(HASHMAP_STD)
PerformTest(HASHMAP_GNUCXX)
PerformTest(HASHMAP_STDEXT)

if(HASHMAP_STD)
	message(STATUS "++ std::hash_map found")
	set(BEAGLE_HAVE_STD_HASHMAP 1)
endif(HASHMAP_STD)
if(HASHMAP_GNUCXX)
	message(STATUS "++ __gnu_cxx::hash_map found")
	set(BEAGLE_HAVE_GNUCXX_HASHMAP false)
	message(STATUS "++ __gnu_cxx::hash_map will not be enabled since some segfault occurs while using it.")
	option(BEAGLE_HAVE_GNUCXX_HASHMAP "Enable __gnu_cxx::hash_map anyway?" OFF)
endif(HASHMAP_GNUCXX)
if(HASHMAP_STDEXT)
	message(STATUS "++ stdext::hash_map found")
	set(BEAGLE_HAVE_STDEXT_HASHMAP 1)
endif(HASHMAP_STDEXT)
if(NOT DEFINED HASHMAP_STD AND NOT DEFINED HASHMAP_GNUCXX AND NOT DEFINED HASHMAP_STDEXT)
	message(STATUS "++ no hash_map found")
endif(NOT DEFINED HASHMAP_STD AND NOT DEFINED HASHMAP_GNUCXX AND NOT DEFINED HASHMAP_STDEXT)

# Check for hash_set C++ template
PerformTest(HASHSET_STD)
PerformTest(HASHSET_GNUCXX)
PerformTest(HASHSET_STDEXT)
if(HASHSET_STD)
	message(STATUS "++ std::hash_set found")
	set(BEAGLE_HAVE_STD_HASHSET 1)
endif(HASHSET_STD)
if(HASHSET_GNUCXX)
	message(STATUS "++ __gnu_cxx::hash_set found")
	set(BEAGLE_HAVE_GNUCXX_HASHSET false)
	message(STATUS "++ __gnu_cxx::hash_set will not be enabled since some segfault occurs while using it.")
	option(BEAGLE_HAVE_GNUCXX_HASHSET "Enable __gnu_cxx::hash_set anyway?" OFF)
endif(HASHSET_GNUCXX)
if(HASHSET_STDEXT)
	message(STATUS "++ stdext::hash_set found")
	set(BEAGLE_HAVE_STDEXT_HASHSET 1)
endif(HASHSET_STDEXT)
if(NOT DEFINED HASHSET_STD AND NOT DEFINED HASHSET_GNUCXX AND NOT DEFINED HASHSET_STDEXT)
	message(STATUS "++ no hash_set found")
endif(NOT DEFINED HASHSET_STD AND NOT DEFINED HASHSET_GNUCXX AND NOT DEFINED HASHSET_STDEXT)

# Check for C++0x new hash headers on G++
if(BEAGLE_USE_C0x)
	check_cxx_compiler_flag("-std=c++0x" COMPILER_SUPPORTS_C0X)
	if(COMPILER_SUPPORTS_C0X)
		set(CMAKE_REQUIRED_FLAGS "-std=c++0x")
	endif(COMPILER_SUPPORTS_C0X)
endif(BEAGLE_USE_C0x)

PerformTest(CXX_HAVE_UNORDERED_MAP)
PerformTest(CXX_HAVE_UNORDERED_SET)
if(CXX_HAVE_UNORDERED_MAP AND CXX_HAVE_UNORDERED_SET)
	message(STATUS "++ compiler supports C++0x hash tables")
	set(BEAGLE_HAVE_UNORDERED_MAP true)
	set(BEAGLE_HAVE_UNORDERED_SET true)
endif(CXX_HAVE_UNORDERED_MAP AND CXX_HAVE_UNORDERED_SET)

PerformTest(CXX_HAVE_UNORDERED_MAP_TR1)
PerformTest(CXX_HAVE_UNORDERED_SET_TR1)
if(CXX_HAVE_UNORDERED_MAP_TR1)
	message(STATUS "++ found std::tr1::unordered_map")
	set(BEAGLE_HAVE_STDTR1_UNORDEREDMAP true)
endif(CXX_HAVE_UNORDERED_MAP_TR1)
if(CXX_HAVE_UNORDERED_SET_TR1)
	message(STATUS "++ found std::tr1::unordered_set")
	set(BEAGLE_HAVE_STDTR1_UNORDEREDSET true)
endif(CXX_HAVE_UNORDERED_SET_TR1)

# Check for cast types
PerformTest(CXX_HAVE_CONST_CAST)
PerformTest(CXX_HAVE_DYN_CAST)
PerformTest(CXX_HAVE_STATIC_CAST)
PerformTest(CXX_HAVE_REINTERPRET_CAST)

if(CXX_HAVE_CONST_CAST)
	message(STATUS "++ compiler supports const_cast<>")
	set(BEAGLE_HAVE_CONST_CAST 1)
else(CXX_HAVE_CONST_CAST)
	message(STATUS "++ const_cast<> not supported")
endif(CXX_HAVE_CONST_CAST)

if(CXX_HAVE_DYN_CAST)
	message(STATUS "++ compiler supports dynamic_cast<>")
	set(BEAGLE_HAVE_DYNAMIC_CAST 1)
else(CXX_HAVE_DYN_CAST)
	message(STATUS "++ dynamic_cast<> not supported")
endif(CXX_HAVE_DYN_CAST)

if(CXX_HAVE_STATIC_CAST)
	message(STATUS "++ compiler supports static_cast<>")
	set(BEAGLE_HAVE_STATIC_CAST 1)
else(CXX_HAVE_STATIC_CAST)
	message(STATUS "++ static_cast<> not supported")
endif(CXX_HAVE_STATIC_CAST)

if(CXX_HAVE_REINTERPRET_CAST)
	message(STATUS "++ compiler supports reinterpret_cast<>")
	set(BEAGLE_HAVE_REINTERPRET_CAST 1)
else(CXX_HAVE_REINTERPRET_CAST)
	message(STATUS "++ reinterpret_cast<> not supported")
endif(CXX_HAVE_REINTERPRET_CAST)


PerformTest(CXX_HAVE_ISFINITE)
PerformTest(CXX_HAVE_NUMERIC_LIMITS)
if(CXX_HAVE_ISFINITE)
	message(STATUS "++ compiler supports isfinite()")
	set(BEAGLE_HAVE_ISFINITE 1)
else(CXX_HAVE_ISFINITE)
	message(STATUS "++ isfinite() not supported by the compiler")
endif(CXX_HAVE_ISFINITE)

if(CXX_HAVE_NUMERIC_LIMITS)
	message(STATUS "++ compiler defines numeric limits")
	set(BEAGLE_HAVE_NUMERIC_LIMITS 1)
else(CXX_HAVE_NUMERIC_LIMITS)
	message(STATUS "++ compiler does not define numeric limits")
endif(CXX_HAVE_NUMERIC_LIMITS)

# Check for Run-time Type Identification
PerformTest(CXX_HAVE_RTTI)
if(CXX_HAVE_RTTI)
	message(STATUS "++ compiler supports Run-Time Type Identification")
	set(BEAGLE_HAVE_RTTI 1)
else(CXX_HAVE_RTTI)
	message(STATUS "++ Run-Time Type Identification not supported")
endif(CXX_HAVE_RTTI)

# Check for stringstream support
PerformTest(CXX_HAVE_SSTREAM)
if(CXX_HAVE_SSTREAM)
	message(STATUS "++ compiler has stringstream")
	set(BEAGLE_HAVE_SSTREAM 1)
else(CXX_HAVE_SSTREAM)
	message(SEND_ERROR "!! Sorry, no sstream found. If you are using gcc less or equal to 2.95.2, see http://gcc.gnu.org/faq.html#2.95sstream to patch your compiler")
endif(CXX_HAVE_SSTREAM)

# Set debug variable
if(NOT CMAKE_BUILD_TYPE)
	   set(CMAKE_BUILD_TYPE "Debug")
endif(NOT CMAKE_BUILD_TYPE)
message(STATUS "++ Building in ${CMAKE_BUILD_TYPE} mode")
if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
		message(STATUS "++ Building in Release mode")
	   set(BEAGLE_NDEBUG 1)
	   message(STATUS "++ BEAGLE_NDEBUG variable set")
else(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
	message(STATUS "++ Building in Debug mode")
endif(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
set(BEAGLE_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")

# Check for PACC
FindPacc()

# Check for zlib
find_package(ZLIB)
if(ZLIB_FOUND)
    #add_definitions(-DPACC_ZLIB)
    #message(STATUS "++ PACC_ZLIB variable set")
    include_directories(${ZLIB_INCLUDE_DIR})
	install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/gzstream.h DESTINATION include)
	set(BEAGLE_HAVE_LIBZ 1)
else(ZLIB_FOUND)
    message(STATUS "++ Cannot find the zlib library") 
endif(ZLIB_FOUND)

if(BORLAND)
    # On doit faire une inclusion supplémentaire si on utilise une variante de ce compilateur
    set(BEAGLE_BORLAND_FLOAT 1)
    message(STATUS "++ Borland C++ Builder detected... including <float.h> to get FLT_MAX")
endif(BORLAND)

# Allow to disable all annoying Visual C++ warnings
if(MSVC)
	option(BEAGLE_MSVC_NOWARNINGS "Do you want to disable Visual C++ warnings?" ON)
endif(MSVC)
if(BEAGLE_MSVC_NOWARNINGS)
	message(STATUS "++ Disable Visual Studio compilation warnings...")
	add_definitions(/w)
endif(BEAGLE_MSVC_NOWARNINGS)

# Check for MPI
# Define following variables if MPI is found:
#   MPI_INCLUDE_PATH
#   MPI_LINK_FLAGS
#   MPI_LIBRARY 
#   MPI_EXTRA_LIBRARY
#   MPI_LIBRARIES

find_package(MPI)
if(MPI_FOUND)
	message(STATUS "++ MPI found")
	set(BEAGLE_HAVE_MPI 1)
	if(NOT DEFINED BEAGLE_NO_HPC)
		include_directories("${MPI_INCLUDE_PATH}")
		find_program(MPI_INFO NAMES ompi_info)
		mark_as_advanced(MPI_INFO)
		if(MPI_INFO)
			exec_program(${MPI_INFO} OUTPUT_VARIABLE MPI_INFO_LIST)
			string(REGEX MATCHALL "exceptions: yes" MPI_EXCEPTIONS "${MPI_INFO_LIST}")
			string(REGEX MATCHALL "mpi: yes, progress: (yes|no)" MPI_THREADS "${MPI_INFO_LIST}")
			if(NOT MPI_EXCEPTIONS)
				message(STATUS "!! The current MPI installed version doesn't support C++ exceptions. HPC won't be compiled.")
				option(BEAGLE_NO_HPC "Disable Open Beagle HPC?" ON)
			endif(NOT MPI_EXCEPTIONS)
			if(NOT MPI_THREADS)
				message(STATUS "!! The current MPI installed version doesn't support C++ multi-threads. HPC won't be compiled.")
				option(BEAGLE_NO_HPC "Disable Open Beagle HPC?" ON)
			endif(NOT MPI_THREADS)
		endif(MPI_INFO)
		if(MPI_THREADS AND MPI_EXCEPTIONS)
			option(BEAGLE_NO_HPC "Disable Open Beagle HPC?" OFF)
		endif(MPI_THREADS AND MPI_EXCEPTIONS)
	
	endif(NOT DEFINED BEAGLE_NO_HPC)
else(MPI_FOUND)
	message(STATUS "++ MPI not found")
	message(STATUS "!! OpenBeagle HPC cannot be enabled without MPI; HPC module should not be used.")
	option(BEAGLE_NO_HPC "Disable Open Beagle HPC?" ON)
endif(MPI_FOUND)

# Check for OpenMP
# BEAGLE_OMP_MODE = DYNAMIC | STATIC | NONE (default = NONE)

find_package(OpenMP QUIET) 		# FindOpenMP macro is not available in all configurations, so we try to use the "official" package
mark_as_advanced(OpenMP_DIR) 		
if(OpenMP_DIR MATCHES OpenMP_DIR-NOTFOUND)	# If CMake fails to locate FindOpenMP, we use our own macro
	include(CMakeMacros/FindOpenMP.cmake)
endif(OpenMP_DIR MATCHES OpenMP_DIR-NOTFOUND)

if(OPENMP_FOUND)
	message(STATUS "++ OpenMP found")
	
	if(NOT DEFINED BEAGLE_OMP_MODE)
		message(STATUS "++ If you want to enable OpenMP, set BEAGLE_OMP_MODE to STATIC or DYNAMIC, depending in which mode scheduler should work.")
		set(BEAGLE_OMP_MODE "NONE" CACHE STRING "OpenMP scheduler modes : NONE (do not use OpenMP at all), STATIC (reproducible results), DYNAMIC (non-reproducible results)")
	endif(NOT DEFINED BEAGLE_OMP_MODE)

	string(TOUPPER ${BEAGLE_OMP_MODE} BEAGLE_OMP_MODE)
	
	if(BEAGLE_OMP_MODE MATCHES "NONE")
		message(STATUS "++ OpenMP is not enabled, set BEAGLE_OMP_MODE to STATIC | DYNAMIC to enable it.")
		set(BEAGLE_USE_OMP_R False)
		set(BEAGLE_USE_OMP_NR False)
	elseif(BEAGLE_OMP_MODE MATCHES "STATIC")
		message(STATUS "++ OpenMP enabled, scheduler set to static mode.")
		set(BEAGLE_USE_OMP_R True)
		set(BEAGLE_USE_OMP_NR False)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
	elseif(BEAGLE_OMP_MODE MATCHES "DYNAMIC")
		message(STATUS "++ OpenMP enabled, scheduler set to dynamic mode.")
		set(BEAGLE_USE_OMP_NR True)
		set(BEAGLE_USE_OMP_R False)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
	else(BEAGLE_OMP_MODE MATCHES "NONE")
		message(STATUS "++ Invalid value for BEAGLE_OMP_MODE : NONE | STATIC | DYNAMIC expected, but found ${BEAGLE_OMP_MODE}; OpenMP is disabled.")
		set(BEAGLE_OMP_MODE "NONE" CACHE STRING "OpenMP scheduler modes : NONE (do not use OpenMP at all), STATIC (reproducible results), DYNAMIC (non-reproducible results)")
		set(BEAGLE_USE_OMP_R False)
		set(BEAGLE_USE_OMP_NR False)
	endif(BEAGLE_OMP_MODE MATCHES "NONE")
	
	if(NOT BEAGLE_OMP_MODE MATCHES "NONE")
		set(BEAGLE_HAVE_OPENMP 1)
		
		if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
			message(STATUS "++ Compiling with GNU, parallel version of STL algorithms will be used if they are available.")
			execute_process(COMMAND gcc -dumpversion OUTPUT_VARIABLE CMAKE_CXX_COMPILER_VERSION)
			
			if(CMAKE_CXX_COMPILER_VERSION MATCHES "4?\\.[3-9]?\\.[0-9]")
				message(STATUS "GCC ${CMAKE_CXX_COMPILER_VERSION} found, enabling parallel STL")

				set(CMAKE_REQUIRED_FLAGS "-L${PACC_LIB_FOUND_DIR} -I${PACC_INCLUDE_FOUND_DIR} -lpacc -fopenmp -D_GLIBCXX_PARALLEL")
				message(STATUS "++ Check if PACC has been compiled with parallel STL...")
				PerformTest(PACC_HAVE_PARALLEL_STL)
				if(NOT PACC_HAVE_PARALLEL_STL)
					message("!! Warning : your PACC library has not been compiled with parallel version of STL, forced to disable parallel STL for beagle too...")
				else(NOT PACC_HAVE_PARALLEL_STL)
					message(STATUS "++ PACC parallel STL ok...")
					add_definitions(-D_GLIBCXX_PARALLEL)
				endif(NOT PACC_HAVE_PARALLEL_STL)
				set(CMAKE_REQUIRED_FLAGS)		# Unset modified CMake variables
			else(CMAKE_CXX_COMPILER_VERSION MATCHES "4?\\.[3-9]?\\.[0-9]")
				message(STATUS "Parallel STL requires GCC >= 4.3, you are using ${CMAKE_CXX_COMPILER_VERSION}")
			endif(CMAKE_CXX_COMPILER_VERSION MATCHES "4?\\.[3-9]?\\.[0-9]")			
		endif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	endif(NOT BEAGLE_OMP_MODE MATCHES "NONE")

	mark_as_advanced(BEAGLE_USE_OMP_R BEAGLE_USE_OMP_NR)

else(OPENMP_FOUND)
	message(STATUS "++ OpenMP not found")
endif(OPENMP_FOUND)

include(FindThreads)

if(CMAKE_USE_PTHREADS_INIT)
	message(STATUS "++ PThreads found")
	set(BEAGLE_HAVE_PTHREAD 1)
elseif(CMAKE_HP_PTHREADS_INIT)
	message(STATUS "++ HP PThreads found")
	set(BEAGLE_HAVE_PTHREAD 1)	
elseif(CMAKE_USE_WIN32_THREADS_INIT)
	message(STATUS "++ Win32 threads found")
	set(BEAGLE_HAVE_WIN32_THREAD 1)
else(CMAKE_USE_PTHREADS_INIT)
	message(SEND_ERROR "!! no thread found")
endif(CMAKE_USE_PTHREADS_INIT)


# Generate beagle/config.hpp file
CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/src/beagle/config.hpp.in" "${CMAKE_CURRENT_BINARY_DIR}/include/beagle/config.hpp")


# Fast compilation option
if(NOT DEFINED CMAKE_FAST_COMPILATION)
	option(CMAKE_FAST_COMPILATION "Do you want to active fast compilation mode?" OFF)
endif(NOT DEFINED CMAKE_FAST_COMPILATION)

if(NOT BEAGLE_USE_OMP_NR AND NOT BEAGLE_USE_OMP_R)
	set(BEAGLE_OPENMP_FILES "OpenMP.cpp RandomizerMulti.cpp")
else(NOT BEAGLE_USE_OMP_NR AND NOT BEAGLE_USE_OMP_R)
	set(BEAGLE_OPENMP_FILES "null")
endif(NOT BEAGLE_USE_OMP_NR AND NOT BEAGLE_USE_OMP_R)

if(CMAKE_FAST_COMPILATION)
	message(STATUS "++ Using fast compilation mode...")
	AllFilesInOne(libbeagle.cpp "${CMAKE_CURRENT_SOURCE_DIR}/src/beagle" "${BEAGLE_OPENMP_FILES}")
	AllFilesInOne(libbeagleGA.cpp "${CMAKE_CURRENT_SOURCE_DIR}/src/beagle/GA" "null")
	AllFilesInOne(libbeagleGP.cpp "${CMAKE_CURRENT_SOURCE_DIR}/src/beagle/GP" "null")
	AllFilesInOne(libbeagleHPC.cpp "${CMAKE_CURRENT_SOURCE_DIR}/src/beagle/HPC" "null")

	set(BEAGLE_SRC		src/beagle/libbeagle.cpp)
	set(BEAGLE_GA_SRC	src/beagle/GA/libbeagleGA.cpp)
	set(BEAGLE_GP_SRC	src/beagle/GP/libbeagleGP.cpp)
	set(BEAGLE_HPC_SRC	src/beagle/HPC/libbeagleHPC.cpp)
	message(STATUS "++ Include files generated...")
else(CMAKE_FAST_COMPILATION)
	message(STATUS "++ Using normal compilation mode...")
	file(REMOVE "${CMAKE_CURRENT_SOURCE_DIR}/src/beagle/libbeagle.cpp")
	file(REMOVE "${CMAKE_CURRENT_SOURCE_DIR}/src/beagle/GA/libbeagleGA.cpp")
	file(REMOVE "${CMAKE_CURRENT_SOURCE_DIR}/src/beagle/GP/libbeagleGP.cpp")
	file(REMOVE "${CMAKE_CURRENT_SOURCE_DIR}/src/beagle/HPC/libbeagleHPC.cpp")
	file(GLOB BEAGLE_SRC        src/beagle/*.cpp)
	file(GLOB BEAGLE_GA_SRC     src/beagle/GA/*.cpp)
	file(GLOB BEAGLE_GP_SRC     src/beagle/GP/*.cpp)
	file(GLOB BEAGLE_HPC_SRC    src/beagle/HPC/*.cpp)
	
	# Remove OpenMP files if OpenMP it no used
	if(NOT BEAGLE_USE_OMP_NR AND NOT BEAGLE_USE_OMP_R)
		list(REMOVE_ITEM BEAGLE_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/beagle/OpenMP.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/beagle/RandomizerMulti.cpp")
	endif(NOT BEAGLE_USE_OMP_NR AND NOT BEAGLE_USE_OMP_R)
endif(CMAKE_FAST_COMPILATION)

# Define targets subdirectories
file(GLOB BEAGLE_HEADERS    src/beagle/*.hpp)
file(GLOB BEAGLE_GA_HEADERS src/beagle/GA/*.hpp)
file(GLOB BEAGLE_GP_HEADERS src/beagle/GP/*.hpp)
file(GLOB BEAGLE_HPC_HEADERS src/beagle/HPC/*.hpp)

if(NOT BEAGLE_USE_OMP_NR AND NOT BEAGLE_USE_OMP_R)
	list(REMOVE_ITEM BEAGLE_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/beagle/OpenMP.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/beagle/RandomizerMulti.hpp")
endif(NOT BEAGLE_USE_OMP_NR AND NOT BEAGLE_USE_OMP_R)

# Include headers required
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_BINARY_DIR}/include")

# Create library targets
if(CMAKE_FAST_COMPILATION)
	add_library(openbeagle ${BEAGLE_LIBRARY_TYPE} ${BEAGLE_SRC})
else(CMAKE_FAST_COMPILATION)
	add_library(openbeagle ${BEAGLE_LIBRARY_TYPE} ${BEAGLE_SRC} ${BEAGLE_HEADERS})
endif(CMAKE_FAST_COMPILATION)
target_link_libraries(openbeagle pacc)
if(ZLIB_FOUND)
    target_link_libraries(openbeagle ${ZLIB_LIBRARY})
endif(ZLIB_FOUND)

set_target_properties(openbeagle PROPERTIES VERSION ${BEAGLE_VERSION} LIBRARY_OUTPUT_DIRECTORY "${BEAGLE_OUTPUT_DIR}/lib")

if(CMAKE_FAST_COMPILATION)
	add_library(openbeagle-GA ${BEAGLE_LIBRARY_TYPE} ${BEAGLE_GA_SRC})
else(CMAKE_FAST_COMPILATION)
	add_library(openbeagle-GA ${BEAGLE_LIBRARY_TYPE} ${BEAGLE_GA_SRC} ${BEAGLE_GA_HEADERS})
endif(CMAKE_FAST_COMPILATION)
add_dependencies(openbeagle-GA openbeagle)
target_link_libraries(openbeagle-GA openbeagle)
set_target_properties(openbeagle-GA PROPERTIES VERSION ${BEAGLE_VERSION} LIBRARY_OUTPUT_DIRECTORY "${BEAGLE_OUTPUT_DIR}/lib")

if(CMAKE_FAST_COMPILATION)
	add_library(openbeagle-GP ${BEAGLE_LIBRARY_TYPE} ${BEAGLE_GP_SRC})
else(CMAKE_FAST_COMPILATION)
	add_library(openbeagle-GP ${BEAGLE_LIBRARY_TYPE} ${BEAGLE_GP_SRC} ${BEAGLE_GP_HEADERS})
endif(CMAKE_FAST_COMPILATION)
add_dependencies(openbeagle-GP openbeagle)
target_link_libraries(openbeagle-GP openbeagle)
set_target_properties(openbeagle-GP PROPERTIES VERSION ${BEAGLE_VERSION} LIBRARY_OUTPUT_DIRECTORY "${BEAGLE_OUTPUT_DIR}/lib")

if(BUILD_STATIC_LIB)
	set_target_properties(openbeagle openbeagle-GA openbeagle-GP PROPERTIES VERSION ${BEAGLE_VERSION} ARCHIVE_OUTPUT_DIRECTORY "${BEAGLE_OUTPUT_DIR}/lib")
else(BUILD_STATIC_LIB)
	set_target_properties(openbeagle openbeagle-GA openbeagle-GP PROPERTIES VERSION ${BEAGLE_VERSION} LIBRARY_OUTPUT_DIRECTORY "${BEAGLE_OUTPUT_DIR}/lib")
endif(BUILD_STATIC_LIB)

if(NOT BEAGLE_NO_HPC)
	if(MPI_FOUND)
		if(CMAKE_FAST_COMPILATION)
			add_library(openbeagle-HPC ${BEAGLE_LIBRARY_TYPE} ${BEAGLE_HPC_SRC} ${MPI_INCLUDE_PATH})
		else(CMAKE_FAST_COMPILATION)
			add_library(openbeagle-HPC ${BEAGLE_LIBRARY_TYPE} ${BEAGLE_HPC_SRC} ${BEAGLE_HPC_HEADERS})
		endif(CMAKE_FAST_COMPILATION)
		add_dependencies(openbeagle-HPC openbeagle)
		set_target_properties(openbeagle-HPC PROPERTIES LINK_FLAGS ${MPI_LINK_FLAGS})
		target_link_libraries(openbeagle-HPC openbeagle ${MPI_LIBRARIES})
		if(BUILD_STATIC_LIB)
			set_target_properties(openbeagle-HPC PROPERTIES VERSION ${BEAGLE_VERSION} ARCHIVE_OUTPUT_DIRECTORY "${BEAGLE_OUTPUT_DIR}/lib")
		else(BUILD_STATIC_LIB)
			set_target_properties(openbeagle-HPC PROPERTIES VERSION ${BEAGLE_VERSION} LIBRARY_OUTPUT_DIRECTORY "${BEAGLE_OUTPUT_DIR}/lib")
		endif(BUILD_STATIC_LIB)
	else(MPI_FOUND)
		message(SEND_ERROR "!! Sorry, no MPI found. Open Beagle HPC needs MPI, to compile without HPC, compile with BEAGLE_NO_HPC")	
	endif(MPI_FOUND)
endif(NOT BEAGLE_NO_HPC)

# Do we want to use C++0x?
if(COMPILER_SUPPORTS_C0X AND BEAGLE_USE_C0x)
	set_target_properties(openbeagle openbeagle-GA openbeagle-GP openbeagle-HPC PROPERTIES COMPILE_FLAGS "-std=c++0x")
endif(COMPILER_SUPPORTS_C0X AND BEAGLE_USE_C0x)


# Install dependencies
MoveConfigFiles("${BEAGLE_HEADERS}" "${BEAGLE_OUTPUT_DIR}/include/beagle" false)
MoveConfigFiles("${BEAGLE_GA_HEADERS}" "${BEAGLE_OUTPUT_DIR}/include/beagle/GA" false)
MoveConfigFiles("${BEAGLE_GP_HEADERS}" "${BEAGLE_OUTPUT_DIR}/include/beagle/GP" false)
if(NOT BEAGLE_NO_HPC)
	MoveConfigFiles("${BEAGLE_HPC_HEADERS}" "${BEAGLE_OUTPUT_DIR}/include/beagle/HPC" false)
endif(NOT BEAGLE_NO_HPC)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/include/beagle/config.hpp ${BEAGLE_HEADERS} DESTINATION include/beagle)
install(FILES ${BEAGLE_GA_HEADERS} DESTINATION include/beagle/GA)
install(FILES ${BEAGLE_GP_HEADERS} DESTINATION include/beagle/GP)
if(NOT BEAGLE_NO_HPC)
	install(FILES ${BEAGLE_HPC_HEADERS} DESTINATION include/beagle/HPC)
endif(NOT BEAGLE_NO_HPC)

# Install targets
install(TARGETS openbeagle    DESTINATION lib)
install(TARGETS openbeagle-GA DESTINATION lib)
install(TARGETS openbeagle-GP DESTINATION lib)
if(NOT BEAGLE_NO_HPC)
	install(TARGETS openbeagle-HPC DESTINATION lib)
endif(NOT BEAGLE_NO_HPC)

if(BEAGLE_BUILD_EXAMPLES)
	message(STATUS "++ Will build OpenBeagle examples, you can avoid it if you want by setting BEAGLE_BUILD_EXAMPLES to false")
	# ant example
	file(GLOB ANT_SRC  examples/ant/*.cpp)
	file(GLOB ANT_DATA examples/ant/*.conf examples/ant/*.xml examples/ant/*.trail examples/ant/ReadMe.txt)
	add_executable(ant ${ANT_SRC})
	add_dependencies(ant openbeagle-GP openbeagle-GA openbeagle)
	target_link_libraries(ant openbeagle-GP openbeagle-GA openbeagle pacc)
	set_target_properties(ant PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${BEAGLE_OUTPUT_DIR}/bin/ant")
	MoveConfigFiles("${ANT_DATA}" "${BEAGLE_OUTPUT_DIR}/bin/ant" false)
	install(TARGETS ant DESTINATION bin/openbeagle/ant)
	install(FILES ${ANT_DATA} DESTINATION bin/openbeagle/ant)

	# knapsack example
	file(GLOB KNAPSACK_SRC  examples/knapsack/*.cpp)
	file(GLOB KNAPSACK_DATA examples/knapsack/*.conf examples/knapsack/ReadMe.txt)
	add_executable(knapsack ${KNAPSACK_SRC})
	add_dependencies(knapsack openbeagle-GA openbeagle)
	target_link_libraries(knapsack openbeagle-GA openbeagle pacc)
	set_target_properties(knapsack PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${BEAGLE_OUTPUT_DIR}/bin/knapsack")
	MoveConfigFiles("${KNAPSACK_DATA}" "${BEAGLE_OUTPUT_DIR}/bin/knapsack" false)
	install(TARGETS knapsack DESTINATION bin/openbeagle/knapsack)
	install(FILES ${KNAPSACK_DATA} DESTINATION bin/openbeagle/knapsack)

	# knapsack-hpc example
	if(NOT BEAGLE_NO_HPC)
		file(GLOB KNAPSACK_HPC_SRC  examples/knapsack-hpc/*.cpp)
		file(GLOB KNAPSACK_HPC_DATA examples/knapsack-hpc/*.conf)
		add_executable(knapsack-hpc ${KNAPSACK_HPC_SRC})
		add_dependencies(knapsack-hpc openbeagle-GA openbeagle-HPC)
		target_link_libraries(knapsack-hpc openbeagle-GA openbeagle-HPC pacc)
		set_target_properties(knapsack-hpc PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${BEAGLE_OUTPUT_DIR}/bin/knapsack-hpc")
		MoveConfigFiles("${KNAPSACK_HPC_DATA}" "${BEAGLE_OUTPUT_DIR}/bin/knapsack-hpc" false)
		install(TARGETS knapsack-hpc DESTINATION bin/openbeagle/knapsack-hpc)
		install(FILES ${KNAPSACK_HPC_DATA} DESTINATION bin/openbeagle/knapsack-hpc)
	endif(NOT BEAGLE_NO_HPC)

	# maxfct example
	file(GLOB MAXFCT_SRC  examples/maxfct/*.cpp)
	file(GLOB MAXFCT_DATA examples/maxfct/*.conf examples/maxfct/ReadMe.txt)
	add_executable(maxfct ${MAXFCT_SRC})
	add_dependencies(maxfct openbeagle-GA openbeagle)
	target_link_libraries(maxfct openbeagle-GA openbeagle pacc)
	set_target_properties(maxfct PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${BEAGLE_OUTPUT_DIR}/bin/maxfct")
	MoveConfigFiles("${MAXFCT_DATA}" "${BEAGLE_OUTPUT_DIR}/bin/maxfct" false)
	install(TARGETS maxfct DESTINATION bin/openbeagle/maxfct)
	install(FILES ${MAXFCT_DATA} DESTINATION bin/openbeagle/maxfct)

	# maxfctes example
	file(GLOB MAXFCTES_SRC  examples/maxfctes/*.cpp)
	file(GLOB MAXFCTES_DATA examples/maxfctes/*.conf examples/maxfctes/ReadMe.txt)
	add_executable(maxfctes ${MAXFCTES_SRC})
	add_dependencies(maxfctes openbeagle-GA openbeagle)
	target_link_libraries(maxfctes openbeagle-GA openbeagle pacc)
	set_target_properties(maxfctes PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${BEAGLE_OUTPUT_DIR}/bin/maxfctes")
	MoveConfigFiles("${MAXFCTES_DATA}" "${BEAGLE_OUTPUT_DIR}/bin/maxfctes" false)
	install(TARGETS maxfctes DESTINATION bin/openbeagle/maxfctes)
	install(FILES ${MAXFCTES_DATA} DESTINATION bin/openbeagle/maxfctes)

	# maxfctfloat example
	file(GLOB MAXFCTFLOAT_SRC  examples/maxfctfloat/*.cpp)
	file(GLOB MAXFCTFLOAT_DATA examples/maxfctfloat/*.conf examples/maxfctfloat/ReadMe.txt)
	add_executable(maxfctfloat ${MAXFCTFLOAT_SRC})
	add_dependencies(maxfctfloat openbeagle-GA openbeagle)
	target_link_libraries(maxfctfloat openbeagle-GA openbeagle pacc)
	set_target_properties(maxfctfloat PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${BEAGLE_OUTPUT_DIR}/bin/maxfctfloat")
	MoveConfigFiles("${MAXFCTFLOAT_DATA}" "${BEAGLE_OUTPUT_DIR}/bin/maxfctfloat" false)
	install(TARGETS maxfctfloat DESTINATION bin/openbeagle/maxfctfloat)
	install(FILES ${MAXFCTFLOAT_DATA} DESTINATION bin/openbeagle/maxfctfloat)

	# multiplexer example
	file(GLOB MULTIPLEXER_SRC  examples/multiplexer/*.cpp)
	file(GLOB MULTIPLEXER_DATA examples/multiplexer/*.conf examples/multiplexer/ReadMe.txt)
	add_executable(multiplexer ${MULTIPLEXER_SRC})
	add_dependencies(multiplexer openbeagle-GP openbeagle-GA openbeagle)
	target_link_libraries(multiplexer openbeagle-GP openbeagle-GA openbeagle pacc)
	set_target_properties(multiplexer PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${BEAGLE_OUTPUT_DIR}/bin/multiplexer")
	MoveConfigFiles("${MULTIPLEXER_DATA}" "${BEAGLE_OUTPUT_DIR}/bin/multiplexer" false)
	install(TARGETS multiplexer DESTINATION bin/openbeagle/multiplexer)
	install(FILES ${MULTIPLEXER_DATA} DESTINATION bin/openbeagle/multiplexer)

	# onemax example
	file(GLOB ONEMAX_SRC  examples/onemax/*.cpp)
	file(GLOB ONEMAX_DATA examples/onemax/*.conf examples/onemax/ReadMe.txt)
	add_executable(onemax ${ONEMAX_SRC})
	add_dependencies(onemax openbeagle-GA openbeagle)
	target_link_libraries(onemax openbeagle-GA openbeagle pacc)
	set_target_properties(onemax PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${BEAGLE_OUTPUT_DIR}/bin/onemax")
	MoveConfigFiles("${ONEMAX_DATA}" "${BEAGLE_OUTPUT_DIR}/bin/onemax" false)
	install(TARGETS onemax DESTINATION bin/openbeagle/onemax)
	install(FILES ${ONEMAX_DATA} DESTINATION bin/openbeagle/onemax)

	# parity example
	set(PARITY_SRC examples/parity/ParityEvalOp.cpp examples/parity/ParityMain.cpp)
	set(PARITY_FAST_SRC examples/parity/ParityFastEvalOp.cpp examples/parity/ParityFastMain.cpp)
	file(GLOB PARITY_DATA examples/parity/*.conf examples/parity/ReadMe.txt)
	add_executable(parity ${PARITY_SRC})
	add_dependencies(parity openbeagle-GP openbeagle-GA openbeagle)
	target_link_libraries(parity openbeagle-GP openbeagle-GA openbeagle pacc)
	add_executable(parity-fast ${PARITY_FAST_SRC})
	add_dependencies(parity-fast openbeagle-GP openbeagle-GA openbeagle)
	target_link_libraries(parity-fast openbeagle-GP openbeagle-GA openbeagle pacc)
	set_target_properties(parity parity-fast PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${BEAGLE_OUTPUT_DIR}/bin/parity")
	MoveConfigFiles("${PARITY_DATA}" "${BEAGLE_OUTPUT_DIR}/bin/parity" false)
	install(TARGETS parity parity-fast DESTINATION bin/openbeagle/parity)
	install(FILES ${PARITY_DATA} DESTINATION bin/openbeagle/parity)

	# spambase example
	file(GLOB SPAMBASE_SRC  examples/spambase/*.cpp)
	file(GLOB SPAMBASE_DATA examples/spambase/*.conf examples/spambase/spambase.data examples/spambase/ReadMe.txt)
	add_executable(spambase ${SPAMBASE_SRC})
	add_dependencies(spambase openbeagle-GP openbeagle-GA openbeagle)
	target_link_libraries(spambase openbeagle-GP openbeagle-GA openbeagle pacc)
	set_target_properties(spambase PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${BEAGLE_OUTPUT_DIR}/bin/spambase")
	MoveConfigFiles("${SPAMBASE_DATA}" "${BEAGLE_OUTPUT_DIR}/bin/spambase" false)
	install(TARGETS spambase DESTINATION bin/openbeagle/spambase)
	install(FILES ${SPAMBASE_DATA} DESTINATION bin/openbeagle/spambase)

	# symbreg example
	file(GLOB SYMBREG_SRC  examples/symbreg/*.cpp)
	file(GLOB SYMBREG_DATA examples/symbreg/*.conf examples/symbreg/ReadMe.txt)
	add_executable(symbreg ${SYMBREG_SRC})
	add_dependencies(symbreg openbeagle-GP openbeagle-GA openbeagle)
	target_link_libraries(symbreg openbeagle-GP openbeagle-GA openbeagle pacc)
	set_target_properties(symbreg PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${BEAGLE_OUTPUT_DIR}/bin/symbreg")
	MoveConfigFiles("${SYMBREG_DATA}" "${BEAGLE_OUTPUT_DIR}/bin/symbreg" false)
	install(TARGETS symbreg DESTINATION bin/openbeagle/symbreg)
	install(FILES ${SYMBREG_DATA} DESTINATION bin/openbeagle/symbreg)

	# tsp example
	file(GLOB TSP_SRC  examples/tsp/*.cpp)
	file(GLOB TSP_DATA examples/tsp/*.conf examples/tsp/ReadMe.txt)
	add_executable(tsp ${TSP_SRC})
	add_dependencies(tsp openbeagle-GA openbeagle)
	target_link_libraries(tsp openbeagle-GA openbeagle pacc)
	set_target_properties(tsp PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${BEAGLE_OUTPUT_DIR}/bin/tsp")
	MoveConfigFiles("${TSP_DATA}" "${BEAGLE_OUTPUT_DIR}/bin/tsp" false)
	install(TARGETS tsp DESTINATION bin/openbeagle/tsp)
	install(FILES ${TSP_DATA} DESTINATION bin/openbeagle/tsp)

	# tsp-hpc example
	if(NOT BEAGLE_NO_HPC)
		file(GLOB TSP_HPC_SRC  examples/tsp-hpc/*.cpp)
		file(GLOB TSP_HPC_DATA examples/tsp-hpc/*.conf)
		add_executable(tsp-hpc ${TSP_HPC_SRC})
		add_dependencies(tsp-hpc openbeagle-GA openbeagle)
		target_link_libraries(tsp-hpc openbeagle-GA openbeagle-HPC pacc)
		set_target_properties(tsp-hpc PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${BEAGLE_OUTPUT_DIR}/bin/tsp-hpc")
		MoveConfigFiles("${TSP_HPC_DATA}" "${BEAGLE_OUTPUT_DIR}/bin/tsp-hpc" false)
		install(TARGETS tsp-hpc DESTINATION bin/openbeagle/tsp-hpc)
		install(FILES ${TSP_DATA} DESTINATION bin/openbeagle/tsp-hpc)
	endif(NOT BEAGLE_NO_HPC)

	# zeromin example
	file(GLOB ZEROMIN_SRC  examples/zeromin/*.cpp)
	file(GLOB ZEROMIN_DATA examples/zeromin/*.conf examples/zeromin/ReadMe.txt)
	add_executable(zeromin ${ZEROMIN_SRC})
	add_dependencies(zeromin openbeagle-GA openbeagle)
	target_link_libraries(zeromin openbeagle-GA openbeagle pacc)
	set_target_properties(zeromin PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${BEAGLE_OUTPUT_DIR}/bin/zeromin")
	MoveConfigFiles("${ZEROMIN_DATA}" "${BEAGLE_OUTPUT_DIR}/bin/zeromin" false)
	install(TARGETS zeromin DESTINATION bin/openbeagle/zeromin)
	install(FILES ${ZEROMIN_DATA} DESTINATION bin/openbeagle/zeromin)

else(BEAGLE_BUILD_EXAMPLES)
	message(STATUS "++ Will not build examples, you can build them by rerun CMake with BEAGLE_BUILD_EXAMPLES set to true")
endif(BEAGLE_BUILD_EXAMPLES)
# BEAGLE_CREATE_DMG (needs MacOS)
# BEAGLE_CREATE_UNIX_BIN
# BEAGLE_CREATE_DEB
# BEAGLE_CREATE_RPM (need rpmbuild)
# BEAGLE_CREATE_WIN32_SETUP

# Enable package creation
set(CPACK_PACKAGE_NAME OpenBEAGLE)
set(CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_SOURCE_DIR}/1-ReadMe.txt)
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/2-License.txt)
set(CPACK_PACKAGE_VERSION ${BEAGLE_VERSION})
set(CPACK_PACKAGE_CONTACT "marc-andre.gardner.1@ulaval.ca")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Open BEAGLE is a C++ Evolutionary Computation (EC) framework. It provides an high-level software environment to do any kind of EC, with support for tree-based genetic programming; bit string, integer-valued vector, and real-valued vector genetic algorithms; and evolution strategy.")

if(BEAGLE_CREATE_DMG)
	if(NOT APPLE)
		message(SEND_ERROR "!! Cannot create PKG packages on an other system than MacOS")
	endif(NOT APPLE)
	set(CPACK_PACKAGE_FILE_NAME "Beagle-${BEAGLE_VERSION}")
endif(BEAGLE_CREATE_DMG)

if(BEAGLE_CREATE_WIN32_SETUP)
	find_program(NSIS_FOUND NSIS PATHS "C:/Program Files/NSIS") 	# Try to locate NSIS
	if(NSIS_FOUND MATCHES NSIS_FOUND-NOTFOUND)
		message(STATUS "Warning : to pack this library into a Windows Installer executable, you will need NSIS.")
		message(STATUS " NSIS is not currently installed on your system, or its path is not defined.\n You can download it at http://nsis.sourceforge.net")
	else(NSIS_FOUND MATCHES NSIS_FOUND-NOTFOUND)
		message(STATUS "++ NSIS installer creator found")
	endif(NSIS_FOUND MATCHES NSIS_FOUND-NOTFOUND)
	set(CPACK_PACKAGE_INSTALL_DIRECTORY "OpenBeagle")
	#set(CPACK_PACKAGE_ICON "pacc_banner.bmp")
	include(InstallRequiredSystemLibraries)
	install(PROGRAMS ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS} DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
endif(BEAGLE_CREATE_WIN32_SETUP)

if(BEAGLE_CREATE_UNIX_BIN)
	if(NOT UNIX)
		message(SEND_ERROR "!! Cannot create UNIX universal binaries on a non-UNIX system...")
	endif(NOT UNIX)
	set(CPACK_SOURCE_GENERATOR ${CPACK_SOURCE_GENERATOR} "TGZ" "ZIP")
endif(BEAGLE_CREATE_UNIX_BIN)

if(BEAGLE_CREATE_DEB)
	set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.4)")
	add_custom_command(TARGET zeromin POST_BUILD COMMAND cpack -G DEB -D DEBIAN_PACKAGE_ARCHITECTURE="i386")
endif(BEAGLE_CREATE_DEB)

if(BEAGLE_CREATE_RPM)
	message(STATUS "++ Warning : you need to have 'rpmbuild' installed in order to generate RPM files")
	set(CPACK_SOURCE_GENERATOR ${CPACK_SOURCE_GENERATOR} "RPM")
endif(BEAGLE_CREATE_RPM)

include(CPack)

