# **MyoPilot: Hands-Free Neuromuscular Navigation for the Next Frontier**

## **CornHacks 2025 | A Corn Odyssey | AI-Driven EMG Control**

*"In the vastness of space, control is redefined—not by hands, but by thought."*

MyoPilot is an embedded AI system that enables hands-free robotic control using **electromyography (EMG)**. Designed for accesibility, efficiency, and adaptability in extreme environments, MyoPilot translates **facial muscle movements** into **real-time navigation commands**—a breakthrough in **biomechanical control** and **embedded intelligence**.

This project represents a step toward the future of **astronaut interfaces, assistive robotics, and next-generation control systems**.

---

## **Project Mission: Seamless Neural-Driven Navigation**

MyoPilot integrates **EMG signal processing, AI-based classification, and embedded motor control** into a fully self-contained system. Unlike traditional robotic interfaces, MyoPilot requires:

- No handheld controllers
- No external computation
- No laptops or other latency-inducing middleware

### **Control Mechanism:**

- **Right Cheek Clench** → Turn Right  
- **Left Cheek Clench** → Turn Left  
- **Both Cheeks Clench** → Move Forward  
- **Relaxed Expression** → Remain Stationary  

This system enables **precise, intuitive, and minimal-effort control**, ideal for **zero-gravity environments, high-stakes operations, and accessibility applications**.

---

## **System Overview: A Closed-Loop Neural Control System**

MyoPilot is a modular, AI-enhanced **biomechanical interface**, engineered for **real-time responsiveness** and **power efficiency**.

### **Component Breakdown:**

| **Component** | **Role** |
|--------------|---------|
| **ESP32-A (Neural Signal Processing & AI)** | Captures EMG signals, filters noise, extracts key features, records muscular contraction and classifies intent of movement using an AI model, and transmits movement commands. |
| **ESP32-B (Motor Control & Navigation)** | Receives movement commands via WiFi, executes real-time motor control, and maneuvers the land rover accordingly. |

---

## **Signal Flow: From Neural Impulse to Motion**

### **1. EMG Signal Acquisition (ESP32-A)**
- Surface electrodes detect **biopotential changes** from **facial muscle contractions**
- Signals undergo **analog-to-digital conversion (ADC)**
- **Bandpass filtering (20-450Hz) & feature extraction** (MAV, RMS, ZCR)

### **2. AI-Based Classification (ESP32-A)**
- **TinyML model** (*TensorFlow Lite for Microcontrollers*) processes extracted features
- Classifies movement as **Left / Right / Forward / No Movement**
- Transmits movement command to **ESP32-B via WiFi**

### **3. Rover Control Execution (ESP32-B)**
- Receives **classified command** from ESP32-A
- Drives **motor controller** to execute precise motion
- Ensures **real-time responsiveness** with **sub-100ms latency**

---

## **Inter-Device Communication Architecture**

- **ESP32-A → ESP32-B over WiFi (TCP/UDP)**
- **ESP32-A (Server):** AI classification & command transmission
- **ESP32-B (Client):** Navigation execution & motor control

This **low-latency, embedded AI-driven communication** ensures **high-speed command execution** and **seamless neural navigation**.

---

## **Why MyoPilot Matters: A Step Toward the Future**

MyoPilot represents a **foundational shift** in human-machine interaction. By eliminating the need for handheld controllers, it enables **intelligent, context-aware, and hands-free control systems** applicable in:

- **Astronaut Operations** – Enables hands-free rover and drone control in space.
- **Accessibility & Assistive Tech** – Empowers individuals with limited mobility to operate devices effortlessly.
- **AI-Driven Robotics** – Expands the boundaries of **embedded intelligence** for real-world applications.

This project is a **technological proof of concept** for the next era of control systems.

---

## **Technical Challenges & Innovations**

MyoPilot required significant engineering advancements in **signal processing, embedded AI, and real-time control**:

**High-Noise EMG Signals?** → Developed a **custom filtering pipeline** (bandpass + feature engineering)  
**Low-Power AI Inference?** → Optimized lightweight **AI models** for real-time classification on ESP32  
**Latency Constraints?** → Designed **WiFi-based communication** 
**Fully Embedded Operation?** → Eliminated external computation, ensuring **autonomous execution**  

These breakthroughs position MyoPilot as an extrememly low-cost **approach** to **real-time bioelectric control** in **embedded systems**.

---

## **Why MyoPilot Stands Out at CornHacks 2025**

- **Extreme Technical Depth** – Signal processing, embedded AI, low-latency networking, and real-time motor control.
- **On-Theme Innovation** – Aligned with *CornHacks: A Corn Odyssey*—futuristic control in high-tech environments.
- **Practical, High-Impact Use Cases** – Designed with **real-world applications** in mind, from space missions to assistive robotics.
- **Aesthetic & Functional Excellence** – **Space-inspired, 3D-printed modular design** for competition-ready presentation.
- **Built from Scratch** – No off-the-shelf solutions—**every system, from signal acquisition to motion control, was designed and implemented** by our team.

---

## **Tech Stack**

**Hardware:** ESP32, EMG Electrodes, Servo Motors, Ground Rover Chassis, Magneto Helmet (EMG electrode)  
**Software:** Arduino IDE, Python,  OpenSCAD, Embedded-C
**Networking:** WiFi

---

## **Future Expansions**

MyoPilot is designed to be **highly scalable and modular**. Future developments may include:

- **Aerial Navigation** – Adapting MyoPilot for **drone and exoskeleton control**.
- **Multi-Gesture Control** – Expanding **EMG-based input gestures** for complex interactions.
- **EEG Integration** – Merging **EMG with EEG signals** for **brain-wave based control**.

---

## **Demonstration & Media**

*(Insert images, GIFs, or demo videos of MyoPilot in action!)*

---

## **CornHacks 2025 - Engineering the Future of Human-Machine Interaction**

MyoPilot is a testament to the **fusion of biological intelligence and embedded AI**. It is a **leap** toward a world where technology is not only cost-effective but also **responds to neural intent**, redefining **how we interact with machines**.

**Built by:** *Team Magneto (James Thompson, Collin Glover, Austin Bubak, Priyankka Nanrudaiyan)*  
**CornHacks 2025 | "A Corn Odyssey"** 


