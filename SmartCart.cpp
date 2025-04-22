/*
A simple and interactive Smart Shopping Cart prototype built using Arduino Uno and a 16x2 I2C LCD. This project simulates the core features of a digital shopping cart with a scrolling display, item removal, and transaction summaries — ideal for showcasing embedded system concepts.

👉 [View Tinkercad Simulation](https://www.tinkercad.com/things/hADQ7nsFiRv-smart-shopping-cart?sharecode=bMYbDIbliCjSGcTkfdqCtqB8lmQKEswx1VzvozdCXZA)

Feel Free to Tinker✨
*/
#include <Keypad.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {12, 11, 10, 9};
byte colPins[COLS] = {8, 7, 6, 5};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String currentCode = "";
int total = 0;
int displayIndex = 0;
String itemCodes[20];      // Increased size to accommodate more items (up to 20 items)
String itemQuantities[20]; // Track quantities (as strings)
int itemCount = 0;

// Generate random alphanumeric transaction ID
String generateID() {
  char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  String id = "";
  for (int i = 0; i < 3; i++) {
    id += chars[random(0, strlen(chars))]; // Get a random character
  }
  return id;
}

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Enter Code:");
  lcd.setCursor(0, 1);
  randomSeed(analogRead(0)); // Init random
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.println(key);

    if (key == 'C') {
      lcd.clear();
      lcd.print("Resetting...");
      delay(1000);
      lcd.clear();
      lcd.print("Enter Code:");
      lcd.setCursor(0, 1);
      currentCode = "";
      total = 0;
      itemCount = 0;
      displayIndex = 0;
    }
	
else if (key == 'A') {
  if (itemCount > 0 && itemCodes[displayIndex] != "T" && itemCodes[displayIndex] != "I") {
    String codeToRemove = itemCodes[displayIndex];
    int qty = itemQuantities[displayIndex].toInt();
    int price = getItemPrice(codeToRemove);

    // Subtract price * qty from total
    total -= price * qty;

    // Shift elements up
    for (int i = displayIndex; i < itemCount - 1; i++) {
      itemCodes[i] = itemCodes[i + 1];
      itemQuantities[i] = itemQuantities[i + 1];
    }

    itemCount--;
    if (displayIndex >= itemCount) {
      displayIndex = max(0, itemCount - 2); // Avoid overflow
    }

    lcd.clear();
    lcd.print("Item Removed");
    delay(1000);
    updateLCDList();
  } else {
    lcd.clear();
    lcd.print("Cannot Remove");
    delay(1000);
    updateLCDList();
  }
}

    else if (key == 'B') {
  if (itemCount > 0) {
    displayIndex = (displayIndex + 1) % itemCount;  // Always scroll through items
    updateLCDList();
  }
}

    else if (key == 'D') {
  if (currentCode.length() > 0) {
    currentCode.remove(currentCode.length() - 1);  // remove last char
    lcd.clear();
    lcd.print("Enter Code:");
    lcd.setCursor(0, 1);
    lcd.print(currentCode); // Show updated code after deletion
  }
}


    else if (key == '*') {
      if (itemCount < 20) {
        String id = generateID();
        itemCodes[itemCount] = "T";  // Special code for total
        itemQuantities[itemCount++] = "Total: Rs." + String(total);

        if (itemCount < 20) {
          itemCodes[itemCount] = "I";  // Special code for ID
          itemQuantities[itemCount++] = "Txn ID: " + id; // Store the full ID as a string
        }
      }
      displayIndex = itemCount > 2 ? itemCount - 2 : 0;
      updateLCDList();
    }

    else if (key == '#') {
      int price = getItemPrice(currentCode);
      if (price > 0) {
        bool found = false;
        for (int i = 0; i < itemCount; i++) {
          if (itemCodes[i] == currentCode) {
            itemQuantities[i] = String(itemQuantities[i].toInt() + 1);  // Increase quantity
            found = true;
            break;
          }
        }

        if (!found && itemCount < 20) {
          itemCodes[itemCount] = currentCode;
          itemQuantities[itemCount++] = "1";  // Start with quantity 1
        }

        total += price;
        displayIndex = itemCount > 2 ? itemCount - 2 : 0;
        updateLCDList();
      } else {
        Serial.println("Invalid code or max limit reached");
      }

      currentCode = "";
    }

    else if (isDigit(key)) {
      if (currentCode.length() < 2) {  // Allow two-digit input
        currentCode += key;
      }
    }
  }
}

