#include "neopixel_utilities.h"
#include "time_utilities.h"
#include "display.h"

void set_alarm(int hours, int minutes, int seconds);

uint32_t alarm_colors[] = {
  pixels.Color(0,0,0),
  pixels.Color(5,0,0),
  pixels.Color(gamma_offset(75), gamma_offset(70), gamma_offset(40)),
  pixels.Color(gamma_offset(250), gamma_offset(250), gamma_offset(255))
};

int alarm_phases = 4;

tmElements_t alarm_time;
int alarm_fade_duration = 60;
float ring_phase_duration = alarm_fade_duration/(float)(NUM_RINGS*alarm_phases);


void alarm_setup(){
  pixel_setup();
  set_alarm(11, 07, 30);
  setup_oled();
}

void alarm_update(){
  tmElements_t current_time = update_time();
  oled_display(current_time);

  int time_diff = seconds_between(alarm_time, current_time);
  
  if(between(time_diff,0, alarm_fade_duration)){
    int current_ring = NUM_RINGS-1-(((int)floor(time_diff/ring_phase_duration))%NUM_RINGS);
    int phase = (int)floor(time_diff/ring_phase_duration)/NUM_RINGS;
    float v =  time_diff - ((floor(time_diff/ring_phase_duration))*ring_phase_duration);
    float lerp_val = v/(float)ring_phase_duration;

    uint32_t col = lerp_color(alarm_colors[phase], alarm_colors[phase+1], lerp_val);
    set_ring(col, current_ring);
  }

}

void set_alarm(int hours, int minutes, int seconds){
  alarm_time.Hour = hours;
  alarm_time.Minute = minutes;
  alarm_time.Second = seconds;
}








