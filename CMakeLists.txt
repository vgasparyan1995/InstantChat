cmake_minimum_required(VERSION 3.0.2)

project(instant_chat)

include_directories(
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/src/asio/include"
    )

set(SERVER_SRC
    src/Server/main.cpp
    src/Server/ChatRoom.cpp
    src/Server/ChatServer.cpp
    src/Server/ChatSession.cpp
    src/Server/ConfigManager.cpp
    src/Server/FTPRoom.cpp
    src/Server/FTServer.cpp
    src/Server/FTSession.cpp
    src/Server/ServerManager.cpp
    )

set(CLIENT_SRC
    src/Client/ChatClient.cpp
    src/Client/ClientManager.cpp
    src/Client/CommandManager.cpp
    src/Client/ConfigManager.cpp
    src/Client/FTPClient.cpp
    src/Client/TUIManager.cpp
    src/Client/main.cpp
    )

set (GENERIC_SRC
    src/Generic/ChatMessage.cpp
    src/Generic/FilePackage.cpp
    src/Generic/FileUtils.cpp
    src/Generic/ConsoleManager.cpp
    src/Generic/SignalHandler.cpp
    src/Generic/SingletonStack.cpp
    )

add_definitions(-std=c++14 -DASIO_STANDALONE -g)

add_executable(server ${SERVER_SRC} ${GENERIC_SRC})

add_executable(client ${CLIENT_SRC} ${GENERIC_SRC})
target_link_libraries(client ncurses pthread)

add_subdirectory(test)
