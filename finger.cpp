#include "finger.h"

Finger::Finger(double maxAngle, int servoPin)  {
    this->maxAngle = maxAngle;
    servo.setPeriodHertz(50);           // standard 50 hz servo
    servo.attach(servoPin, 500, 2500);  // attaches the servo on servoPin to the servo object
}

Finger::~Finger() {
    servo.detach();
}

void Finger::setAngle(double angle) {
    // Implementation of finger movement logic
    if (angle < 0) {
        angle = 0;
    } else if (angle > maxAngle) {
        angle = maxAngle;
    }
    servo.write(angle);
}
