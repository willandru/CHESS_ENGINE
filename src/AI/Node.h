#pragma once

#include <cstdint>

class Node
{
public:

    Node();

    Node(
        uint8_t from,
        uint8_t to
    );

    //------------------------------------------------
    // ACCESS
    //------------------------------------------------

    uint8_t getFrom() const;
    uint8_t getTo() const;

    void setFrom(uint8_t square);
    void setTo(uint8_t square);

private:

    uint8_t from;
    uint8_t to;
};