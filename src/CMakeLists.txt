add_executable(publisher
    publisher.cpp  
)

add_executable(consumer
    consumer.cpp
)

target_link_libraries(publisher CONAN_PKG::paho-mqtt-cpp)
target_link_libraries(consumer CONAN_PKG::paho-mqtt-cpp)