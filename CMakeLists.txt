cmake_minimum_required(VERSION 3.22)

project(SnapTalk LANGUAGES CXX)
set(target_name SnapTalk-client)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g -fsanitize=address")
#
set(SRC_FILES
    src/main.cpp
    src/gui/chatwidget.cpp)
#
set(HDR_FILES
    src/gui/chatwidget.h)
#
set(UI_FILES
    src/gui/chatwidget.ui)
#
set(PROTO_FILES src/proto/messenger.proto)
#
include_directories(src/gui)
#
find_package(Protobuf REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
#
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
#
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
#
#!!!!!! С этим нужно подумать
set(grpc_cpp_plugin_location /usr/bin/grpc_cpp_plugin)
#!!!!!!
protobuf_generate_cpp(PROTO_SRC PROTO_HDR ${PROTO_FILES})
protobuf_generate_cpp(PROTO_GRPC_SRC PROTO_GRPC_HDR ${PROTO_FILES} LANGUAGE grpc GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}")
#
#
add_executable(${target_name}
    ${SRC_FILES} ${HDR_FILES} ${UI_FILES}
    ${PROTO_SRC} ${PROTO_HDR} ${PROTO_FILES}
)
#
target_link_libraries(${target_name}
    PRIVATE Qt6::Widgets
    ${Protobuf_LIBRARIES}
)
