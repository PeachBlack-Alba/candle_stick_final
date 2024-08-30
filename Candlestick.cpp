#include "Candlestick.h"

// Constructor implementation
Candlestick::Candlestick(const std::string& date, double open, double high, double low, double close)
    : date(date), open(open), high(high), low(low), close(close) {}
