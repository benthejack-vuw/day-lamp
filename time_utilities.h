#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>

tmElements_t current_time;

tmElements_t update_time(){
    RTC.read(current_time);
    return current_time;
}

int seconds_between(tmElements_t start_tm, tmElements_t tm){
  int hourDiff = (tm.Hour - start_tm.Hour);
  int minDiff  = (tm.Minute - start_tm.Minute)+hourDiff*60;
  return (tm.Second - start_tm.Second)+minDiff*60;
}

bool between(int value, int mn, int mx){
  return value > mn && value < mx;
}

float time_lerp_val(uint16_t duration, tmElements_t start_tm, tmElements_t tm){
  int secondDiff = seconds_between(start_tm, tm);
  return duration == 0 ? 0 : constrain(secondDiff/(float)duration, 0, 1);
}
