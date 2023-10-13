project(${CPP_PROJECT_NAME}_runnable)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
        ${CPP_PROJECT_NAME}_src
)