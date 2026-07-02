#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define SENSOR_PIN    13  
#define BUZZER_PIN    23  
#define LED_GREEN     26  
#define LED_RED       27  
#define DHTPIN        4     
#define DHTTYPE       DHT11 

DHT dht(DHTPIN, DHTTYPE);

int hours = 12;
int minutes = 30;
int seconds = 0;

int breachCount = 0;
unsigned long lastTimeUpdate = 0;
unsigned long lastDisplayToggle = 0;
unsigned long cooldownTimer = 0;
bool showClockPage = true; 
bool inCooldown = false;

void setup() {
  pinMode(SENSOR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  dht.begin();

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    for(;;); 
  }
  display.clearDisplay();
}

void loop() {
  if (millis() - lastTimeUpdate >= 1000) {
    lastTimeUpdate = millis();
    seconds++;
    if (seconds >= 60) { seconds = 0; minutes++; }
    if (minutes >= 60) { minutes = 0; hours++; }
    if (hours >= 24)   { hours = 0; }
  }

  if (inCooldown && (millis() - cooldownTimer >= 2000)) {
    inCooldown = false;
  }

  int ir_tripped = digitalRead(SENSOR_PIN);

  if (ir_tripped == LOW && !inCooldown) {
    breachCount++;
    inCooldown = true;
    cooldownTimer = millis();
    
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, HIGH);
    
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(20, 10);
    display.print("BREACH!");
    
    display.setTextSize(1);
    display.setCursor(20, 45);
    display.print("Total Alerts: ");
    display.print(breachCount);
    display.display();
    
    for (int i = 0; i < 3; i++) {
      digitalWrite(BUZZER_PIN, HIGH);
      delay(150);
      digitalWrite(BUZZER_PIN, LOW);
      delay(150);
    }
    
  } else if (!inCooldown) {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, LOW);
    
    if (millis() - lastDisplayToggle >= 3000) {
      lastDisplayToggle = millis();
      showClockPage = !showClockPage; 
    }

    display.clearDisplay();
    display.setTextColor(WHITE);
    
    display.setTextSize(1);
    display.setCursor(15, 0);
    display.print("SAFESPACE ACTIVE");
    display.drawFastHLine(0, 10, 128, WHITE);
    
    if (showClockPage) {
      display.setTextSize(2);
      display.setCursor(20, 25);
      if(hours < 10) display.print("0");
      display.print(hours); display.print(":");
      if(minutes < 10) display.print("0");
      display.print(minutes); display.print(":");
      if(seconds < 10) display.print("0");
      display.print(seconds);
    } else {
      float temp = dht.readTemperature();
      float humid = dht.readHumidity();

      display.setTextSize(1);
      display.setCursor(10, 22);
      display.print("Temp: "); 
      display.print(isnan(temp) ? 0.0 : temp, 1); display.print(" C");
      
      display.setCursor(10, 40);
      display.print("Humidity: "); 
      display.print(isnan(humid) ? 0.0 : humid, 1); display.print(" %");
    }
    
    display.setTextSize(1);
    display.setCursor(0, 55);
    display.print("Alerts Logged: ");
    display.print(breachCount);
    
    display.display();
  }
  
  delay(10);
}