#include "switch.h"
#include "station.h"
#include <fstream>

void Switch::registerStation(const std::string& stationId, Station* station) {
    stations[stationId] = station;
}

void Switch::processFrames() {
    while (!dataQueue.empty()) {
        std::lock_guard<std::mutex> lock(mutex);
        Frame frame = dataQueue.front();
        dataQueue.pop();

        logActivity("Forwarding frame " + std::to_string(frame.sequenceNumber) +
            " from " + frame.source + " to " + frame.destination);

        if (stations.find(frame.destination) != stations.end()) {
            stations[frame.destination]->receiveFrame(frame);
        }
        else {
            logActivity("Destination " + frame.destination + " not found.");
        }
    }
}

void Switch::forwardFrame(const Frame& frame) {
    std::lock_guard<std::mutex> lock(mutex);
    dataQueue.push(frame);
}

std::mutex& Switch::getMutex() {
    return mutex;
}

std::queue<Frame>& Switch::getDataQueue() {
    return dataQueue;
}

void Switch::logActivity(const std::string& message) const {
    std::ofstream logFile("switch_log.txt", std::ios::app);
    if (logFile.is_open()) {
        logFile << message << std::endl;
        logFile.close();
    }
}
