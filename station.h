#ifndef STATION_H
#define STATION_H

#include "common.h"
#include "switch.h"
#include <queue>
#include <string>

class Station {
private:
    std::string id;
    std::queue<Frame> sendQueue;
    std::queue<Frame> receiveQueue;

public:
    explicit Station(const std::string& stationId);

    // Send frames
    void sendFrame(const Frame& frame, Switch& ethernetSwitch);

    // Receive frames
    void receiveFrame(const Frame& frame);

    // Process send
    void processSend(Switch& ethernetSwitch);

    // Logging
    void logActivity(const std::string& message) const;
};

#endif // STATION_H
