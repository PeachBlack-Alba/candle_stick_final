#ifndef CANDLESTICKDATA_H
#define CANDLESTICKDATA_H

#include <vector>
#include <string>
#include "Candlestick.h"

// Function declaration for processing candlestick data
std::vector<Candlestick> computeCandlestickData(const std::string& filename, const std::string& country);
void plotCandlestickData(const std::vector<Candlestick>& data);
void filterByDateRange(const std::vector<Candlestick>& data, const std::string& startDate, const std::string& endDate);
void filterByTemperatureRange(const std::vector<Candlestick>& data, double minTemp, double maxTemp);
std::vector<Candlestick> predictTemperatureData(const std::vector<Candlestick>& data, int startYear, int endYear);

#endif // CANDLESTICKDATA_H
