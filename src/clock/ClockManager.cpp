#include <Arduino.h>
#include <time.h>
#include <cstring>
#include "clock/ClockManager.h"

void ClockManager::setupClock(const char* timezone) {
  Serial.printf("Setting timezone to %s\n", timezone);
  setenv("TZ", timezone, 1);
  tzset();
  syncClock();
}

void ClockManager::syncClock() {
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

const char* ClockManager::getCurrentDatetimeString() {
  static char buffer[64];
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    strncpy(buffer, "Failed to obtain time", sizeof(buffer) - 1);
    return buffer;
  }
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
  return buffer;
}

const char* ClockManager::getCurrentDatetimeFile() {
  static char buffer[64];
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    strncpy(buffer, "Failed to obtain time", sizeof(buffer) - 1);
    return buffer;
  }
  strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H.%M.%S", &timeinfo);
  return buffer;
}

void ClockManager::waitUntilNext(int interval, int type) {
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

void ClockManager::waitUntilNextSecond() {
  waitUntilNext(1, 0);
}

void ClockManager::waitUntilNext5Seconds() {
  waitUntilNext(5, 0);
}

void ClockManager::waitUntilNext10Seconds() {
  waitUntilNext(10, 0);
}

void ClockManager::waitUntilNext30Seconds() {
  waitUntilNext(30, 0);
}

void ClockManager::waitUntilNextMinute() {
  waitUntilNext(1, 1);
}

void ClockManager::waitUntilNext5Minutes() {
  waitUntilNext(5, 1);
}

void ClockManager::waitUntilNext10Minutes() {
  waitUntilNext(10, 1);
}

void ClockManager::waitUntilNext30Minutes() {
  waitUntilNext(30, 1);
}

void ClockManager::waitUntilNextHour() {
  waitUntilNext(1, 2);
}

void ClockManager::waitUntilNext2Hours() {
  waitUntilNext(2, 2);
}

void ClockManager::waitUntilNext3Hours() {
  waitUntilNext(3, 2);
}

void ClockManager::waitUntilNext4Hours() {
  waitUntilNext(4, 2);
}

void ClockManager::waitUntilNext6Hours() {
  waitUntilNext(6, 2);
}

void ClockManager::waitUntilNext8Hours() {
  waitUntilNext(8, 2);
}

void ClockManager::waitUntilNext10Hours() {
  waitUntilNext(10, 2);
}

void ClockManager::waitUntilNext12Hours() {
  waitUntilNext(12, 2);
}

void ClockManager::waitUntilNext18Hours() {
  waitUntilNext(18, 2);
}

void ClockManager::waitUntilNextDay() {
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
