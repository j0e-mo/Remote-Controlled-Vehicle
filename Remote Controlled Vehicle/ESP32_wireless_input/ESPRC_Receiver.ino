#include <esp_now.h>
#include <WiFi.h>

#define DIR_PIN1 14 // D14
#define DIR_PIN2 27 // D27
#define DIR_PIN3 26 // D26
#define SPEED_PIN1 25 // D25
#define SPEED_PIN2 33 // D33
#define SPEED_PIN3 32 // D32

struct JoystickData {
  int16_t x;
  int16_t y;
  uint8_t speed;
};

JoystickData joystickData;

void setup() {
  Serial.begin(115200);

  // Initialize WiFi
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register the receive callback function
  esp_now_register_recv_cb(onDataRecv);

  // Configure AVR pins as output
  pinMode(DIR_PIN1, OUTPUT);
  pinMode(DIR_PIN2, OUTPUT);
  pinMode(DIR_PIN3, OUTPUT);
  pinMode(SPEED_PIN1, OUTPUT);
  pinMode(SPEED_PIN2, OUTPUT);
  pinMode(SPEED_PIN3, OUTPUT);
}

void loop() {
  // Nothing to do here, everything is handled in the callback
}

// Callback function when data is received
void onDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&joystickData, incomingData, sizeof(joystickData));
  sendToAVR();
  Serial.print("Received Data - X: ");
  Serial.print(joystickData.x);
  Serial.print(" Y: ");
  Serial.print(joystickData.y);
  Serial.print(" Speed: ");
  Serial.println(joystickData.speed);
}

// Function to send data to AVR ATmega328P
void sendToAVR() {
  // Set direction pins
  digitalWrite(DIR_PIN1, (joystickData.x > 3000) ? HIGH : LOW);  // Left (swapped)
  digitalWrite(DIR_PIN2, (joystickData.x < 1000) ? HIGH : LOW);  // Right (swapped)
  digitalWrite(DIR_PIN3, (joystickData.y > 3000) ? HIGH : LOW);  // Forward
  digitalWrite(DIR_PIN3, (joystickData.y < 1000) ? HIGH : LOW);  // Backward

  // Set speed pins
  digitalWrite(SPEED_PIN1, (joystickData.speed & 0x01) ? HIGH : LOW);
  digitalWrite(SPEED_PIN2, (joystickData.speed & 0x02) ? HIGH : LOW);
  digitalWrite(SPEED_PIN3, (joystickData.speed & 0x04) ? HIGH : LOW);

  Serial.print("Direction Pins: ");
  Serial.print(digitalRead(DIR_PIN1));
  Serial.print(digitalRead(DIR_PIN2));
  Serial.println(digitalRead(DIR_PIN3));

  Serial.print("Speed Pins: ");
  Serial.print(digitalRead(SPEED_PIN1));
  Serial.print(digitalRead(SPEED_PIN2));
  Serial.println(digitalRead(SPEED_PIN3));
}