// --- LCD Display ---
// Update LCD to show items and total
void updateLCDList() {
  lcd.clear();
  for (int i = 0; i < 2; i++) {
    int index = displayIndex + i;
    if (index < itemCount) {
      lcd.setCursor(0, i); // i = 0 -> line 1, i = 1 -> line 2

      if (itemCodes[index] == "T" || itemCodes[index] == "I") {
        lcd.print(itemQuantities[index]);  // For Total or Transaction ID
      } else {
        String name = getItemName(itemCodes[index]);
        String quantity = itemQuantities[index];
        String line = itemCodes[index] + ":" + name + " (" + quantity + ")";
        
        // Truncate if too long for 16 characters
        if (line.length() > 16) {
          line = line.substring(0, 16);
        }

        lcd.print(line);
      }
    }
  }
}



// --- Price Mapping ---
// Updated to handle two-digit and more item codes
int getItemPrice(String code) {
  if (code == "1") return 25;
  else if (code == "2") return 30;
  else if (code == "3") return 45;
  else if (code == "4") return 20;
  else if (code == "5") return 60;
  else if (code == "6") return 15;
  else if (code == "7") return 120;
  else if (code == "8") return 35;
  else if (code == "9") return 80;
  else if (code == "0") return 10;
  else if (code == "10") return 50;  // New code for "10"
  else if (code == "11") return 70;  // New code for "11"
  else if (code == "12") return 90;  // New code for "12"
  else if (code == "13") return 40;  // Amul Milk
  else if (code == "14") return 150; // Britannia Biscuits
  else if (code == "15") return 30;  // Maggi Noodles
  else if (code == "16") return 200; // Parle-G Biscuits
  else if (code == "17") return 100; // Red Label Tea
  else if (code == "18") return 120; // Dabur Honey
  else if (code == "19") return 55;  // Lays Chips
  else if (code == "20") return 90;  // Amul Butter
  else if (code == "21") return 70;  // Nestle Milk
  else if (code == "22") return 110; // Nescafe Coffee
  else if (code == "23") return 180; // Surf Excel
  else if (code == "24") return 40;  // Maggi Masala
  else return 0;  
}

// --- Name Mapping ---
// Updated to handle new item codes
String getItemName(String code) {
  if (code == "1") return "Amul Milk";
  else if (code == "2") return "Modern Bread";
  else if (code == "3") return "Sunshine Eggs";
  else if (code == "4") return "Lays Chips";
  else if (code == "5") return "Dawat Rice";
  else if (code == "6") return "Medimix Soap";
  else if (code == "7") return "Gemini Oil";
  else if (code == "8") return "Sugar";
  else if (code == "9") return "Dove Shampoo";
  else if (code == "0") return "Biscuit";
  else if (code == "10") return "Amul Butter";  // New item for code "10"
  else if (code == "11") return "Amul Cheese";  // New item for code "11"
  else if (code == "12") return "Real Juice";  // New item for code "12"
  else if (code == "13") return "Gokul Milk";
  else if (code == "14") return "Britannia Biscuits";
  else if (code == "15") return "Maggi Noodles";
  else if (code == "16") return "Parle-G Biscuits";
  else if (code == "17") return "Red Label Tea";
  else if (code == "18") return "Dabur Honey";
  else if (code == "19") return "Lays Chips";
  else if (code == "20") return "Amul Butter";
  else if (code == "21") return "Nestle Milk";
  else if (code == "22") return "Nescafe Coffee";
  else if (code == "23") return "Surf Excel";
  else if (code == "24") return "Maggi Masala";
  else return "Unknown";
}
