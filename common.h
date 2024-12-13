#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <mutex>
#include <thread>
#include <condition_variable>

struct Frame {
    int sequenceNumber;
    std::string source;
    std::string destination;
    std::string data;
    int priority;

    Frame(int seqNum, const std::string& src, const std::string& dest, const std::string& d, int prio)
        : sequenceNumber(seqNum), source(src), destination(dest), data(d), priority(prio) {
    }
};

#endif // COMMON_H
