#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

extern const uint8_t gamma[]; 

#define LED_PIN        8
#define NUM_PIXELS      52
#define NUM_RINGS       3
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
uint8_t rings[] = {24, 16, 12}; //how many pixels per ring

void pixel_setup(){
    pixels.begin(); //This initializes the NeoPixel library.
    pixels.show();
}

uint8_t gamma_offset(uint8_t val){
   return pgm_read_byte(&gamma[val]);
}

uint8_t ring_offset(uint8_t ring){
   uint8_t offset = 0;
   for(uint16_t i=0; i < ring; ++i) offset += rings[i];
   return offset;
}

void set_ring_pixel(uint32_t color, uint8_t ring, uint8_t pixel){
   pixels.setPixelColor(ring_offset(ring)+(pixel%rings[ring]), color);
   pixels.show(); 
}

void set_ring(uint32_t color, uint8_t ring){
   uint8_t offset = ring_offset(ring); 
   for(uint16_t i = offset; i < offset+rings[ring]; ++i)
      pixels.setPixelColor(i, color);
   pixels.show(); 
}

void set_all_pixels(uint32_t c){
  for(uint16_t i=0;i<NUM_PIXELS;i++) pixels.setPixelColor(i, c); 
  pixels.show(); 
}

uint32_t lerp_color(uint32_t c1, uint32_t c2, float val){
  uint8_t r1 = c1>>16&255;   uint8_t r2 = c2>>16&255;
  uint8_t g1 = c1>>8&255;  uint8_t g2 = c2>>8&255;
  uint8_t b1 = c1&255;  uint8_t b2 = c2&255;

  return pixels.Color(r1+(int)((r2-r1)*val), g1+(int)((g2-g1)*val), b1+(int)((b2-b1)*val));
}

























const uint8_t PROGMEM gamma[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };
