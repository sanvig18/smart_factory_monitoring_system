#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <memory>

struct TelemetryPacket {
    float temperature;
    float humidity;
    float vibrationG; 
    std::string timestamp;
};

class FactoryAlertObserver {
public:
    virtual void onTelemetryReceived(const TelemetryPacket& packet) = 0;
    virtual ~FactoryAlertObserver() = default;
};

class ThresholdMonitor : public FactoryAlertObserver {
private:
    const float MAX_TEMP_C = 75.0f;
    const float MAX_VIBRATION_G = 4.5f;

public:
    void onTelemetryReceived(const TelemetryPacket& packet) override {
        if (packet.temperature > MAX_TEMP_C) {
            std::cout << "[ALERT] CRITICAL OVERHEAT: " << packet.temperature 
                      << "°C detected! Triggering cooling systems." << std::endl;
        }
        if (packet.vibrationG > MAX_VIBRATION_G) {
            std::cout << "[ALERT] EXCESSIVE VIBRATION: " << packet.vibrationG 
                      << "G detected! Machine alignment check required." << std::endl;
        }
    }
};

class DashboardLogger : public FactoryAlertObserver {
public:
    void onTelemetryReceived(const TelemetryPacket& packet) override {
        std::cout << "[Telemetry Log] Temp: " << packet.temperature 
                  << "°C | Humidity: " << packet.humidity 
                  << "% | Vibration: " << packet.vibrationG << "G" << std::endl;
    }
};

class FactoryTelemetryNode {
private:
    std::vector<std::shared_ptr<FactoryAlertObserver>> observers;

public:
    void registerObserver(std::shared_ptr<FactoryAlertObserver> observer) {
        observers.push_back(observer);
    }

    void parseSensorInputs(float temp, float hum, float vib) {
        TelemetryPacket packet{temp, hum, vib, "2026-06-20T22:33:00Z"};
        notifyObservers(packet);
    }

private:
    void notifyObservers(const TelemetryPacket& packet) {
        for (const auto& observer : observers) {
            observer->onTelemetryReceived(packet);
        }
    }
};

int main() {
    FactoryTelemetryNode edgeGateway;

    auto alertSystem = std::make_shared<ThresholdMonitor>();
    auto displayDashboard = std::make_shared<DashboardLogger>();

    edgeGateway.registerObserver(alertSystem);
    edgeGateway.registerObserver(displayDashboard);

    std::cout << "[System]: Industrial Smart Factory Gateway Initialized." << std::endl;

    // Simulate real-time industrial machine telemetry stream
    std::cout << "\n--- Cycle 1: Nominal Operations ---" << std::endl;
    edgeGateway.parseSensorInputs(42.3f, 55.0f, 1.2f);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::cout << "\n--- Cycle 2: Anomalous Structural Behavior ---" << std::endl;
    edgeGateway.parseSensorInputs(81.5f, 53.2f, 5.1f); 

    return 0;
}
