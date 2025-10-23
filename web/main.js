const ip = '192.168.4.1';
const port = '80';

// setting up input options
var options = "";
for (i = 0; i <= 180; i++) options += `<option value="${i}">${i}º</option>`;

const fingerSelects = document.querySelectorAll(".fingerSelect");

fingerSelects.forEach((e) => {
  e.innerHTML = options;
});

// setting up presets
document.querySelectorAll(".presetButton").forEach((e) => e.addEventListener("click", usePreset));

function usePreset(e) {
  const val = e.target.getAttribute("value");

  if (val == "open") {
    fingerAngles = [0,0,0,0,0];
  }

  if (val == "point") {
    fingerAngles = [0,0,180,180,180];
  }

  if (val == "thumb") {
    fingerAngles = [0, 180, 180, 180, 180];;
  }

  if (val == "one") {
    fingerAngles = [180, 0, 180, 180, 180];
  }

  if (val == "fist") {
    fingerAngles = [180, 180, 180, 180, 180];
  }

  for (i = 0; i < 5; i++) {
    fingerSelects[i].value = fingerAngles[i];
  }

  sendHandData(fingerAngles);
}

const msgElement = document.querySelector(".msg");

// sending requests for individual fingers
fingerSelects.forEach((e) => e.addEventListener("change", sendFingerData))

async function sendFingerData(e) {
  const finger = e.target.id;
  const val = e.target.value;

  try {
    const response = await fetch(`http://${ip}:${port}/${finger}/angle/set?angle=${val}`, {
      method: 'POST'
    });
    const txt = await response.text();
    msgElement.innerText = txt;
  } catch (error) {
    msgElement.innerHTML = `<span class='err'>${error}</span>`;
  }

  console.log(finger, val);
}


// sending request for all fingers (used for presets)
async function sendHandData(fingerAngles) {
  const data = fingerAngles.join(',')
  console.log(fingerAngles);

  try {
    const response = await fetch(`http://${ip}:${port}/hand/angles/set?=angle${data}`, {
      method: 'POST'
    });
    const txt = await response.text();
    msgElement.innerText = txt;
  } catch (error) {
    msgElement.innerHTML = `<span class='err'>${error}</span>`;
  }

}
