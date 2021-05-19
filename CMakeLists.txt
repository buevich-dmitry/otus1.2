cmake_minimum_required(VERSION 3.8)

project(ip_filter VERSION 1.0.0)

# find packages
find_package(Boost COMPONENTS unit_test_framework REQUIRED)


# common properties
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# target ip_lib
add_library(ip_lib ip.h ip.cpp)
target_compile_options(ip_lib PRIVATE
    -Wall -Wextra -pedantic -Werror
)


# target ip_filter
add_executable(ip_filter main.cpp)
target_link_libraries(ip_filter PRIVATE ip_lib)
target_compile_options(ip_filter PRIVATE
    -Wall -Wextra -pedantic -Werror
)


# target test_version
add_executable(test_ip_lib test_ip.cpp)
set_target_properties(test_ip_lib PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)
target_link_libraries(test_ip_lib
    ${Boost_LIBRARIES}
    ip_lib
)
target_compile_options(test_ip_lib PRIVATE
    -Wall -Wextra -pedantic -Werror
)


enable_testing()
add_test(test_ip_lib test_ip_lib)


install(TARGETS ip_filter RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_DEB_COMPONENT_INSTALL ON)
set(CPACK_DEB_PACKAGE_NAME ${CMAKE_PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${ip_filter_VERSION})
set(CPACK_PACKAGE_CONTACT buevichd@yandex-team.ru)
include(CPack)
