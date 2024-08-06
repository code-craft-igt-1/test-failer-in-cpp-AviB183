#include <assert.h>
#include <string>
#include <iostream>

namespace WeatherSpace {
class IWeatherSensor {
public:
    virtual double TemperatureInC() const = 0;
    virtual int Precipitation() const = 0;
    virtual int Humidity() const = 0;
    virtual int WindSpeedKMPH() const = 0;
};

/// This is a stub for a weather sensor. For the sake of testing
/// we create a stub that generates weather data and allows us to
/// test the other parts of this application in isolation
/// without needing the actual Sensor during development

class SensorStub : public IWeatherSensor {
    int m_humidity;
    int m_precipitation;
    double m_temperature;
    int m_windSpeed;

public:
    explicit SensorStub(int humidity = 72, int precipitation = 70,
        double temperature = 26.0, int windSpeed = 52) :
        m_humidity(humidity),
        m_precipitation(precipitation),
        m_temperature(temperature),
        m_windSpeed(windSpeed) {}

    int Humidity() const override {
        return m_humidity;
    }

    int Precipitation() const override {
        return m_humidity;
    }

    double TemperatureInC() const override {
        return m_temperature;
    }

    int WindSpeedKMPH() const override {
        return m_windSpeed;
    }
};

// This is a function to predict the weather, based on readings
// from a sensor

std::string Report(const IWeatherSensor& sensor) {
    int precipitation = sensor.Precipitation();
    // precipitation < 20 is a sunny day
    std::string report = "Sunny day";

    if (sensor.TemperatureInC() > 25) {
        if (precipitation >= 20 && precipitation < 60)
            report = "Partly cloudy";
        else if (sensor.WindSpeedKMPH() > 50)
            report = "Alert, Stormy with heavy rain";
    }
    return report;
}

// Test a rainy day

void TestRainy() {
    SensorStub sensor;
    std::string report = Report(sensor);
    std::cout << report << std::endl;
    assert(report.find("rain") != std::string::npos);
}

// Test another rainy day

void TestHighPrecipitationAndLowWindspeed() {
    // This instance of stub needs to be different-
    // to give high precipitation (>60) and low wind-speed (<50)
    SensorStub sensor(0, 70, 30.0, 45);

    // strengthen the assert to expose the bug
    // (function returns Sunny day, it should predict rain)
    std::string report = Report(sensor);
    assert(report.find("rain") != std::string::npos);
}
}  // namespace WeatherSpace

int main() {
    WeatherSpace::TestRainy();
    WeatherSpace::TestHighPrecipitationAndLowWindspeed();
    std::cout << "All is well (maybe)\n";
    return 0;
}
