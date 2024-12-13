#include "station.h"
#include <fstream>

Station::Station(const std::string& stationId) : id(stationId) {}

void Station::sendFrame(const Frame& frame, Switch& ethernetSwitch) {
    std::lock_guard<std::mutex> lock(ethernetSwitch.getMutex());
    ethernetSwitch.getDataQueue().push(frame);
    logActivity("Sent frame " + std::to_string(frame.sequenceNumber) + " to switch.");
}

void Station::receiveFrame(const Frame& frame) {
    receiveQueue.push(frame);
    logActivity("Received frame " + std::to_string(frame.sequenceNumber) + " from " + frame.source);
}

void Station::processSend(Switch& ethernetSwitch) {
    while (!sendQueue.empty()) {
        Frame frame = sendQueue.front();
        sendQueue.pop();
        sendFrame(frame, ethernetSwitch);
    }
}

void Station::logActivity(const std::string& message) const {
    std::ofstream logFile(id + "_log.txt", std::ios::app);
    if (logFile.is_open()) {
        logFile << message << std::endl;
        logFile.close();
    }
}
