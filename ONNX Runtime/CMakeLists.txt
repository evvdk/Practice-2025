cmake_minimum_required(VERSION 3.10)
project(ONNX)

set(CMAKE_CXX_STANDARD 17)

include_directories($ENV{ONNX_DIR}/include)
link_directories($ENV{ONNX_DIR}/lib)

add_executable(ONNX main.cpp)
target_link_libraries(ONNX onnxruntime)

add_custom_command(TARGET ONNX POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "$ENV{ONNX_DIR}/lib/onnxruntime.dll"
    $<TARGET_FILE_DIR:ONNX>
)