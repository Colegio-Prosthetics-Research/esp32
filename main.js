import { versions } from "./lib/HandVersions.js";

const ip = '192.168.4.1';
const port = '80';

// setting up hand version selector
const handVersionSelect = document.getElementById("versionSelect");

for (let version in versions) {
  handVersionSelect.innerHTML += `<option value="${version}">${version}</option>`;
}

var hand = Object.values(versions)[0];

handVersionSelect.addEventListener("change", (e) => {
  hand = versions[e.target.value];
});

// setting up input options
var options = "";
for (let i = 100; i >= 0; i--) options += `<option value="${i}">${i}%</option>`;

const fingerSelects = document.querySelectorAll(".fingerSelect");

fingerSelects.forEach((e) => {
  e.innerHTML = options;
});

// setting up presets
document.querySelectorAll(".presetButton").forEach((e) => e.addEventListener("click", usePreset));

function usePreset(e) {
  const val = e.target.getAttribute("value");
  var fingerOpenFractions;

  if (val == "rock") {
    fingerOpenFractions = [0, 1, 0, 0, 1];
  }

  if (val == "open") {
    fingerOpenFractions = [1, 1, 1, 1, 1];
  }

  if (val == "thumb") {
    fingerOpenFractions = [1, 0, 0, 0, 0];
  }

  if (val == "one") {
    fingerOpenFractions = [0, 1, 0, 0, 0];
  }

  if (val == "fist") {
    fingerOpenFractions = [0, 0, 0, 0, 0];
  }

  for (let i = 0; i < 5; i++) {
    fingerSelects[i].value = fingerOpenFractions[i] * 100;
    hand.fingers[i].openTo(fingerOpenFractions[i]);
  }

  sendHandData(hand.angles);
}

const msgElement = document.querySelector(".msg");

// sending requests for individual fingers
fingerSelects.forEach((e) => e.addEventListener("change", sendFingerData))

async function sendFingerData(e) {
  const finger = e.target.id;
  const val = e.target.value;

  try {
    const response = await fetch(`http://${ip}:${port}/fingers/angle/set?${finger}=${val}`);
    const txt = await response.text();
    msgElement.innerText = txt;
  } catch (error) {
    msgElement.innerHTML = `<span class='err'>${error}</span>`;
  }

  console.log(finger, val);
}


// sending request for all fingers (used for presets)
async function sendHandData(fingerAngles) {
  const angleParams = Array(5);

  for (let i = 0; i < 5; i++) {
    angleParams[i] = [`${fingerSelects[i].id}=${fingerAngles[i]}`];
  }

  console.log(fingerAngles);

  try {
    const response = await fetch(`http://${ip}:${port}/fingers/angle/set?${angleParams.join('&')}`);
    const txt = await response.text();
    msgElement.innerText = txt;
  } catch (error) {
    msgElement.innerHTML = `<span class='err'>${error}</span>`;
  }

}
