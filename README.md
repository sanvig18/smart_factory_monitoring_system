# Industrial Smart Factory Monitoring Node (C++) 🏭⚡

A low-latency, modular edge-gateway pipeline written in standard C++ designed for industrial IoT environments. The system processes high-frequency sensor streams (ambient temperature, humidity profiles, and multi-axis mechanical vibration metrics) to achieve deterministic predictive maintenance alerts without introducing execution blocks.

This architecture showcases decoupled design patterns, strict event management, and algorithmic safety thresholds tailored for the Google Apprenticeship engineering track.

---

## 🧠 Core Engineering Architecture



- **Observer Pattern Integration**: Decouples the primary core hardware ingestion pipeline (`FactoryTelemetryNode`) from processing layers (the alert processor and display dashboards). This makes it trivial to mount new network interfaces, database modules, or cloud analytics loops without editing core ingestion routines.
- **Predictive Fault Mapping**: Monitors physical hardware boundaries (e.g., thermal thresholds and vibration G-forces) using structured asynchronous event dispatching to prevent equipment degradation.

---

## 🛠️ Build and Local Validation

To compile and run this industrial telemetry simulation natively on your local machine using a C++17 compatible compiler:

```bash
# Compile using g++
g++ -std=c++17 main.cpp -o factory_monitor

# Execute binary execution
./factory_monitor
