#  Smart Shopping Cart - Arduino Mini Project

A simple and interactive Smart Shopping Cart prototype built using Arduino Uno and a 16x2 I2C LCD. This project simulates the core features of a digital shopping cart with a scrolling display, item removal, and transaction summaries — ideal for showcasing embedded system concepts.

👉 [View Tinkercad Simulation](https://www.tinkercad.com/things/hADQ7nsFiRv-smart-shopping-cart?sharecode=bMYbDIbliCjSGcTkfdqCtqB8lmQKEswx1VzvozdCXZA)

---

##  Description

This project mimics a digital shopping cart where a user can:

- View items they've "added" to their cart.
- Scroll through each item using a button.
- Remove items if needed.
- See total price and transaction ID entries in the same list.

All actions are shown in a 2-line LCD display. The interface is intuitive, button-driven, and demonstrates how a minimal UI can be built with Arduino.

---

## Features

-  **I2C 16x2 LCD**: Uses only 2 Arduino pins (A4, A5) for display.
-  **Scroll Through Items**: Press a button to cycle through cart items.
-  **Circular Navigation**: Reaches end? Goes back to start automatically.
-  **Delete Items**: Remove any item using a dedicated delete button.
-  **Item Name Display**: Shows item code, name, and quantity together.
-  **Truncation + Auto Formatting**: Items that don't fit the screen are smartly handled.
-  **Special Item Support**: Recognizes `T` for total and `I` for transaction ID display.
-  **Modular Code**: Easy to extend or customize.

---

##  How to Use

###  Hardware Setup

- Arduino Uno
- I2C 16x2 LCD
- 2 Pushbuttons:
  - `A` Button: Scroll to the next item
  - `0` Button: Delete the currently displayed item
- Breadboard + Jumper Wires
- Resistors (10kΩ) for pull-downs

> **Pin Mapping** (changeable in code)
- `A` button → Digital Pin 2
- `0` button → Digital Pin 3
- I2C LCD → A4 (SDA), A5 (SCL)

###  Functional Controls

| Button | Function                           |
|--------|------------------------------------|
| A      | Scrolls to the next item in the list |
| 0      | Deletes the currently displayed item |

---

##  Example Display Output

1:Milk (2) 
2:Bread (1)
Total: Rs 55
Txn ID: 5ZF
---

##  Test It Online

You can test this full project on Tinkercad without any hardware. Use the simulation, click buttons, and observe the LCD output.

🔗 [Try Simulation Now](https://www.tinkercad.com/things/hADQ7nsFiRv-smart-shopping-cart?sharecode=bMYbDIbliCjSGcTkfdqCtqB8lmQKEswx1VzvozdCXZA)

---

##  Future Ideas

- Add a buzzer or LED feedback when an item is deleted
- Auto-total calculation logic
- Add RFID item scanning simulation
- Store transaction history in EEPROM

---

## Author

Made with ❤️ by Mansi Wanjale  
B.Tech CSE @ Cummins College of Engineering, Pune

---

##  License

MIT License – feel free to fork and build upon!
