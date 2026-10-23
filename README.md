
# PassHub 🚀

**PassHub** is a custom password auditor and secure credential management tool built using **C** and **HTML/CSS**. It bridges a console-based application with interactive web dashboards, allowing users to evaluate password strength, receive secure alternatives, manage a persistent credential vault, and instantly view visual security reports.

---

## ✨ Key Features

* **Secure Terminal Input:** Implements real-time character masking (`*`) while typing in the console to keep sensitive credentials private.
* **Intelligent Password Analysis:** Evaluates password complexity and automatically suggests strong, randomized alternatives when input falls below security thresholds.
* **Persistent Vault Storage:** Utilizes robust file handling to securely store and append new credentials without overwriting previously saved data.
* **Lightweight Obfuscation:** Incorporates a character-shifting mechanism to protect stored passwords within the local data file.
* **Interactive HTML Dashboards:** Automatically generates clean, CSS-styled web pages (`security_dashboard.html` and `stored_passwords.html`) to present audit reports and stored credentials in a professional, user-friendly format.

---

## 🛠️ Tech Stack & Concepts

* **Programming Language:** C
* **Frontend Output:** HTML5 & CSS3
* **Concepts Applied:** 
  * File I/O (`fopen`, `fprintf`, `fgets`, `fclose`)
  * String Manipulation & Parsing (`sscanf`, `strlen`, `strcpy`)
  * Console Utilities (`conio.h` for `getch()`, random generation via `time.h`)
  * Dynamic File Generation (CLI to Web integration)

---

## 🚀 How to Run the Project

1. **Prerequisites:** 
   * A C compiler (such as GCC, MinGW, or Code::Blocks).
   * *Note: This project utilizes `<conio.h>` and Windows-specific system calls (`system("start ...")`), so it is best run on a Windows environment.*
2. **Clone or Download** the repository to your local machine.
3. **Compile the Code:**
   Open your terminal or IDE and compile `main.c`:
   
   gcc main.c -o passhub



4. **Run the Executable:**

./passhub.exe




5. Follow the interactive console prompts to enter account details, review your security score, and check your generated web dashboards automatically!

---

## 📁 Generated Files

When you run the application, it dynamically manages the following files in your directory:

* `vault_data.txt` — Stores your encrypted credential records.
* `security_dashboard.html` — Displays the real-time password audit and strength meter.
* `stored_passwords.html` — Displays your saved credential vault in a clean table format.

---

## 💡 Acknowledgement

Developed as a practical project exploring the integration of low-level C programming logic with clean, modern web views. Feedback and contributions are always welcome!

---

## 👤 Author

**Safwath Jannat Labiba**

Undergraduate Student

Department of Computer Science and Engineering (CSE)

Rajshahi University of Engineering & Technology (RUET)

