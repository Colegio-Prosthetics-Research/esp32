export class Hand {
  constructor({ versionName, thumb, index, middle, ring, pinky }) {
    this.versionName = versionName;
    this.thumb = thumb;
    this.index = index;
    this.middle = middle;
    this.ring = ring;
    this.pinky = pinky;
  }

  get fingers() {
    return [this.thumb, this.index, this.middle, this.ring, this.pinky];
  }

  get angles() {
    return this.fingers.map(finger => finger.angle);
  }
}

export class Finger {
  #openFraction;
  #fullyOpenedAngle;
  #fullyClosedAngle;
  #angleRange;
  #angle;
  
  constructor(fullyOpenedAngle, fullyClosedAngle, openFraction = 1) {
    this.#fullyOpenedAngle = fullyOpenedAngle;
    this.#fullyClosedAngle = fullyClosedAngle;
    this.#angleRange = fullyOpenedAngle - fullyClosedAngle;
    this.openTo(openFraction)
  }

  get openFraction() {
    return this.#openFraction;
  }

  openTo(fraction) {
    this.#openFraction = fraction;
    this.#angle = this.calculateAngle(this.#openFraction);
  }

  get angleRange() {
    return this.#angleRange;
  }

  get angle() {
    return this.#angle;
  }

  // fraction is a number between 0 and 1, being fully closed and fully open, respectively.
  calculateAngle(fraction) {
    return this.#fullyClosedAngle + (this.#angleRange * fraction);
  }
}
