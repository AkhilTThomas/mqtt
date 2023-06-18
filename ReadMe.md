# Pre-requiste

```shell
# install conan package for python
pip install conan==1.59.0
# add artifactory remote repository
conan remote add conancenter https://center.conan.io
# Install conan profile
mkdir build && cd build
conan install .. -pr:h ../.conan/profile/linux_x86_64_debug
# build executable
conan build ..

```

# Testing

- Start the local mqtt server

    Press `F1` > Type `Tasks: Run task` > Select `Run MQTT Server` - This will pull and start a docker container running mqtt on port 1883

*Note: To stop the mqtt server use the Task `Stop MQTT Server`*

- Install extension VSMqtt (rpdswtk.vsmqtt)  
  Add subscriber topic "hello"

- Run binary  
    ```./build/bin/publisher```