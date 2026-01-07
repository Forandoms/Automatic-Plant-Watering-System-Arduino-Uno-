---

<h2 align="center">⚙️ Installation & Implementation</h2>

<p align="justify">
Follow these steps to build and run the autonomous watering system:
</p>

<h3 align="center">Step 1: Hardware Assembly</h3>

<p align="justify">
[cite_start]Connect the components to the Arduino Uno using the breadboard and jumper wires [cite: 13-20]. Ensure the power (VCC) and Ground (GND) connections are common for all modules.
</p>

<div align="center">

| Component | Connection Pin | Note |
| :--- | :--- | :--- |
| **Soil Moisture Sensor** | `A0` | Connect Analog Output (AO) to Arduino. |
| **LDR Module** | `Pin 8` | Connect Digital Output (DO) to Arduino. |
| **Servo Motor** | `Pin 9` | Orange/Yellow wire is Signal. |
| **LED** | `Pin 7` | Connect the long leg (+) to Pin 7. |

</div>

<h3 align="center">Step 2: Calibration</h3>

<p align="justify">
Every soil type is different. Before final deployment, calibrate the sensor:
<ol>
  <li>Upload the code to Arduino.</li>
  <li>Open the <b>Serial Monitor</b> (9600 baud).</li>
  [cite_start]<li>Observe the values when the sensor is in "Dry" air vs. "Wet" soil [cite: 77-80].</li>
  [cite_start]<li>Update the <code>KURULUK_ESIK_DEGERI</code> variable (Default: 600) in the code to match your soil's dry threshold[cite: 81].</li>
</ol>
</p>

<h3 align="center">Step 3: Uploading the Code</h3>

<p align="justify">
<ol>
  <li>Open the <code>.ino</code> project file in Arduino IDE.</li>
  <li>Go to <b>Tools > Board</b> and select <b>Arduino Uno</b>.</li>
  <li>Go to <b>Tools > Port</b> and select the active COM port.</li>
  <li>Click the <b>Upload</b> (Arrow) button.</li>
</ol>
</p>