cmake_minimum_required(VERSION 3.10)
project(toy_project)

set(CMAKE_CXX_STANDARD 14)

include_directories(Common/include)
include_directories(Common/python36/include)
include_directories(CFR/include)
include_directories(CFR/zhajinhua/include)

# Main program
add_executable(generate_random main/generate_random.cpp)
add_executable(lua_invoker main/lua_invoker.cpp)
add_executable(crf_rsp CFR/src/cfr_rsp.cpp)
add_executable(crf_rsp_2 CFR/src/cfr_rsp_2.cpp)
add_executable(cfr_kuhn CFR/src/cfr_kuhn.cpp)
add_executable(test_only main/test_only.cpp)
add_executable(py_invoker main/py_invoker.cpp)
add_executable(zjh CFR/zhajinhua/src/main.cpp)
add_executable(highlight main/highlight_card.cpp)

add_subdirectory(CFR)

target_link_libraries(cfr_kuhn cfr_kuhn_deps)
target_link_libraries(zjh zjh_deps)



