include_directories(${PROJECT_SOURCE_DIR}/src/httpServer)
include_directories(${PROJECT_SOURCE_DIR}/src/htmlGame)
include_directories(${PROJECT_SOURCE_DIR}/src/mahjongCore)
include_directories(${PROJECT_SOURCE_DIR}/mahjong_evaluator/include)

add_executable(game main.cpp)

add_subdirectory(httpServer)
add_subdirectory(htmlGame)
add_subdirectory(mahjongCore)

target_link_libraries(game httpServer htmlGame mahjongCore mahjong_evaluator)
