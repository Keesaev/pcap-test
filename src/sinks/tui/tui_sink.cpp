#include "tui_sink.h"

#include <iostream>

void tui_sink::run(std::string const& device)
{
    _sniffer.reset(
        new sniffer(device, std::bind(&tui_sink::print, this, std::placeholders::_1)));
    _sniffer->run();
}

void tui_sink::print(packet pkt) const
{
    const auto& dl = pkt.get_datalink();
    std::cout << "DATALINK" << std::endl;
    for (int i = 0; i < dl->size(); i++) {
        auto [value, desc] = (*dl)[i];
        std::cout << '\t' << desc << '\t' << value << std::endl;
    }

    const auto& nl = pkt.get_network();
    std::cout << "NETWORK" << std::endl;
    for(int i = 0; i < nl->size(); i++){
        auto [value, desc] = (*nl)[i];
        std::cout << '\t' << desc << '\t' << value << std::endl;
    }
}

void tui_sink::stop() { }