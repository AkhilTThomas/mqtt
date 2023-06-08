from conans import ConanFile, CMake

class MqttSample(ConanFile):
    name = "mqtt-sample"
    version = "0.1"
    generators = "cmake"
    requires = \
        "paho-mqtt-c/1.3.9@#0421671a9f4e8ccfa5fc678cfb160394", \
        "paho-mqtt-cpp/1.2.0@#cb70f45760e60655faa35251a394b1d2"
    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder= ".", build_folder="build")
        cmake.build()
