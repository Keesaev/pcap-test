#pragma once

#include "datalink.hpp"

class unsupported_datalink final : public datalink {
public:
    virtual std::string name() const final { return "Unsupported"; }
    virtual network_proto_type next_protocol() const final
    {
        return network_proto_type::unsupported;
    }
    virtual std::string hex() const final { return ""; }
    virtual int header_size() const final { return 0; };
    virtual int field_count() const final { return 0; };
    virtual const std::pair<std::string, std::string> operator[](std::size_t idx) const final { return { "", "" }; };

    virtual ~unsupported_datalink() { }
};