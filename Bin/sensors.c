#ifndef SENSOR_C
#define SENSOR_C

void sensorReset(){
  for(int i = 0; i < 28; i++){
    SensorValue[i] = 0;
  }
}

int getMainBatteryVoltage(){ //Returns voltage of main battery in millivolts
  return nImmediateBatteryLevel;
}

int getSecondBatteryVoltage(){ //Returns voltage of power expander battery in millivolts
	#if USE_SECOND_BATTERY
		return SensorValue(PWR) * 1000 / 286;
	#else
		return 0;
	#endif
}


#endif
