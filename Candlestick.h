#ifndef CANDLESTICK_H
#define CANDLESTICK_H
#include <string>

class Candlestick {
public:
    std::string date;
    double open;
    double high;
    double low;
    double close;

    // Constructor to initialize candlestick data
    Candlestick(const std::string& date, double open, double high, double low, double close);
};

#endif // CANDLESTICK_H
