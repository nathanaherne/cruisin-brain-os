////////////////////////////////////////////////////////////////////////
// DO NOT EDIT THIS FILE
////////////////////////////////////////////////////////////////////////

void validateUserSettings(boolean &throttleError, boolean &reverseError, boolean &cruiseControlError) {

  // Throttle manual
  if (throttleType != "Normal" && throttleType != "Joystick" && throttleType != "PPM" && throttleType != "PWM") {
    throttleError = true;
    Serial.print("throttleType: ");Serial.print(throttleType);Serial.print(" ");Serial.print("MC_throttle: ");Serial.print(*MC_throttle);
    Serial.println();
  } else {
    throttleError = false;
  }

  reverseError = false;
  
  // Cruise Control
  if ((cruiseControlType == "Button" && *MC_cruiseControl == -1) || (cruiseControlType != "Off" && cruiseControlType != "Throttle" && cruiseControlType != "Button")) {
    cruiseControlError = true;
    Serial.print("cruiseControlType: ");Serial.print(cruiseControlType);Serial.print(" ");Serial.print("MC_cruiseControl: ");Serial.print(*MC_cruiseControl);
    Serial.println();
  } else {
    cruiseControlError = false;
  }

}

// Calculate Forward/Reverse values
void calcForwardReverseValues(int &maxForward, int &minForward, int &maxReverse, int &minReverse){
  
  // Calculations for maxForward
  if (reverseMotorDirection == true) {
    maxForward = throttleBrake - (((throttleBrake - throttleMin) * maxForwardPercent) / 100); // Based on maxForwardPercent & Throttle Output Value settings
    minForward = throttleBrake - driverDeadband / 2;
  } else if (reverseMotorDirection == false) {
    maxForward = throttleBrake + (((throttleMax - throttleBrake) * maxForwardPercent) / 100); // Based on maxForwardPercent & Throttle Output Value settings
    minForward = throttleBrake + driverDeadband / 2;
  } else {
    maxForward = throttleBrake;
  }
  
  // Calculation for maxReverse
  if (reverseMotorDirection == true) {
    maxReverse = throttleBrake + (((throttleMax - throttleBrake) * maxReversePercent) / 100); // Based on maxReversePercent & Throttle Output Value settings
    minReverse = throttleBrake + driverDeadband / 2;
  } else if (reverseMotorDirection == false) {
    maxReverse = throttleBrake - (((throttleBrake - throttleMin) * maxReversePercent) / 100); // Based on maxReversePercent & Throttle Output Value settings
    minReverse = throttleBrake - driverDeadband / 2;
  } else {
    maxReverse = throttleBrake;
  }

//  Serial.print("minForward: ");Serial.print(minForward);Serial.print(" ");
//  Serial.print("maxForward: ");Serial.print(maxForward);Serial.print(" ");
//  Serial.print("minReverse: ");Serial.print(minReverse);Serial.print(" ");
//  Serial.print("maxReverse: ");Serial.print(maxReverse);Serial.print(" ");
//  Serial.println();
}

// Calculate Cruise Control throttle values
void calcCruiseControlValues(int &maxCruiseControl, int &minCruiseControl){

  // Calculation for maxCruiseControl forward throttle && cruiseControlMinThrottle
  if (reverseMotorDirection == true) {
    maxCruiseControl = throttleBrake - (((throttleBrake - throttleMin) * maxCruiseControlPercent) / 100); //Based on maxCruiseControlPercent & Throttle Output Value settings
    minCruiseControl = throttleBrake - (((throttleBrake - maxCruiseControl) * minCruiseControlPercent) / 100);
  } else if (reverseMotorDirection == false) {
    maxCruiseControl = throttleBrake + (((throttleMax - throttleBrake) * maxCruiseControlPercent) / 100); // Based on maxCruiseControlPercent & Throttle Output Value settings
    minCruiseControl = throttleBrake + (((maxCruiseControl - throttleBrake) * minCruiseControlPercent) / 100);
  } else {
    maxCruiseControl = throttleBrake;
  }

//  Serial.print("minCruiseControl: ");Serial.print(minCruiseControl);Serial.print(" ");
//  Serial.print("maxCruiseControl: ");Serial.print(maxCruiseControl);Serial.print(" ");
//  Serial.println();

  
}

// Calculations for ramp intervals
void calcRampIntervals(unsigned long &forwardRampInterval, unsigned long &reverseRampInterval, unsigned long &brakeRampInterval, unsigned long &cruiseControlRampInterval) {
  
  forwardRampInterval = 1000 * (forwardRampPercent * (throttleRangeMs / (throttleMax - throttleMin)) / 100); // microseconds between Forward currentThrottle updates
  
  reverseRampInterval = 1000 * (reverseRampPercent * (throttleRangeMs / (throttleMax - throttleMin)) / 100); // microseconds between Reverse currentThrottle updates
  
  brakeRampInterval =  1000 * (brakeRampPercent * (throttleRangeMs / (throttleMax - throttleMin)) / 100); // microseconds between Reverse currentThrottle updates
  
  cruiseControlRampInterval = 1000 * (cruiseControlRampPercent * (throttleRangeMs / (throttleMax - throttleMin)) / 100); // microseconds between Cruise Control currentThrottle updates

//  Serial.print("forwardRampInterval: ");Serial.print(forwardRampInterval);Serial.print(" ");
//  Serial.print("reverseRampInterval: ");Serial.print(reverseRampInterval);Serial.print(" ");
//  Serial.print("brakeRampInterval: ");Serial.print(brakeRampInterval);Serial.print(" ");
//  Serial.print("cruiseControlRampInterval: ");Serial.print(cruiseControlRampInterval);Serial.print(" ");
//  Serial.println();
  
}

void calcDeadband(int &throttleDeadband_min, int &throttleDeadband_max, int &driverDeadbandHalf) {

  throttleDeadband_min = 1023 * throttleDeadband_min_Percent / 100;

  throttleDeadband_max = 1023 * throttleDeadband_max_Percent / 100;

  driverDeadbandHalf = round((driverDeadband / 2) - 0.5); // round down
}

void calcDebounceMax(int &debounceMax) {

  debounceMax = int(debounceMs * debounceSampleFrequencyHz) / 1000; // debounceMax is in seconds

  //Serial.print("debounceMax: ");Serial.print(debounceMax);Serial.println();
  
}
