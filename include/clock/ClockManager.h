#ifndef ESPCAM_PROJECT_CLOCKMANAGER_H
#define ESPCAM_PROJECT_CLOCKMANAGER_H

void setup_clock(const char *timezone);
void sync_clock();
char* get_current_datetime_string();
char* get_current_datetime_file();

void wait_until_next_second();

void wait_until_next_5_seconds();
void wait_until_next_10_seconds();
void wait_until_next_30_seconds();

void wait_until_next_minute();
void wait_until_next_5_minutes();
void wait_until_next_10_minutes();
void wait_until_next_30_minutes();

void wait_until_next_hour();
void wait_until_next_2_hours();
void wait_until_next_3_hours();
void wait_until_next_4_hours();
void wait_until_next_6_hours();
void wait_until_next_8_hours();
void wait_until_next_10_hours();
void wait_until_next_12_hours();
void wait_until_next_18_hours();

void wait_until_next_day();

#endif //ESPCAM_PROJECT_CLOCKMANAGER_H
