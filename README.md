#Weather Data Candlestick Analysis Toolkit

This project is a command-line C++ application that visualizes and predicts weather data trends across European countries using a candlestick representation. It was developed as part of the **CM2005 Object Oriented Programming Midterm** at the **University of London**.

---

##Objective

To build a **technical analysis toolkit** that uses **object-oriented programming** principles to:
- Compute candlestick data for hourly temperature readings from 1980–2019.
- Render **text-based plots** of the candlestick data.
- Allow **filtered data views** based on date, country, or temperature range.
- Provide **basic prediction functionality** to forecast temperature trends.

---

##Project Structure

| File/Folder         | Purpose |
|---------------------|---------|
| `main.cpp`          | Entry point. Manages program flow and CLI interaction. |
| `Candlestick.h/.cpp` | Defines the `Candlestick` class representing OHLC temperature data. |
| `CandlestickData.h/.cpp` | Parses data and computes candlestick metrics by year and country. |
| `CSVReader.h/.cpp`  | Handles loading and parsing of CSV weather data. |
| `README.md`         | This file. Documentation and usage guide. |
| `a.out`             | Compiled binary (may vary depending on system). |

---

##Implemented Features

### Task 1: Compute Candlestick Data
- Parses hourly weather data from 1980 to 2019.
- Computes yearly OHLC values:
  - **Open**: previous year’s average temperature.
  - **High/Low**: highest and lowest hourly temperature in the year.
  - **Close**: current year’s average temperature.
- Returns a `std::vector<Candlestick>` for further processing.

### Task 2: Text-Based Plot
- Uses ASCII characters to simulate a candlestick chart in the terminal.
- Visual elements:
  - `|` to represent high/low stalks.
  - `[]` or `##` to represent Open and Close bounds.

### Task 3: Filtering and Plotting
- Supports filtering by:
  - Country code (e.g., GB, FR, ES).
  - Year or year range (e.g., 1980–1990).
  - Temperature range (e.g., 10°C to 30°C).
- Generates plots only for filtered data.

### Task 4: Predictive Analysis
- Implements a basic prediction algorithm (e.g., linear regression or moving average).
- Forecasts next year's temperature for a selected country.
- Outputs predicted candlestick-style data and includes justification in the report.

---

##How to Compile and Run

```bash
g++ -std=c++11 -o weather_toolkit main.cpp CSVReader.cpp Candlestick.cpp CandlestickData.cpp
./weather_toolkit
