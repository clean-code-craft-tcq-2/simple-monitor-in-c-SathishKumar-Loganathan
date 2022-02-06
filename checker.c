#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define MINIMUM_TEMPERATURE    0.0
#define MAXIMUM_TEMPERATURE    45.0
#define MINIMUM_SOC    20.0
#define MAXIMUM_SOC    80.0
#define MINIMUM_CHARGERATE    0
#define MAXIMUM_CHARGERATE    0.8

/* Comparator Function that checks if the given input is within the given range*/
bool isBatteryParameter_OutOfRange(float currentInput, float minimumThreshold, float maximumThreshold) {
    return ((currentInput < minimumThreshold) || (currentInput > maximumThreshold));
}

/* Helper Function to print the given texts on console*/
void printMeOnDisplay(char *stringsToBeDisplayed) {
    if(stringsToBeDisplayed != NULL)
        printf("%s \n", stringsToBeDisplayed);
}

/* Helper Function to check Temperature Status */
bool isTemperatureNotSafe(float currentTemperature) {
    bool TemperatureStatus = isBatteryParameter_OutOfRange(currentTemperature, (float)MINIMUM_TEMPERATURE, (float)MAXIMUM_TEMPERATURE);
    if(TemperatureStatus)
        printMeOnDisplay("CAUTION!! Temperature is Out of Range!");

    return TemperatureStatus;        
}

/* Helper Function to check SOC Status */
bool isSOCNotSafe(float currentSOC) {
    bool SOC_Status = isBatteryParameter_OutOfRange(currentSOC, (float)MINIMUM_SOC, (float)MAXIMUM_SOC);
    if(SOC_Status) 
        printMeOnDisplay("CAUTION!! State Of Charge is Out of Range");

    return SOC_Status;
}

/* Helper Function to check Charge Rate Status */
bool isChargeRateNotSafe(float currentChargeRate) {
    bool ChargeRateStatus = isBatteryParameter_OutOfRange(currentChargeRate, (float)MINIMUM_CHARGERATE, (float)MAXIMUM_CHARGERATE);
    if(ChargeRateStatus)
        printMeOnDisplay("CAUTION!! Charge Rate is Out of Range");

    return ChargeRateStatus;
}

/* Function that implements the Helper functions */
bool isBatteryConditionNotSafe(float currentTemperature, float currentSOC, float currentChargeRate) {
    return (isTemperatureNotSafe(currentTemperature) || isSOCNotSafe(currentSOC) || isChargeRateNotSafe(currentChargeRate));  
}


/* Test Function for Unit isBatteryConditionNotSafe */
void Test_isBatteryConditionNotSafe(bool expectedState, float inputTemperature, float inputSOC, float inputChargeRate) {
    bool testState = isBatteryConditionNotSafe(inputTemperature, inputSOC, inputChargeRate);
    assert(expectedState == testState);
}

/* Test Function for Unit that Compares inputs */
void Test_isBatteryParameter_OutOfRange(bool expectedState, float testInput, float testMinThreshold, float testMaxThreshold) {
    bool testState = isBatteryParameter_OutOfRange(testInput, testMinThreshold, testMaxThreshold);
    assert(expectedState == testState);
}

int main() {
  Test_isBatteryParameter_OutOfRange(0, 23.2, 23.1, 23.3);
  Test_isBatteryParameter_OutOfRange(1, 23.0, 23.1, 23.3);

  Test_isBatteryConditionNotSafe(0, 25, 70, 0.7);
  Test_isBatteryConditionNotSafe(1, 50, 85, 0);

  return 0;
}
