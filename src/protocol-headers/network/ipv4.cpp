#include "ipv4.h"

#include "ipv4_protos.hpp"

#include <netinet/in.h>

#include <iostream> // TODO RM

const std::array<std::string, ipv4::_field_count> ipv4::_descriptions {
    "Version",
    "Internet Header Length (IHL)",
    "Differentiated Services Code Point (DSCP)",
    "Explicit Congestion Notification (ECN)",
    "Total Length",
    "Identification",
    "Don't Fragment (DF) Flag",
    "More Fragments (MF) Flag",
    "Fragment offset",
    "Time to live (TTL)",
    "Protocol",
    "Header checksum",
    "Source address",
    "Destination address"
};

ipv4::ipv4(const unsigned char* bytes)
    : _data { *reinterpret_cast<const ipv4_h*>(bytes) }
{
    std::cout << "==== ipv4_vhl: " << sizeof(ipv4_vhl) << "; "
              << "ipv4_tos: " << sizeof(ipv4_tos) << "; "
              << "ipv4_flags_offset: " << sizeof(ipv4_flags_offset) << "; "
              << "ipv4_h: " << sizeof(ipv4_h) << std::endl;

    std::cout << "IPv4:\t\t";
    for (int i = 0; i < sizeof(ipv4_h); i++) {
        std::cout << std::hex << (int)bytes[i] << std::dec << ' ';
    }
    std::cout << std::endl;
}

std::string ipv4::src_addr() const
{
    return _data.src_addr.pretty_str();
}

std::string ipv4::dst_addr() const
{
    return _data.dest_addr.pretty_str();
}

transport_proto_type ipv4::next_protocol_type() const
{
    switch (static_cast<ipv4_protos>(_data.protocol)) {
    case ipv4_protos::TCP:
        return transport_proto_type::tcp;
    // case ipv4_protos::UDP:
    //     return transport_proto_type::udp;
    // case ipv4_protos::ICMP:
    //     return transport_proto_type::icmp;
    default:
        return transport_proto_type::unsupported;
        break;
    }
}

const std::pair<std::string, std::string> ipv4::operator[](std::size_t idx) const
{
    auto value = [&data = _data](std::size_t idx) -> std::string {
        switch (idx) {
        case 0:
            return std::to_string(data.vhl.version);
        case 1:
            return std::to_string(data.vhl.ihl);
        case 2:
            return std::to_string(data.tos.dscp);
        case 3:
            return std::to_string(data.tos.ecn);
        case 4:
            return std::to_string(::htons(data.length));
        case 5:
            return std::to_string(::htons(data.id));
        case 6:
            return std::to_string(data.offset.df);
        case 7:
            return std::to_string(data.offset.mf);
        case 8:
            return std::to_string(data.offset.offset);
        case 9:
            return std::to_string(data.ttl);
        case 10:
            return std::to_string(data.protocol);
        case 11:
            return std::to_string(::htons(data.checksum));
        case 12:
            return data.src_addr.pretty_str();
        case 13:
            return data.dest_addr.pretty_str();
        default:
            return "";
        }
    };
    return { value(idx), _descriptions[idx] };
}
