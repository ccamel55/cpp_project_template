project(${CPP_PROJECT_NAME}_tests)

# todo: consider support for googletest. i have been using catch2 recently because its super easy to setup.
CPMAddPackage(
        NAME Catch2
        VERSION 3.4.0
        GITHUB_REPOSITORY catchorg/Catch2
)

add_executable(${PROJECT_NAME} test.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
        Catch2::Catch2WithMain
        ${CPP_PROJECT_NAME}_src
)

enable_testing()
add_test(Tests unit_tests)