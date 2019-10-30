include_directories(${PROJECT_SOURCE_DIR}/src/httpServer)
include_directories(${PROJECT_SOURCE_DIR}/src/htmlGame)
include_directories(${PROJECT_SOURCE_DIR}/src/mahjongCore)
add_executable(game main.cpp)

add_subdirectory(httpServer)
add_subdirectory(htmlGame)
add_subdirectory(mahjongCore)

target_link_libraries(game httpServer htmlGame mahjongCore mahjong_evaluator)
