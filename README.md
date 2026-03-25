# SMM_Sensor

Jest to kod do sensora do mojego systemu monitorowania wilgotności gleby roślin doniczkowych. Do wgrania kodu na płytkę potrzebny jest program Arduino IDE.
Do poprawnego działania kodu potrzebne jest zainstalowanie 2 bibliotek. Aby zainstalować wspomniane biblioteki należy w Arduino IDE przejść do zakładki **Szkic**, następnie wybrać **Dołącz bibliotekę** i **Zarządzaj bibliotekami**. Biblioteki konieczne do pobrania to:
1. Adafruit NeoPixel by Adafruit
2. SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library by SparkFun Electronics

Proces instalacji przebiega następująco:
1. Należy podpiąć mikrokontroler do portu USB.
2. Należy wybrać płytkę w Arduino IDE poprzez przejście w **Narzędzia** -> **Płytka** -> **ESP8266 Boards** -> **LOLIN Wemos D1 R2 & mini**
3. Następnie należy wybrać właściwy port COM do którego podpięty jest mikrokontroler
4. Należy wypełnić dane konfiguracyjne, w kodzie oznaczone one są blokiem /////////// CONFIGURATION ///////////
4.1. SENSOR ID - ID sensora, każdy sensor powinien mieć unikalne ID
4.2. WIFI CONFIGURATION - dane dotyczące połączenia wifi oraz adres ip serwera z zainstalowaną aplikacją backendową
4.3. BASIC AUTH DATA - dane logowania ustawiane na serwerze
4.4. TIMING - sendInterval definiuje czas pomiędzy kolejnymi pomiarami i transmisją danych, domyślnie jest ustawiona 1 godzina
4.5. PINS - przypisanie pinów
4.6. LED - konfiguracja diody RGB, NUMPIXELS oznacza ilość diod, LED_BRIGHTNESS oznacza jasność diody (0 - 255)
5. Po zakończonej konfiguracji można wgrać kod za pomocą przycisku **Wgraj** z ikoną strzałki (->)

========================================================================================================================================================================================

This is the sensor code for my potted plant soil moisture monitoring system. To upload the code to the board, you need the Arduino IDE.
To run the code, you must install 2 libraries. In Arduino IDE, go to Sketch → Include Library → Manage Libraries and install:
1. Adafruit NeoPixel by Adafruit
2. SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library by SparkFun Electronics

Installation steps:
1. Connect the microcontroller via USB
2. Select the board: Tools → Board → ESP8266 Boards → LOLIN Wemos D1 R2 & mini
3. Select the correct COM port
4. Fill in the configuration section (marked /////////// CONFIGURATION ///////////):
4.1 SENSOR ID – unique ID for each sensor
4.2 WIFI CONFIGURATION – WiFi credentials and server IP address
4.3 BASIC AUTH DATA – server login credentials
4.4 TIMING – sendInterval sets time between data transmissions (default: 1 hour)
4.5 PINS – pin assignments
4.6 LED – NUMPIXELS (number of LEDs), LED_BRIGHTNESS (0–255)
5. Upload the code using the Upload button (→ icon)   
