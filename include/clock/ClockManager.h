#ifndef ESPCAM_PROJECT_CLOCKMANAGER_H
#define ESPCAM_PROJECT_CLOCKMANAGER_H

class ClockManager {
public:
  // Constructor
  ClockManager() = default;

  // Métodos públicos
  static void setupClock(const char* timezone);
  static void syncClock();
  static const char* getCurrentDatetimeString();
  static const char* getCurrentDatetimeFile();

  static void waitUntilNextSecond();
  static void waitUntilNext5Seconds();
  static void waitUntilNext10Seconds();
  static void waitUntilNext30Seconds();
  static void waitUntilNextMinute();
  static void waitUntilNext5Minutes();
  static void waitUntilNext10Minutes();
  static void waitUntilNext30Minutes();
  static void waitUntilNextHour();
  static void waitUntilNext2Hours();
  static void waitUntilNext3Hours();
  static void waitUntilNext4Hours();
  static void waitUntilNext6Hours();
  static void waitUntilNext8Hours();
  static void waitUntilNext10Hours();
  static void waitUntilNext12Hours();
  static void waitUntilNext18Hours();
  static void waitUntilNextDay();

private:
  // Método privado auxiliar
  static void waitUntilNext(int interval, int type);
};

#endif //ESPCAM_PROJECT_CLOCKMANAGER_H