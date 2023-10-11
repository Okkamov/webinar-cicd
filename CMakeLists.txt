cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})
set(MY_PROJECT_NAME helloworld)
set(EXEC_FILE_NAME helloworld_cli)

project(${MY_PROJECT_NAME} VERSION ${PROJECT_VESRION})


add_subdirectory(
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest" 
    EXCLUDE_FROM_ALL
    "googletest"
)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(version.h.in version.h)

add_executable(${EXEC_FILE_NAME} main.cpp)
add_library(${MY_PROJECT_NAME} lib.cpp)
add_executable(test_version test_version.cpp)

set_target_properties(${EXEC_FILE_NAME} ${MY_PROJECT_NAME} test_version PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(${MY_PROJECT_NAME}
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(${EXEC_FILE_NAME} PRIVATE
    ${MY_PROJECT_NAME}
)

target_link_libraries(
    test_version PRIVATE
    gtest gtest_main
    ${MY_PROJECT_NAME}
)

if (MSVC)
    target_compile_options(${EXEC_FILE_NAME} PRIVATE
        /W4
    )
    target_compile_options(${MY_PROJECT_NAME} PRIVATE
        /W4
    )
    target_compile_options(test_version PRIVATE
        /W4
    )
else ()
    target_compile_options(${EXEC_FILE_NAME} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(${MY_PROJECT_NAME} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_version PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()



install(TARGETS ${EXEC_FILE_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(test_version test_version)
