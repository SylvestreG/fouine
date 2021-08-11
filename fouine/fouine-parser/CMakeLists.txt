add_library(fouine-parser ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.cpp)

if (UNIT_TEST)
    add_executable(ut-fouine-parser ${CMAKE_CURRENT_SOURCE_DIR}/test/machine.cpp)
    target_link_libraries(ut-fouine-parser CONAN_PKG::gtest)
endif (UNIT_TEST)