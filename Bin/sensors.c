#ifndef SENSOR_C
#define SENSOR_C

void sensorReset(){
  for(int i = 0; i < 28; i++){
    SensorValue[i] = 0;
  }
  nMotorEncoder[I2C_1] = 0;
  nMotorEncoder[I2C_2] = 0;
  nMotorEncoder[I2C_3] = 0;
  nMotorEncoder[I2C_4] = 0;
  nMotorEncoder[I2C_5] = 0;
  nMotorEncoder[I2C_6] = 0;
  nMotorEncoder[I2C_7] = 0;
  nMotorEncoder[I2C_8] = 0;
}

int getMainBatteryVoltage(){ //Returns voltage of main battery in millivolts
  return nImmediateBatteryLevel;
}

int getSecondBatteryVoltage(){ //Returns voltage of power expander battery in millivolts
	#ifndef USE_SECOND_BATTERY
	#define USE_SECOND_BATTERY 0
	#endif

	#if USE_SECOND_BATTERY == 1
		return SensorValue(PWR) * 1000 / 286;
	#else
		return 0;
	#endif
}

typedef struct {
  int valI;
  int val;
  int tI;
  int tf;
  int speed;
  float scalingFactor;
  tSensors port;
} sensor;

void updateSensorValue(sensor* s){
  s->valI = s->val;
  s->val = SensorValue(s->port) * s->scalingFactor;

  s->tf = time1[T1];

  int deltaT = s->tF - s->tI;
  if(deltaT == 0) deltaT = 1;

  s->speed = (s->val - s->valI) / deltaT;

  s->tI = s->tF;

  if(debug.sensors == 1 || debug.debug == 1){
    writeDebugStreamLine("Value: %d Speed: %d", s->val, s->speed);
  }
}

#endif
