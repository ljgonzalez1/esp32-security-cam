#include <Arduino.h>
#include <time.h>
#include <cstring>
#include "clock/ClockManager.h"

void setup_clock(const char *timezone) {
  Serial.printf("Setting timezone to %s\n", timezone);
  setenv("TZ", timezone, 1);
  tzset();
  sync_clock();
}

void sync_clock() {
  Serial.println("Syncing time...");
  configTime(0, 0, "pool.ntp.org");
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.printf("Time synced: %04d-%02d-%02d %02d:%02d:%02d\n",
                timeinfo.tm_year + 1900,
                timeinfo.tm_mon + 1,
                timeinfo.tm_mday,
                timeinfo.tm_hour,
                timeinfo.tm_min,
                timeinfo.tm_sec);
}

char* get_current_datetime_string() {
  static char buffer[64];
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    strncpy(buffer, "Failed to obtain time", sizeof(buffer) - 1);
    return buffer;
  }
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
  return buffer;
}

char* get_current_datetime_file() {
  static char buffer[64];
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    strncpy(buffer, "Failed to obtain time", sizeof(buffer) - 1);
    return buffer;
  }
  strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H.%M.%S", &timeinfo);
  return buffer;
}

void wait_until_next(int interval, int type) {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }

  int target;
  switch (type) {
    case 0: // Seconds
      target = (timeinfo.tm_sec / interval + 1) * interval;
      if (target >= 60) target = 0;
      while (timeinfo.tm_sec != target) {
        delay(100);
        getLocalTime(&timeinfo);
      }
      break;
    case 1: // Minutes
      target = (timeinfo.tm_min / interval + 1) * interval;
      if (target >= 60) target = 0;
      while (timeinfo.tm_min != target) {
        delay(1000);
        getLocalTime(&timeinfo);
      }
      break;
    case 2: // Hours
      target = (timeinfo.tm_hour / interval + 1) * interval;
      if (target >= 24) target = 0;
      while (timeinfo.tm_hour != target) {
        delay(60000);
        getLocalTime(&timeinfo);
      }
      break;
  }
}

void wait_until_next_second() {
  wait_until_next(1, 0);
}

void wait_until_next_5_seconds() {
  wait_until_next(5, 0);
}

void wait_until_next_10_seconds() {
  wait_until_next(10, 0);
}

void wait_until_next_30_seconds() {
  wait_until_next(30, 0);
}

void wait_until_next_minute() {
  wait_until_next(1, 1);
}

void wait_until_next_5_minutes() {
  wait_until_next(5, 1);
}

void wait_until_next_10_minutes() {
  wait_until_next(10, 1);
}

void wait_until_next_30_minutes() {
  wait_until_next(30, 1);
}

void wait_until_next_hour() {
  wait_until_next(1, 2);
}

void wait_until_next_2_hours() {
  wait_until_next(2, 2);
}

void wait_until_next_3_hours() {
  wait_until_next(3, 2);
}

void wait_until_next_4_hours() {
  wait_until_next(4, 2);
}

void wait_until_next_6_hours() {
  wait_until_next(6, 2);
}

void wait_until_next_8_hours() {
  wait_until_next(8, 2);
}

void wait_until_next_10_hours() {
  wait_until_next(10, 2);
}

void wait_until_next_12_hours() {
  wait_until_next(12, 2);
}

void wait_until_next_18_hours() {
  wait_until_next(18, 2);
}

void wait_until_next_day() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  while (timeinfo.tm_hour != 0 || timeinfo.tm_min != 0 || timeinfo.tm_sec != 0) {
    delay(1000);
    getLocalTime(&timeinfo);
  }
}
