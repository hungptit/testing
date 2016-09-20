PROJECT(TOOLS)
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

set(PROJECTS_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/../../")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Read the git tags to determine the project version
include(GetGitVersion)
get_git_version(GIT_VERSION)

# Tell the user what versions we are using
string(REGEX MATCH "[0-9]+\\.[0-9]+\\.[0-9]+" VERSION ${GIT_VERSION})
message("-- Version: ${VERSION}")

# The version of the libraries
set(GENERIC_LIB_VERSION ${VERSION})
string(SUBSTRING ${VERSION} 0 1 GENERIC_LIB_SOVERSION)

include(CheckCXXCompilerFlag)
include(AddCXXCompilerFlag)
include(CXXFeatureCheck)

# set(CMAKE_BUILD_TYPE Debug)

set (CMAKE_BUILD_TYPE Release)
add_cxx_compiler_flag(-O4)

add_cxx_compiler_flag(-std=c++14)
add_cxx_compiler_flag(-Wall)
add_cxx_compiler_flag(-Wextra)
add_cxx_compiler_flag(-Wshadow)
# add_cxx_compiler_flag(-Werror RELEASE)
# add_cxx_compiler_flag(-Werror RELWITHDEBINFO)
# add_cxx_compiler_flag(-Werror MINSIZEREL)

add_cxx_compiler_flag(-pedantic)
add_cxx_compiler_flag(-pedantic-errors)

add_cxx_compiler_flag(-Wshorten-64-to-32)
add_cxx_compiler_flag(-Wfloat-equal)
add_cxx_compiler_flag(-Wint-to-void-pointer-cast)
add_cxx_compiler_flag(-fstrict-aliasing)
if (HAVE_CXX_FLAG_FSTRICT_ALIASING)
  add_cxx_compiler_flag(-Wstrict-aliasing)
endif()
add_cxx_compiler_flag(-Wthread-safety)
if (HAVE_WTHREAD_SAFETY)
  add_definitions(-DHAVE_WTHREAD_SAFETY)
  cxx_feature_check(THREAD_SAFETY_ATTRIBUTES)
endif()

add_cxx_compiler_flag(-DFMT_HEADER_ONLY)
add_cxx_compiler_flag(-DCEREAL_RAPIDJSON_HAS_CXX11_RVALUE_REFS)

set(CMAKE_CXX_COMPILER "${PROJECTS_FOLDER}3p/llvm/bin/clang++")

ENABLE_TESTING()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Libraries used by rocksdb
set(LIB_ROCKSDB "${PROJECTS_FOLDER}/3p/rocksdb/librocksdb.a")
set(LIB_ZLIB "${PROJECTS_FOLDER}/3p/zlib/lib/libz.a")
set(LIB_LZ4 "${PROJECTS_FOLDER}/3p/lz4/lib/liblz4.a")
set(LIB_BZ2 "${PROJECTS_FOLDER}/3p/bzip2/lib/libbz2.a")
set(LIB_SNAPPY "${PROJECTS_FOLDER}/3p/snappy/lib/libsnappy.a")
set(LIB_JEMALLOC "${PROJECTS_FOLDER}/3p/jemalloc/lib/libjemalloc.a")
set(LIB_CITYHASH "${PROJECTS_FOLDER}/3p/libcuckoo/lib/libcityhash.a")
set(LIB_SNAPPY "${PROJECTS_FOLDER}/3p/snappy/lib/libsnappy.a")
set(LIB_JEMALLOC "${PROJECTS_FOLDER}/3p/jemalloc/lib/libjemalloc.a")
set(LIB_TBB "${PROJECTS_FOLDER}/3p/tbb/lib/libtbb.so")
set(LIB_ZMQ "${PROJECTS_FOLDER}/3p/libzmq/lib/libzmq.a")

# Include folder
message(${PROJECTS_FOLDER})
include_directories (${PROJECTS_FOLDER})
include_directories ("${PROJECTS_FOLDER}/3p/fmt/include")
include_directories ("${PROJECTS_FOLDER}/3p/rocksdb/include")
include_directories ("${PROJECTS_FOLDER}/3p/zlib/include")
include_directories ("${PROJECTS_FOLDER}/3p/lz4/include")
include_directories ("${PROJECTS_FOLDER}/3p/bzip2/include")
include_directories ("${PROJECTS_FOLDER}/3p/jemalloc/include")
include_directories ("${PROJECTS_FOLDER}/3p/cereal/include")
include_directories ("${PROJECTS_FOLDER}/3p/tbb/include/")
include_directories ("${PROJECTS_FOLDER}/3p/libzmq/include")
include_directories ("${PROJECTS_FOLDER}/3p/cppzmq/")

set(SRC_FILES lpclient lpserver)
foreach (src_file ${SRC_FILES})
  ADD_EXECUTABLE(${src_file} ${src_file}.cpp)
  TARGET_LINK_LIBRARIES(${src_file} ${LIB_ZMQ} -lpthread)
  ADD_TEST(${src_file} ./${src_file})
endforeach (src_file)
