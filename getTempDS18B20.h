#ifndef get_temp_DS18B20
#define get_temp_DS18B20

#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWire(DS18B20);
DallasTemperature sensors(&oneWire);
DeviceAddress tempDeviceAddress;

void intTemp()
{
  sensors.begin();
  sensors.getAddress(tempDeviceAddress, 0);
  sensors.setResolution(tempDeviceAddress, 12);
  sensors.setWaitForConversion(false);
  sensors.requestTemperatures();
}

float getTemp()
{
static unsigned long lastTempRequest = 0;
static float temperature = -127.0;
if (lastTempRequest == 0) lastTempRequest = millis(); 
if (millis() - lastTempRequest >= 750) // waited long enough??
  {
    temperature = sensors.getTempCByIndex(0);
    sensors.requestTemperatures(); 
    lastTempRequest = millis(); 
  }
  return temperature;
}

#endif 
