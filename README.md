# ❄️ ESP32 Dual AC Controller (Gree & Haier) via Node-RED Dashboard

Proyek ini memungkinkan kontrol **dua unit AC (Gree dan Haier)** menggunakan **ESP32** yang terhubung ke **Node-RED Dashboard** melalui **WebSocket**.  
Sistem ini memungkinkan pengaturan **daya ON/OFF** dan **suhu** untuk kedua AC secara real-time.

---

## 🧩 Arsitektur Sistem



Node-RED Dashboard ↔️ WebSocket ↔️ ESP32 ↔️ IR LED ↔️ Gree & Haier AC


- **Node-RED Dashboard (`2channel.json`)**  
  Mengatur antarmuka web untuk menyalakan/mematikan AC dan mengatur suhu.

- **ESP32 (`main.cpp`)**  
  Menerima data dari Node-RED via WebSocket dan mengirimkan sinyal IR ke AC menggunakan library **IRremoteESP8266**.

- **PlatformIO (`platformio.ini`)**  
  Mengatur dependensi library dan konfigurasi board untuk kompilasi dan upload program ke ESP32.

---

## 📂 Struktur Proyek

| File | Deskripsi |
|------|------------|
| `.gitignore` | Mengabaikan file build dan konfigurasi editor |
| `platformio.ini` | Konfigurasi proyek PlatformIO |
| `main.cpp` | Kode utama ESP32 untuk kontrol dua AC |
| `2channel.json` | Flow Node-RED Dashboard |
| `README.md` | Dokumentasi proyek ini |

---

## ⚙️ Konfigurasi Node-RED

### 1️⃣ Import Flow
1. Buka **Node-RED** di browser (`http://localhost:1880`).
2. Klik **menu → Import → Upload file**, lalu pilih `2channel.json`.
3. Deploy flow tersebut.

### 2️⃣ Fitur Dashboard
Flow ini memiliki kontrol untuk:
- `Gree Power` (Switch)
- `Gree Temp` (Numeric 16–30 °C)
- `Haier Power` (Switch)
- `Haier Temp` (Numeric 16–30 °C)

Node-RED mengirim dan menerima data melalui **WebSocket**:


ws://192.168.223.68:1880/ws


---

## 📡 Program ESP32

### 🔧 Setup WiFi dan WebSocket
File `main.cpp` akan:
- Menghubungkan ESP32 ke jaringan WiFi
- Membuka koneksi WebSocket ke Node-RED di:


ws://192.168.223.21:1880/ac-control

- Menerima payload JSON seperti:
```json
{
  "device_id": "Stand Batik 1",
  "action": "on"
}


atau:

{
  "device_id": "Stand Batik 1",
  "action": "off"
}

🔌 IR Output
AC	Pin IR	Library
Gree	22	IRremoteESP8266
Haier	23	IRremoteESP8266
🧠 Library Dependencies

Ditetapkan di platformio.ini:

lib_deps =
    links2004/WebSockets
    bblanchon/ArduinoJson
    crankyoldgit/IRremoteESP8266

🧾 Cara Menjalankan

Buka folder proyek di PlatformIO.

Pastikan board yang digunakan:

[env:esp32doit-devkit-v1]
platform = espressif32
board = esp32doit-devkit-v1
framework = arduino


Ubah WiFi SSID dan password di main.cpp:

const char* ssid     = "NOC";
const char* password = "noc2023!";


Upload kode ke ESP32.

Jalankan Node-RED dan buka Dashboard.

Kontrol AC langsung dari browser.

🧑‍💻 Pengembang

Radit (itjmp)
ESP32 IoT Developer & Node-RED Enthusiast

Dibuat dengan ❤️ menggunakan ESP32, Node-RED, dan IRremoteESP8266.
Lisensi: MIT License


It seems like I can’t do more advanced data analysis right now. Please try again later.

Namun, kamu masih bisa membuat file README.md ini sendiri dengan mudah:
