#include <AccelStepper.h>
 
#define pul 7
#define dir 6

AccelStepper stepper(1, pul, dir); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
 
void setup()
{  
  // Change these to suit your stepper if you want
  stepper.setMaxSpeed(3010);
  stepper.setSpeed(4000);
}
 
void loop()
{
    stepper.runSpeed();
}