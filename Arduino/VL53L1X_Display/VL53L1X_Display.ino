#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include <lgfx/v1/platforms/esp32s3/Panel_RGB.hpp>
#include <lgfx/v1/platforms/esp32s3/Bus_RGB.hpp>
#include <Wire.h>
#include <TCA9534.h>
#include <Adafruit_VL53L1X.h>


class LGFX : public lgfx::LGFX_Device {
public:
  lgfx::Bus_RGB   _bus_instance;
  lgfx::Panel_RGB _panel_instance;

  LGFX(void) {
    {
      auto cfg = _panel_instance.config();
      cfg.memory_width  = 800;
      cfg.memory_height = 480;
      cfg.panel_width   = 800;
      cfg.panel_height  = 480;
      cfg.offset_x = 0;
      cfg.offset_y = 0;
      _panel_instance.config(cfg);
    }
    {
      auto cfg = _panel_instance.config_detail();
      cfg.use_psram = 1;
      _panel_instance.config_detail(cfg);
    }
    {
      auto cfg = _bus_instance.config();
      cfg.panel       = &_panel_instance;
      cfg.pin_d0      = GPIO_NUM_8;
      cfg.pin_d1      = GPIO_NUM_3;
      cfg.pin_d2      = GPIO_NUM_46;
      cfg.pin_d3      = GPIO_NUM_9;
      cfg.pin_d4      = GPIO_NUM_1;
      cfg.pin_d5      = GPIO_NUM_5;
      cfg.pin_d6      = GPIO_NUM_6;
      cfg.pin_d7      = GPIO_NUM_7;
      cfg.pin_d8      = GPIO_NUM_15;
      cfg.pin_d9      = GPIO_NUM_16;
      cfg.pin_d10     = GPIO_NUM_4;
      cfg.pin_d11     = GPIO_NUM_45;
      cfg.pin_d12     = GPIO_NUM_48;
      cfg.pin_d13     = GPIO_NUM_47;
      cfg.pin_d14     = GPIO_NUM_21;
      cfg.pin_d15     = GPIO_NUM_14;
      cfg.pin_henable = GPIO_NUM_42;
      cfg.pin_vsync   = GPIO_NUM_41;
      cfg.pin_hsync   = GPIO_NUM_40;
      cfg.pin_pclk    = GPIO_NUM_39;
      cfg.freq_write  = 15000000;
      cfg.hsync_polarity    = 0;
      cfg.hsync_front_porch = 8;
      cfg.hsync_pulse_width = 4;
      cfg.hsync_back_porch  = 43;
      cfg.vsync_polarity    = 0;
      cfg.vsync_front_porch = 8;
      cfg.vsync_pulse_width = 4;
      cfg.vsync_back_porch  = 12;
      cfg.pclk_active_neg   = 1;
      cfg.de_idle_high      = 0;
      cfg.pclk_idle_high    = 0;
      _bus_instance.config(cfg);
      _panel_instance.setBus(&_bus_instance);
    }
    setPanel(&_panel_instance);
  }
};

LGFX lcd;
TCA9534 ioex;
Adafruit_VL53L1X vl53 = Adafruit_VL53L1X();

void setup() {
  esp_log_level_set("gpio", ESP_LOG_NONE);
  Serial.begin(115200);
  delay(1000);
  Serial.println("Starting...");

  // Step 1: TCA9534 loop on Wire (19/20) — makes lcd.init() work
  Wire.begin(19, 20);
  delay(100);
  uint8_t addresses[] = {0x18, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
                         0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F};
  for (uint8_t i = 0; i < sizeof(addresses); i++) {
    ioex.attach(Wire);
    ioex.setDeviceAddress(addresses[i]);
    ioex.config(1, TCA9534::Config::OUT);
    ioex.output(1, TCA9534::Level::H);
    delay(300);
  }
  Serial.println("TCA9534 loop done");

  // Step 2: init display
  Serial.println("Calling lcd.init()...");
  lcd.init();
  Serial.println("lcd.init() done!");
  lcd.setRotation(0);
  lcd.fillScreen(TFT_BLACK);
  lcd.setTextColor(TFT_WHITE);
  lcd.setTextSize(2);
  lcd.drawString("Finding sensor...", 20, 20);

  // Step 3: re-init Wire1 fresh right before sensor init
  // TCA9534 library corrupts bus state — this resets it
  Wire1.begin(15, 16);
  delay(1000);
  Serial.println("Wire1 re-init done");

  // Step 4: init sensor
  Serial.println("Calling vl53.begin()...");
  if (!vl53.begin(0x29, &Wire1)) {
    lcd.fillScreen(TFT_BLACK);
    lcd.drawString("SENSOR NOT FOUND", 20, 200);
    Serial.println("Sensor not found!");
    while (1) delay(10);
  }
  Serial.println("Sensor found!");

  if (!vl53.startRanging()) {
    lcd.drawString("RANGING FAILED", 20, 240);
    Serial.println("startRanging failed!");
    while (1) delay(10);
  }
  Serial.println("Ranging started!");
  vl53.setTimingBudget(50);

  lcd.fillScreen(TFT_BLACK);
  lcd.setTextSize(2);
  lcd.drawString("VL53L1X Distance Sensor", 20, 20);
  Serial.println("Setup complete!");
}

void loop() {
  if (vl53.dataReady()) {
    int16_t distance = vl53.distance();
    vl53.clearInterrupt();

    lcd.setTextColor(TFT_WHITE, TFT_BLACK);  // foreground, background

    if (distance == -1) {
      lcd.setTextSize(6);
      lcd.drawString("Out of Range", 20, 100);
      lcd.setTextSize(4);
      lcd.drawString("        ", 20, 220);
      lcd.setTextSize(3);
      lcd.drawString("        ", 20, 310);
    } else {
      lcd.setTextSize(6);
      lcd.drawString(String(distance * 0.001, 3) + " m     ", 20, 100);
      lcd.setTextSize(4);
      lcd.drawString(String(distance * 0.1, 1) + " cm     ", 20, 220);
      lcd.setTextSize(3);
      lcd.drawString(String(distance) + " mm     ", 20, 310);
    }

    Serial.println(distance);
  }
}