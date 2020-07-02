cmake_minimum_required(VERSION 3.10)

# set the project name
project(racing_cars)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(simulate SHARED simulate/Map.cpp simulate/Car.cpp simulate/Simulator.cpp)
add_library(visualise SHARED visualise/Render.cpp)
add_library(ai SHARED ai/DNN.cpp)

add_executable(TestGame TestGame.cpp)
target_link_libraries(TestGame simulate visualise armadillo sfml-window sfml-graphics sfml-system)

add_library(all_deps INTERFACE)
target_link_libraries(all_deps INTERFACE ai simulate visualise armadillo sfml-window sfml-graphics sfml-system pagmo boost_serialization tbb stdc++fs)
target_include_directories(all_deps INTERFACE /usr/include/eigen3)

add_executable(DNN_NSGA2 experiments/DNN_NSGA2.cpp)
target_link_libraries(DNN_NSGA2 PRIVATE all_deps)

add_executable(DNN_NSGA2_vis experiments/DNN_NSGA2_visualise.cpp)
target_link_libraries(DNN_NSGA2_vis PRIVATE all_deps)

add_executable(DNN_NSGA2_2L experiments/DNN_NSGA2_2layer.cpp)
target_link_libraries(DNN_NSGA2_2L PRIVATE all_deps)

add_executable(DNN_NSGA2_2L_vis experiments/DNN_NSGA2_2layer_visualise.cpp)
target_link_libraries(DNN_NSGA2_2L_vis PRIVATE all_deps)

add_executable(DNN_CMAES experiments/DNN_CMA_ES.cpp)
target_link_libraries(DNN_CMAES PRIVATE all_deps)

add_executable(DNN_NSGA2_islands experiments/DNN_NSGA2_islands.cpp)
target_link_libraries(DNN_NSGA2_islands PRIVATE all_deps)

add_executable(DNN_GACO experiments/DNN_GACO.cpp)
target_link_libraries(DNN_GACO PRIVATE all_deps)

add_executable(DNN_NSGA2_multi experiments/DNN_NSGA2_multi.cpp)
target_link_libraries(DNN_NSGA2_multi PRIVATE all_deps)