/*

https://learn.adafruit.com/adafruit-updi-friend/enabling-settings-for-the-high-voltage-updi-friend
*/

#define NBR_OF_LED   8
#define NBR_OF_VAL   16
#define NBR_OF_BIT   16
#define NBR_OF_PGM   32

const uint8_t ledPin1 = 1;
const uint8_t ledPin2 = 2;
const uint8_t ledPin3 = 3;
const uint8_t ledPin4 = 4;
const uint8_t ledPin5 = 5;
const uint8_t ledPin6 = 6;
const uint8_t ledPin7 = 7;
const uint8_t ledPin8 = 11;

const uint8_t led_pin[NBR_OF_LED] = {1, 2, 3, 4, 5, 6, 7, 11 };
const uint8_t high_of_64[NBR_OF_VAL] = {0,2, 6, 8, 16, 32, 48, 55, 63, 55, 48, 32, 16, 8, 6, 2 };
const uint16_t on_pattern[NBR_OF_VAL] = 
{
  0b0000000000000000,
  0b0000001000000000,
  0b0010000001000000,
  0b0000100001000010,
  0b0101000101010001,
  0b0010010010010001,
  0b0010101001010010,
  0b0101001010101001,
  0b0101010101010101,
  0b0101101010110101,
  0b0110110110110110,
  0b0110110110110111,
  0b1110111101110111,
  0b1111101111011110,
  0b1111101111101111,
  0b1111111111111111,
};

uint8_t led_intens[NBR_OF_LED][NBR_OF_PGM] = 
{
  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
};

uint8_t led_pgm_indx[NBR_OF_LED]  = { 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t led_iter_max[NBR_OF_LED]      = { 3, 4, 5, 6, 7, 8, 9,10,};
uint8_t led_iter_cntr[NBR_OF_LED]      = { 3, 4, 5, 6, 7, 8, 9,10,};


void setup() {
  for (uint8_t lindex = 0; lindex < NBR_OF_LED; lindex++) pinMode(led_pin[lindex],OUTPUT);
}

uint8_t mask_bit_pos;

void loop() 
{ if (++mask_bit_pos >= NBR_OF_BIT) mask_bit_pos = 0; 
  uint16_t pwm_mask = 1u << mask_bit_pos;
  for (uint8_t lindex = 0; lindex < NBR_OF_LED; lindex++)
  {
      uint8_t  led_iter       = led_iter_cntr[lindex];
      led_iter++;
      if (led_iter >= led_iter_max[lindex])
      {
        led_iter = 0;
        if (led_pgm_indx[lindex] < NBR_OF_PGM - 1) led_pgm_indx[lindex]++;
        else led_pgm_indx[lindex] = 0;
      }
      led_iter_cntr[lindex] = led_iter;
      uint8_t  pgm_indx       = led_pgm_indx[lindex];
      uint16_t led_mask_indx  = led_intens[lindex][pgm_indx];
      uint16_t led_mask       = on_pattern[led_mask_indx];

      if(led_mask & pwm_mask) digitalWrite(led_pin[lindex], HIGH);
      else digitalWrite(led_pin[lindex], LOW);
  }
  
}
