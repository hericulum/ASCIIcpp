# C++ ASCII Art Generator

A high-fidelity, command-line C++ application that converts any standard image into detailed text-based ASCII art using the SFML library. Designed with block-averaging downscaling and perceptual grayscale mapping to produce clean, recognizable results—especially for portraits.

---

## 🚀 Features

* **SFML Integration:** Fast and reliable image loading and pixel sampling.
* **Block-Averaging Downscaling:** Pools pixel clusters together to act as an anti-aliasing filter, smoothing out noise and preserving image integrity.
* **Aspect Ratio Correction:** Automatically scales vertical grid dimensions to compensate for rectangular terminal font proportions.
* **70-Character Grayscale Palette:** Utilizes a smooth density gradient for deep tonal contrast.
* **File Export Stream:** Outputs directly to `output.txt`, bypassing standard terminal character wrapping and size restrictions for massive, high-resolution text art.

---

## 🛠️ Prerequisites & Dependencies

To compile and run this project, you will need:
* A modern C++ compiler supporting C++11 or later (`g++`, `clang++`, or MSVC).
* The **SFML** (Simple and Fast Multimedia Library) installed on your system.

### Installing SFML (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install libsfml-dev
```

---

## ⚙️ Getting Started

### 1. Clone the Repository
```bash
git clone https://github.com/YOUR_USERNAME/YOUR_REPOSITORY_NAME.git
cd YOUR_REPOSITORY_NAME
```

### 2. Add a Source Image
Place your target image in the root project directory and name it **`image.jpg`** (or modify the filename in `main.cpp` to match your image file).

### 3. Compile the Code
Run the following compilation command in your terminal (linking the necessary SFML modules):
```bash
g++ main.cpp -o ascii_generator -lsfml-graphics -lsfml-window -lsfml-system
```

### 4. Run the Program
```bash
./ascii_generator
```
Once executed successfully, look for the newly generated **`output.txt`** file in your directory.

---

## 💡 How to View the Output
Because text editors often wrap long lines by default, follow these steps for the best viewing experience:
1. Open `output.txt` in **VS Code**.
2. Turn off word wrap (`Alt + Z` or `View > Toggle Word Wrap`).
3. Zoom out (`Ctrl + -` / `Cmd + -`) to let your eyes blend the characters into a sharp photographic image. Alternatively, drag and drop `output.txt` directly into any web browser.

---

## 🧠 Core Algorithm Overview
1. **Load & Read:** Loads the image file and retrieves its native dimensions (`origWidth`, `origHeight`).
2. **Downscale Math:** Computes scaling ratios to map a high-resolution pixel space down to a compact text grid (`targetWidth`, `targetHeight`).
3. **Block Averaging:** Averages every sub-pixel cluster's luminance using the perceptual grayscale formula:
   $$\text{Gray} = 0.299R + 0.587G + 0.114B$$
4. **Quantization:** Normalizes the average brightness ($0–255$) and maps it proportionally to