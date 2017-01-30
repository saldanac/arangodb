# -*- mode: CMAKE; -*-
# these are the install targets for the client package.
# we can't use RUNTIME DESTINATION here.

set(STRIP_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_X}/strip")
execute_process(COMMAND mkdir -p ${STRIP_DIR})

set(FILE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_X}/${BIN_ARANGOD}${CMAKE_EXECUTABLE_SUFFIX})
set(STRIP_FILE ${STRIP_DIR}/${BIN_ARANGOD}${CMAKE_EXECUTABLE_SUFFIX})
if (NOT MSVC AND CMAKE_STRIP)
  execute_process(COMMAND "rm" -f ${STRIP_FILE})
  execute_process(COMMAND ${CMAKE_OBJCOPY} --only-keep-debug ${FILE} ${STRIP_FILE})
  set(FILE ${STRIP_FILE})
endif()
install(
  PROGRAMS ${FILE}
  DESTINATION ${CMAKE_INSTALL_DEBINFO_DIR}/${CMAKE_INSTALL_SBINDIR})
