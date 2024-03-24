#include <AccelStepper.h>
 
#define pul 7
#define dir 6

AccelStepper stepper(1, pul, dir); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
 
void setup()
{  
  // Change these to suit your stepper if you want
  stepper.setMaxSpeed(4000);
  stepper.setAcceleration(3000);
  stepper.moveTo(5000);
}
 
void loop()
{
    // If at the end of travel go to the other end
    if (stepper.distanceToGo() == 0)
      stepper.moveTo(-stepper.currentPosition());
 
    stepper.run();
}