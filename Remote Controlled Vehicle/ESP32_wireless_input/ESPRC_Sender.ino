#include <esp_now.h>
#include <WiFi.h>

#define VRX_PIN 34
#define VRY_PIN 35
#define SW_PIN 32

struct JoystickData {
  int16_t x;
  int16_t y;
  uint8_t speed;
};

JoystickData joystickData;
uint8_t speedLevel = 0;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 300; // Increased debounce delay

const uint8_t receiverMAC[] = {0xFC, 0xB4, 0x67, 0xC3, 0x3A, 0x4C};  // Provided MAC address

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

  // Configure joystick pins
  pinMode(VRX_PIN, INPUT);
  pinMode(VRY_PIN, INPUT);
  pinMode(SW_PIN, INPUT_PULLUP);

  // Add peer
  esp_now_peer_info_t peerInfo;
  memset(&peerInfo, 0, sizeof(peerInfo));
  memcpy(peerInfo.peer_addr, receiverMAC, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  // Register the send callback function
  esp_now_register_send_cb(onDataSent);
}

void loop() {
  // Read joystick values
  joystickData.x = analogRead(VRX_PIN);
  joystickData.y = analogRead(VRY_PIN);

  // Apply a simple moving average filter to reduce noise (optional)
  static int16_t x_avg = 0;
  static int16_t y_avg = 0;
  const int alpha = 10;
  x_avg = (x_avg * (alpha - 1) + joystickData.x) / alpha;
  y_avg = (y_avg * (alpha - 1) + joystickData.y) / alpha;
  joystickData.x = x_avg;
  joystickData.y = y_avg;

  // Determine direction
  const char* direction = "Stop";
  if (joystickData.x > 3000) {
    direction = "Left";  // Swapped direction
  } else if (joystickData.x < 1000) {
    direction = "Right";  // Swapped direction
  } else if (joystickData.y > 3000) {
    direction = "Forward";
  } else if (joystickData.y < 1000) {
    direction = "Backward";
  }

  // Print direction
  Serial.print("Direction: ");
  Serial.println(direction);

  // Check for button press to change speed
  if (digitalRead(SW_PIN) == LOW) {
    unsigned long currentTime = millis();
    if ((currentTime - lastDebounceTime) > debounceDelay) {
      speedLevel = (speedLevel + 1) % 6;  // Cycle through speed levels 0 to 5
      joystickData.speed = speedLevel;
      lastDebounceTime = currentTime;
      Serial.print("Speed Level: ");
      Serial.println(speedLevel);
    }
  }

  // Send data
  esp_err_t result = esp_now_send(receiverMAC, (uint8_t *) &joystickData, sizeof(joystickData));

  if (result == ESP_OK) {
    Serial.println("Sent with success");
  } else {
    Serial.println("Error sending the data");
  }

  delay(100);  // Adjust delay as needed
}

void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Last Packet Send Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
