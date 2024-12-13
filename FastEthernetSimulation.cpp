#include "station.h"
#include "switch.h"

int main() {
    Switch ethernetSwitch;

    Station station1("SP1"), station2("SP2"), station3("SP3");
    ethernetSwitch.registerStation("SP1", &station1);
    ethernetSwitch.registerStation("SP2", &station2);
    ethernetSwitch.registerStation("SP3", &station3);

    Frame frame1(1, "SP1", "SP2", "Hello SP2!", 1);
    Frame frame2(2, "SP2", "SP3", "Hello SP3!", 2);

    station1.sendFrame(frame1, ethernetSwitch);
    station2.sendFrame(frame2, ethernetSwitch);

    ethernetSwitch.processFrames();

    return 0;
}