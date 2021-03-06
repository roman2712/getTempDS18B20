#ifndef get_temp_DS18B20
#define get_temp_DS18B20

#include <OneWire.h>
#include <DallasTemperature.h>

class DS18B20
{
  private:
    OneWire *oneWire;
    DallasTemperature *sensors;
    DeviceAddress tempDeviceAddress;
	float temperature;
	unsigned long lastTempRequest;
	byte reset;
  public:
    float getTemp();
    DS18B20(byte PIN)
    {
      oneWire = new OneWire(PIN);
      sensors = new DallasTemperature(oneWire);
	  temperature = -127.0;
	  lastTempRequest = 0;
	  reset = 0;
    }
	void resetData(byte _reset)
	{
		reset = _reset;
		temperature = -127.0;
	}
};



float DS18B20::getTemp()
{
  if (lastTempRequest == 0) 
  {	  
	sensors->begin();
	sensors->getAddress(tempDeviceAddress, 0);
	sensors->setResolution(tempDeviceAddress, 12);
	sensors->setWaitForConversion(false);
	sensors->requestTemperatures();
	lastTempRequest = millis();
  } 
  if (millis() - lastTempRequest >= 750)
  {
    if (!reset) temperature = sensors->getTempCByIndex(0);
	else 
	{
		sensors->getTempCByIndex(0);
		--reset;
    }
	sensors->requestTemperatures();
    lastTempRequest = millis();
  }
  return temperature;
}

#endif