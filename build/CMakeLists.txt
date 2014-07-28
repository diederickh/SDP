cmake_minimum_required(VERSION 2.8)

include(${CMAKE_CURRENT_LIST_DIR}/Triplet.cmake)

set(app sdp)
set(lib sdp)
set(sd ${CMAKE_CURRENT_LIST_DIR}/../src/)
set(id ${CMAKE_CURRENT_LIST_DIR}/../include/)
set(debug "")

if(CMAKE_BUILD_TYPE STREQUAL Debug)
  set(app "${app}_debug")
  set(debug "debug")
endif()

include_directories(
  ${CMAKE_CURRENT_LIST_DIR}/../src
  ${CMAKE_CURRENT_LIST_DIR}/../include
  ${extern_include_dir}
  ${CMAKE_CURRENT_LIST_DIR}/../extern/tinylib/src
)

set(lib_sources 
  ${sd}/sdp/SDP.cpp
  ${sd}/sdp/Utils.cpp
  ${sd}/sdp/Types.cpp
  ${sd}/sdp/Reader.cpp
  ${sd}/sdp/Writer.cpp
)

set(lib_headers
  ${id}/sdp/SDP.h
  ${id}/sdp/Utils.h
  ${id}/sdp/Types.h
  ${id}/sdp/Reader.h
  ${id}/sdp/Writer.h
)

add_library(${lib} STATIC ${lib_sources})
install(TARGETS ${lib} ARCHIVE DESTINATION lib)
install(FILES ${lib_headers} DESTINATION include/sdp)

set(test test_sdp_parser)
add_executable("${test}${debug}" ${sd}/${test}.cpp)
target_link_libraries("${test}${debug}" ${lib} ${app_libs})
install(TARGETS "${test}${debug}" DESTINATION bin)