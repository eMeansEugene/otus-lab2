cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(ip_filter VERSION ${PROJECT_VERSION})

option(WITH_BOOST_TEST "Whether to build Boost test" OFF)

add_executable(ip_filter main.cpp)

set_target_properties(ip_filter PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

if(MSVC)
    target_compile_options(ip_filter PRIVATE /W4)
else()
    target_compile_options(ip_filter PRIVATE
            -Wall -Wextra -pedantic -Werror
    )
endif()

if(WITH_BOOST_TEST)
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    add_executable(test_ip_filter test_ip_filter.cpp)
    set_target_properties(test_ip_filter PROPERTIES
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED ON
            COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
            INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
    )
    if(MSVC)
        target_compile_options(test_ip_filter PRIVATE /W4)
    else()
        target_compile_options(test_ip_filter PRIVATE
                -Wall -Wextra -pedantic -Werror
        )
    endif()
    target_link_libraries(test_ip_filter ${Boost_LIBRARIES})
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

if(WITH_BOOST_TEST)
    enable_testing()
    add_test(test_ip_filter test_ip_filter)
endif()