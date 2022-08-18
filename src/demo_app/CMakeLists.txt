set(DEMO_SOURCES Demo.cpp
                 main.cpp)

add_executable(demo ${DEMO_SOURCES})
target_link_libraries(demo curves)
