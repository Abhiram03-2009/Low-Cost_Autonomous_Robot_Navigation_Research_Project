// ===== ESP32 Template Matching (FAST, CLEAN, STABLE) =====
#include "esp_camera.h"
#include <Arduino.h>
#include <pgmspace.h>

// ===== Include Templates =====
#include "red_block.h"
#include "blue_block.h"
#include "yellow_block.h"
#include "green_block.h"
#include "stop_sign1.h"
#include "stop_sign2.h"
#include "left_sign1.h"
#include "left_sign2.h"
#include "right_sign1.h"
#include "right_sign2.h"

// ===== Template Size =====
#define TEMPLATE_WIDTH   32
#define TEMPLATE_HEIGHT  24
#define TEMPLATE_SIZE    (TEMPLATE_WIDTH * TEMPLATE_HEIGHT)

uint8_t smallFrame[TEMPLATE_SIZE];

// ===== Block Color Enum =====
enum BlockColor { RED, BLUE, GREEN, YELLOW, UNKNOWN };

// ===== Camera Pins =====
#define PWDN_GPIO_NUM  -1
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM  15
#define SIOD_GPIO_NUM  4
#define SIOC_GPIO_NUM  5
#define Y2_GPIO_NUM    11
#define Y3_GPIO_NUM    9
#define Y4_GPIO_NUM    8
#define Y5_GPIO_NUM    10
#define Y6_GPIO_NUM    12
#define Y7_GPIO_NUM    18
#define Y8_GPIO_NUM    17
#define Y9_GPIO_NUM    16
#define VSYNC_GPIO_NUM 6
#define HREF_GPIO_NUM  7
#define PCLK_GPIO_NUM  13

// ===== Template Structure =====
struct Template {
  const uint8_t* data;
  const char* name;
  const char* command;
  bool isBlock;
};

Template templates[] = {
  { red_block,    "Red Block",    "AVOID", true  },
  { blue_block,   "Blue Block",   "AVOID", true  },
  { yellow_block, "Yellow Block", "AVOID", true  },
  { green_block,  "Green Block",  "AVOID", true  },
  { stop_sign1,   "Stop Sign",    "STOP",  false },
  { stop_sign2,   "Stop Sign",    "STOP",  false },
  { left_sign1,   "Left Sign",    "LEFT",  false },
  { left_sign2,   "Left Sign",    "LEFT",  false },
  { right_sign1,  "Right Sign",   "RIGHT", false },
  { right_sign2,  "Right Sign",   "RIGHT", false }
};

const int TEMPL_COUNT = sizeof(templates) / sizeof(Template);

// ===== Stability =====
#define STABLE_FRAME_COUNT 5
#define CONFIDENCE_THRESHOLD 0.7
String stableBuf[STABLE_FRAME_COUNT];
int stableIdx = 0;
String lastStable = "";

// ===== Resize =====
void resizeToSmall(const uint8_t* src, int sw, int sh, uint8_t* out) {
  for (int y = 0; y < TEMPLATE_HEIGHT; y++) {
    int sy = (y * sh) / TEMPLATE_HEIGHT;
    for (int x = 0; x < TEMPLATE_WIDTH; x++) {
      int sx = (x * sw) / TEMPLATE_WIDTH;
      out[y * TEMPLATE_WIDTH + x] = src[sy * sw + sx];
    }
  }
}

// ===== SAD =====
long diffSAD(const uint8_t* f, const uint8_t* t, long best) {
  long sum = 0;
  for (int i = 0; i < TEMPLATE_SIZE; i++) {
    sum += abs(f[i] - pgm_read_byte_near(t + i));
    if (sum > best) return sum;
  }
  return sum;
}

bool stable(const String &n) {
  int c = 0;
  for (int i = 0; i < STABLE_FRAME_COUNT; i++)
    if (stableBuf[i] == n) c++;
  return ((float)c / STABLE_FRAME_COUNT) >= CONFIDENCE_THRESHOLD;
}

// ===== Setup =====
void setup() {
  Serial.begin(115200);
  delay(500);

  camera_config_t c;
  c.ledc_channel = LEDC_CHANNEL_0;
  c.ledc_timer = LEDC_TIMER_0;
  c.pin_d0 = Y2_GPIO_NUM;
  c.pin_d1 = Y3_GPIO_NUM;
  c.pin_d2 = Y4_GPIO_NUM;
  c.pin_d3 = Y5_GPIO_NUM;
  c.pin_d4 = Y6_GPIO_NUM;
  c.pin_d5 = Y7_GPIO_NUM;
  c.pin_d6 = Y8_GPIO_NUM;
  c.pin_d7 = Y9_GPIO_NUM;
  c.pin_xclk = XCLK_GPIO_NUM;
  c.pin_pclk = PCLK_GPIO_NUM;
  c.pin_vsync = VSYNC_GPIO_NUM;
  c.pin_href = HREF_GPIO_NUM;
  c.pin_sscb_sda = SIOD_GPIO_NUM;
  c.pin_sscb_scl = SIOC_GPIO_NUM;
  c.pin_pwdn = PWDN_GPIO_NUM;
  c.pin_reset = RESET_GPIO_NUM;
  c.xclk_freq_hz = 20000000;
  c.pixel_format = PIXFORMAT_GRAYSCALE;
  c.frame_size = FRAMESIZE_QVGA;
  c.jpeg_quality = 12;
  c.fb_count = 1;

  if (esp_camera_init(&c) != ESP_OK) {
    Serial.println("Camera FAILED");
    while (1);
  }

  Serial.println("Camera READY");
}

// ===== Loop =====
void loop() {
  camera_fb_t* fb = esp_camera_fb_get();
  if (!fb) return;

  resizeToSmall(fb->buf, fb->width, fb->height, smallFrame);

  long bestDiff = LONG_MAX;
  const char* bestName = "Unknown";
  const char* bestCmd  = "";

  for (int i = 0; i < TEMPL_COUNT; i++) {
    long d = diffSAD(smallFrame, templates[i].data, bestDiff);
    if (d < bestDiff) {
      bestDiff = d;
      bestName = templates[i].name;
      bestCmd  = templates[i].command;
    }
  }

  esp_camera_fb_return(fb);

  stableBuf[stableIdx] = String(bestName);
  stableIdx = (stableIdx + 1) % STABLE_FRAME_COUNT;

  if (stable(bestName) && lastStable != String(bestName)) {
    lastStable = String(bestName);

    Serial.print("CMD:");
    Serial.println(bestCmd);   // <<< THIS IS WHAT ARDUINO READS

    Serial.print("VISION: ");
    Serial.print(bestName);
    Serial.print(" -> ");
    Serial.println(bestCmd);
  }

  delay(10);
}
