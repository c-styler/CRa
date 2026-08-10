# CMakeList.txt : CMake project for Project-Ra, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (CRa "src/main.c" "src/code.c" "src/debug.c" "src/memory.c" "src/value.c")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CRa PROPERTY C_STANDARD 17)
endif()

# TODO: Add tests and install targets if needed.
