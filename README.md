<div align="center">

# 🌱 Smart Plant Watering System

![Arduino](https://img.shields.io/badge/Platform-Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)
![Language](https://img.shields.io/badge/Language-C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)

<br>
<p align="center">
  <img width="1707" height="807" src="https://github.com/user-attachments/assets/1c4afc1b-e3f3-4387-a5d9-76939806b970" alt="Circuit Diagram"/>
</p>

<br>

**An autonomous IoT solution for plant care, featuring real-time soil moisture monitoring and ambient light sensing.**

</div>

---

<h2 align="center">📖 Overview</h2>

<p align="justify">
This project is an <b>autonomous irrigation system</b> designed to optimize water usage and ensure plant health. By continuously analyzing soil moisture levels, the system activates a water valve (servo motor) only when necessary. Additionally, it features an integrated day/night detection system to control ambient lighting automatically.
</p>

<h3 align="center">🎯 Key Features</h3>

<p align="justify">
<ul>
<li><b>💧 Smart Irrigation:</b> Activates watering mechanism only when soil moisture drops below a specific threshold.</li>
<li><b>🌗 Day/Night Detection:</b> Uses an LDR sensor to detect darkness and automatically toggle LED lighting.</li>
<li><b>⚡ Continuous Feedback:</b> Real-time monitoring loop ensuring immediate response to environmental changes.</li>
<li><b>🔋 Resource Efficient:</b> Prevents overwatering and saves electricity by automating the process.</li>
</ul>
</p>

---

<h2 align="center">📂 Project Structure & How to Run</h2>

<p align="justify">
To make it easy to find the code, here is the folder structure of the repository. The source code is located inside the <code>Installation</code> folder.
</p>

<div align="center">
<pre>
📦 Automatic-Plant-Watering-System
 ┣ 📂 Installation
 ┃ ┗ 📂 main_project      <-- 💻 SOURCE CODE IS HERE (.ino file)
 ┗ 📜 README.md
</pre>
</div>

<h3 align="center">🚀 Quick Start Guide</h3>

<p align="justify">
<b>1. Locate the File:</b> Navigate to the <code>Installation/main_project</code> folder in this repository.<br>
<b>2. Open:</b> Open the <code>.ino</code> file using the <b>Arduino IDE</b>.<br>
<b>3. Connect:</b> Plug your Arduino Uno into your computer via USB.<br>
<b>4. Upload:</b> Select the correct Port and Board (Arduino Uno) in the IDE, then click the <b>Upload (➡️)</b> button.
</p>

---

<h2 align="center">🛠️ Hardware Requirements</h2>

<p align="justify">
[cite_start]To build this project, you will need the following components [cite: 13-20]:
</p>

<div align="center">

| Component | Model / Type | Quantity | Description |
| :--- | :--- | :---: | :--- |
| Microcontroller | Arduino Uno R3 | 1 | The main control unit |
| Soil Sensor | HW-103 | 1 | Measures soil moisture levels |
| Light Sensor | LDR Module (3-Pin) | 1 | Detects ambient light intensity |
| Actuator | SG90 Servo Motor | 1 | Controls the water valve mechanism |
| Output | LED (Red/Yellow) | 1 | Status indicator / Night light |
| Connection | Jumper Wires & Breadboard | - | For circuit assembly |

</div>

---

<h2 align="center">🔌 Circuit & Pin Configuration</h2>

<p align="justify">
The system is wired according to the following pinout based on the source code:
</p>

<div align="center">

| Component | Arduino Pin | Function |
| :--- | :--- | :--- |
| **Soil Sensor** | `A0` | Analog Input (0-1023) |
| **LDR Sensor** | `D8` | Digital Input (Light Detection) |
| **Servo Motor** | `D9` | PWM Output (Valve Control) |
| **LED** | `D7` | Digital Output (Lighting) |
| **Power** | `5V / GND` | Common Power Rail |

</div>
<br>

<p align="justify">
> <b>Note:</b> The soil dryness threshold is calibrated to <code>600</code>. This value can be adjusted in the code depending on the specific soil type used.
</p>

---

<h2 align="center">💻 Software Logic</h2>

<p align="justify">
The system operates on two independent logic loops:
</p>

<h3 align="center">1. Irrigation Logic (Moisture Control)</h3>

<p align="justify">
The Arduino reads the analog value from the HW-103 sensor <code>analogRead(A0)</code>.
<ul>
<li><b>IF (Moisture > 600):</b> The soil is <b>DRY</b>. The Servo rotates to <b>180°</b> (Valve Open).</li>
<li><b>IF (Moisture <= 600):</b> The soil is <b>WET</b>. The Servo rotates to <b>0°</b> (Valve Closed).</li>
<li><i>Jitter Prevention:</i> The code checks the current servo position before writing a new angle to prevent unnecessary motor buzzing.</li>
</ul>
</p>

<h3 align="center">2. Lighting Logic (LDR Control)</h3>

<p align="justify">
The Arduino reads the digital state of the LDR sensor <code>digitalRead(8)</code>.
<ul>
<li><b>IF (High):</b> No light detected -> <b>Turn LED ON</b>.</li>
<li><b>IF (Low):</b> Light detected -> <b>Turn LED OFF</b>.</li>
</ul>
</p>

```cpp
// Logic Snippet
if (moistureValue > DRYNESS_THRESHOLD) {
    // Soil is Dry -> Open Valve
    if (wateringServo.read() != POS_OPEN_Y) {
        wateringServo.write(POS_OPEN_Y);
        Serial.println("Soil Dry -> Valve OPENED");
    }
}
