#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include "Candlestick.h" 
#include "CandlestickData.h"
using namespace std;

int main()
{
    // File and country for data
    string filename = "weather_data.csv";
    string country = "GB";
    cout << "Task 1: Compute Candlestick Data\n";
    cout << "--------------------------------\n";

    // Compute candlestick data from CSV file
    auto candlestickData = computeCandlestickData(filename, country);
    for (const auto& candle : candlestickData) {
        // Print candlestick data
        cout << candle.date << "  ";
        cout << "O: " << candle.open << "  ";
        cout << "H: " << candle.high << "  ";
        cout << "L: " << candle.low << "  ";
        cout << "C: " << candle.close << endl;
    }
    cout << "\n\n";

    cout << "Task 2: Create Text-based Plot of Candlestick Data\n";
    cout << "--------------------------------------------------\n";
    // Plot candlestick data
    plotCandlestickData(candlestickData);
    cout << "\n\n";

    cout << "Task 3: Filter Data and Plot\n";
    cout << "-----------------------------\n";
    int choice;
    cout << "Choose filter type:\n1. Date Range\n2. Temperature Range\n";
    cin >> choice;

    // Filter and plot based on user choice
    if (choice == 1) {
        string startDate, endDate;
        cout << "Enter start date (YYYY): ";
        cin >> startDate;
        cout << "Enter end date (YYYY): ";
        cin >> endDate;
        filterByDateRange(candlestickData, startDate, endDate);     
    } else if(choice == 2) {
        double minTemp, maxTemp;
        cout << "Enter minimum temperature: ";
        cin >> minTemp;
        cout << "Enter maximum temperature: ";
        cin >> maxTemp;
        filterByTemperatureRange(candlestickData, minTemp, maxTemp);
    } else {
        cout << "Invalid choice. Exiting.\n";
    }

    cout << "Task 4: Predicting Data and Plotting\n";
    cout << "------------------------------------\n";
    // Predict temperature data and plot
    auto predictedData = predictTemperatureData(candlestickData, 1986, 2020);
    plotCandlestickData(predictedData);

    return 0;
}
