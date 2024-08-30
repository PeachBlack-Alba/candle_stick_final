#include "Candlestick.h"
#include "CSVReader.h"
#include <iostream>
#include <limits>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <iomanip>
using namespace std;

// Function to compute candlestick data from CSV file
vector<Candlestick> computeCandlestickData(const string& filename, const string& country) {
    CSVReader reader(filename);
    auto data = reader.readCSV();

    vector<Candlestick> candlesticks;

    // Find the index of the country-specific temperature column
    int countryIndex = -1;
    for (size_t i = 0; i < data[0].size(); ++i) {
        if (data[0][i] == country + "_temperature") {
            countryIndex = i;
            break;
        }
    }

    if (countryIndex == -1) {
        cerr << "Country code not found in the header" << endl;
        return candlesticks;
    }

    vector<double> temperatures;
    for (size_t i = 1; i < data.size(); ++i) {
        temperatures.push_back(stod(data[i][countryIndex]));
    }

    int year = 1980;
    size_t hourlyCount = 0;
    double open = 0.0, high = -numeric_limits<double>::infinity(), low = numeric_limits<double>::infinity(), close = 0.0;
    double sumTemps = 0.0;

    // Compute candlestick data for each year
    for (double temperature : temperatures) {
        sumTemps += temperature;

        if (hourlyCount == 0) {
            open = temperature;
        }
        if (temperature > high) {
            high = temperature;
        }
        if (temperature < low) {
            low = temperature; 
        }
        close = temperature;
        hourlyCount++; 

        if (hourlyCount == 8760) {
            // Non-leap year hours
            string date = to_string(year); 
            double avgTemp = sumTemps / hourlyCount;
            candlesticks.push_back(Candlestick(date, open, high, low, avgTemp));

            hourlyCount = 0;
            high = -numeric_limits<double>::infinity();
            low = numeric_limits<double>::infinity();
            sumTemps = 0.0;
            year++;
        }
    }

    if (hourlyCount > 0) {
        string date = to_string(year);
        double avgTemp = sumTemps / hourlyCount;
        candlesticks.push_back(Candlestick(date, open, high, low, avgTemp));
    }

    return candlesticks;
}

// Set console text color based on temperature trend
void setColor(bool isUp) {
    #ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (isUp) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    } else {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
    }
    #else 
    if (isUp) {
        cout << "\033[32m";
    } else {
        cout << "\033[31m";
    }
    #endif
}

// Reset console text color to default
void resetColor() {
    #ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    #else 
    cout << "\033[0m"; // Reset text color on UNIX
    #endif
}

// Function to plot candlestick data as text-based graph
void plotCandlestickData(const vector<Candlestick>& data) {
    const int plotHeight = 40; // Height of the plot
    double minPrice = -7;
    double maxPrice = 29;
    double range = maxPrice - minPrice;
    cout << " Price\n";
    int a = 31;
    // Print vertical axis and graph
    for (int row = 0; row < plotHeight; ++row) {
        double priceLevel = a - 1;
        a = a - 1;
        cout << setw(7) << fixed << setprecision(2) << priceLevel << "|";

        for (size_t i = 0; i < data.size(); ++i) {
            const auto& candle = data[i];
            double normHigh = (candle.high);
            double normLow = (candle.low);
            double normOpen = (candle.open);
            double normClose = (candle.close);

            // Calculate positions on the plot
            int highPos = static_cast<int>(normHigh);
            int lowPos = static_cast<int>(normLow);
            int openPos = static_cast<int>(normOpen);
            int closePos = static_cast<int>(normClose);

            if (a == highPos) {
                cout << "+  ";  
            } else if (a == lowPos) {
                cout << "-  ";
            } else if (a == openPos) {
                setColor(candle.close > candle.open);
                cout << "v  ";
                resetColor();
            } else if (a == closePos) {
                setColor(candle.close > candle.open);
                cout << "^  "; 
                resetColor();
            } else if (a < closePos && a > openPos) {
                setColor(candle.close > candle.open);
                cout << "o  ";
                resetColor();
            } else if (a < highPos && a > lowPos) {
                cout << "|  ";
            } else {
                cout << "   ";
            }
        }
        cout << "\n";
    }

    // Print horizontal axis
    cout << "       ";
    for (size_t i = 0; i < data.size(); ++i) {
        cout << "---"; 
    }
    cout << "\n       "; 

    for (const auto& candle : data) {
        cout << setw(2) << candle.date.substr(2, 2) << "  ";
    }
    cout << "\n";
} 

// Function to filter candlestick data by date range
void filterByDateRange(const vector<Candlestick>& data, const string& startDate, const string& endDate) {
    vector<Candlestick> filteredData;
    for (const auto& candle : data) {
        if (candle.date >= startDate && candle.date <= endDate) {
            filteredData.push_back(candle);
        }
    }
    plotCandlestickData(filteredData);
}

// Function to filter candlestick data by temperature range
void filterByTemperatureRange(const vector<Candlestick>& data, double minTemp, double maxTemp) {
    vector<Candlestick> filteredData;
    for (const auto& candle : data) {
        if (candle.high <= maxTemp && candle.low >= minTemp) {
            filteredData.push_back(candle);      
        }
    }
    plotCandlestickData(filteredData);
}

// Function for linear regression
pair<double, double> linearRegression(const vector<double>& x, const vector<double>& y) {
    double n = x.size();
    double sum_x = accumulate(x.begin(), x.end(), 0.0);
    double sum_y = accumulate(y.begin(), y.end(), 0.0);
    double sum_xx = inner_product(x.begin(), x.end(), x.begin(), 0.0);
    double sum_xy = inner_product(x.begin(), x.end(), y.begin(), 0.0);
    double slope = (n * sum_xy - sum_x * sum_y) / (n * sum_xx - sum_x * sum_x);
    double intercept = (sum_y - slope * sum_x) / n;
    return {slope, intercept};
}

// Function to predict future temperature data
vector<Candlestick> predictTemperatureData(const vector<Candlestick>& data, int startYear, int endYear) {
    vector<Candlestick> predictedData;
    vector<double> years(data.size());
    vector<double> closes(data.size());
    iota(years.begin(), years.end(), startYear);
    transform(data.begin(), data.end(), closes.begin(), [](const Candlestick& c) { return c.close; });

    auto [slope, intercept] = linearRegression(years, closes);

    double avgOpenDeviation = 0.0;
    double avgHighDeviation = 0.0;
    double avgLowDeviation = 0.0;

    for (const auto& candle : data) {
        avgOpenDeviation += (candle.open - candle.close);
        avgHighDeviation += (candle.high - candle.close);
        avgLowDeviation += (candle.low - candle.close);
    }

    avgOpenDeviation /= data.size();
    avgHighDeviation /= data.size();
    avgLowDeviation /= data.size();

    for (int year = endYear + 1; year <= endYear + 10; ++year) {
        double predictedClose = slope * year + intercept;
        double predictedOpen = predictedClose + avgOpenDeviation;
        double predictedHigh = predictedClose + avgHighDeviation;
        double predictedLow = predictedClose + avgLowDeviation;

        predictedData.push_back(Candlestick(to_string(year),
                                            predictedOpen, predictedHigh, predictedLow, predictedClose));
    }
    return predictedData;
}
