#include "finger.h"

Finger::Finger(double maxAngle = 180, double minAngle = 0, int servoPin = 15)  {
    this->maxAngle = maxAngle;
    this->minAngle = minAngle;
    servo.setPeriodHertz(50);           // standard 50 hz servo
    servo.attach(servoPin, 500, 2500);  // attaches the servo on servoPin to the servo object
    if (servo.attached()) {
        Serial.println("Finger servo attached on pin: " + String(servoPin) + "\n");
    } else {
        Serial.println("Failed to attach finger servo on pin: " + String(servoPin) + "\n");
    }
}

Finger::~Finger() {
    servo.detach();
    Serial.println("Finger servo detached.\n");
}

void Finger::CalculateAngle(double percentage) {
    if (percentage < 0) {
        percentage = 0;
    } else if (percentage > 100) {
        percentage = 100;
    }
    double angle = minAngle + (maxAngle - minAngle) * (percentage / 100.0);
    setAngle(angle);
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
