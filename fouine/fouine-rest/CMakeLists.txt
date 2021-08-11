add_library(fouine-rest-client ${CMAKE_CURRENT_SOURCE_DIR}/src/client.cpp)
target_link_libraries(fouine-rest-client PUBLIC CONAN_PKG::tl-expected)
target_link_libraries(fouine-rest-client PRIVATE CONAN_PKG::boost)
target_link_libraries(fouine-rest-client PRIVATE CONAN_PKG::spdlog)

if (UNIT_TEST)
    add_executable(ut-fouine-rest   ${CMAKE_CURRENT_SOURCE_DIR}/test/client.cpp
                                    ${CMAKE_CURRENT_SOURCE_DIR}/test/main.cpp)
    target_link_libraries(ut-fouine-rest CONAN_PKG::gtest fouine-rest-client)
endif (UNIT_TEST)