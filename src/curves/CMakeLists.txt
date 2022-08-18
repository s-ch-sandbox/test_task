set(CURVES_SOURCE Curve.cpp
                  Circle.cpp
                  Ellipse.cpp
                  Helix.cpp)

set(CURVES_HEADERS Curve.h
                   Circle.h
                   Ellipse.h
                   Helix.h)

add_library(curves SHARED ${CURVES_SOURCE})

target_include_directories(curves PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(curves PROPERTIES PUBLIC_HEADER "${CURVES_HEADERS}")

file(COPY ${CURVES_HEADERS} DESTINATION ${CMAKE_BINARY_DIR}/output/include/curves)
