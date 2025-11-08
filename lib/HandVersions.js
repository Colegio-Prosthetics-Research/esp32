import { Hand, Finger } from "./Hand.js";

export const versions = {};

// Version 1
{
  let versionName = "v1";
  let thumb = new Finger(180, 0);
  let index = new Finger(180, 0);
  let middle = new Finger(180, 0);
  let ring = new Finger(180, 0);
  let pinky = new Finger(180, 0);

  versions[versionName] = new Hand({ versionName, thumb, index, middle, ring, pinky });
}

// Version 2
{
  let versionName = "v2";
  let thumb = new Finger(120, 0);
  let index = new Finger(0, 120);
  let middle = new Finger(120, 0);
  let ring = new Finger(30, 90);
  let pinky = new Finger(120, 0);

  versions[versionName] = new Hand({ versionName, thumb, index, middle, ring, pinky });
}