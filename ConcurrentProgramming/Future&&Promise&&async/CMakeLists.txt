add_executable(futurepromiseasync)

target_sources(futurepromiseasync
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/future&&promise&&async.cpp
)