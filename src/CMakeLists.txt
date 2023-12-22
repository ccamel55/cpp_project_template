project(${CPP_PROJECT_NAME}_src)

# a source file must always be included when building a static library.
add_library(${PROJECT_NAME} STATIC main.cpp)

# include directory's must be public so that we can access the library from our runnable and test targets
target_include_directories(${PROJECT_NAME} PUBLIC
        include
)

target_link_libraries(${PROJECT_NAME} PUBLIC
        custom_lib
)