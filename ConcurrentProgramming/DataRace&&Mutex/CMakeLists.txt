add_executable(DataRaceMutex)

target_sources(DataRaceMutex
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/DataRace&&Mutex.cpp
)