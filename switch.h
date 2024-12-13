#ifndef SWITCH_H
#define SWITCH_H

#include "common.h"
#include <queue>
#include <map>
#include <mutex>
#include <string>

class Station; // Forward declaration of Station

class Switch {
private:
    std::queue<Frame> dataQueue;
    std::mutex mutex;
    std::map<std::string, Station*> stations;

public:
    // Register stations
    void registerStation(const std::string& stationId, Station* station);

    // Process frames
    void processFrames();

    // Forward frames
    void forwardFrame(const Frame& frame);

    // Logging
    void logActivity(const std::string& message) const;

    // Accessors
    std::mutex& getMutex();
    std::queue<Frame>& getDataQueue();
};

#endif // SWITCH_H
