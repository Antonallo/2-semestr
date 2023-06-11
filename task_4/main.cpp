#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<sstream>

class Device {
public:
    virtual void poll() {
        std::cout << "base polled";
    }
};

class ElectricMeter : public Device {
public:
    ElectricMeter(const std::string& name) : name(name) {}

    void poll() override {
        std::cout << name << " polled1." << std::endl;
        // Реализация получения данных.
    }

private:
    std::string name;
};

class DiscreteInputBlock : public Device {
public:
    DiscreteInputBlock(const std::string& name) : name(name) {}

    void poll() override {
        std::cout << name << " polled2." << std::endl;
        // Реализация получения данных.
    }

private:
    std::string name;
};

class HeatingControlBlock : public Device {
public:
    HeatingControlBlock(const std::string& name) : name(name) {}

    void poll() override {
        std::cout << name << " polled3." << std::endl;
        // Реализация получения данных.
    }

private:
    std::string name;
};

class DeviceFactory {
public:
    std::unique_ptr<Device> createDevice(const std::string& deviceType, const std::string& deviceName) {
        if (deviceType == "ElectricMeter") {
            return std::make_unique<ElectricMeter>(deviceName);
        }
        else if (deviceType == "DiscreteInputBlock") {
            return std::make_unique<DiscreteInputBlock>(deviceName);
        }
        else if (deviceType == "HeatingControlBlock") {
            return std::make_unique<HeatingControlBlock>(deviceName);
        }

        std::cerr << "Warning: unknown device type " << deviceType << "." << std::endl;
        return nullptr;
    }
};

int main() 
{
    DeviceFactory deviceFactory;
    std::vector<std::unique_ptr<Device>> devices;

    std::ifstream file("config.txt");
    if (!file.is_open()) {
        std::cerr << "Error: could not open file config.txt." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string deviceType, deviceName;
        ss >> deviceType >> deviceName;

        std::unique_ptr<Device> device = deviceFactory.createDevice(deviceType, deviceName);
        if (device != nullptr) {
            devices.push_back(std::move(device));
        }
    }

    file.close();

    for (const auto& device : devices) {
        device->poll();
    }

    return 0;
}