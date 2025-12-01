/*

https://learn.adafruit.com/adafruit-updi-friend/enabling-settings-for-the-high-voltage-updi-friend
*/

#define NBR_OF_LED   8
#define NBR_OF_VAL   16
#define NBR_OF_BIT   16
#define NBR_OF_PGM   32

// Port A
#define PORT_A          1
#define PIN_BM_LED_1    (0b00000010)
#define PIN_BM_LED_2    (0b00000100)
#define PIN_BM_LED_3    (0b00001000)
#define PIN_BM_LED_4    (0b00010000)
#define PIN_BM_LED_5    (0b00100000)
#define PIN_BM_LED_6    (0b01000000)
#define PIN_BM_LED_7    (0b10000000)
// Port B
#define PORT_B          2
#define PIN_BM_LED_8    (0b000000100)


const uint8_t ledPin1 = 1;
const uint8_t ledPin2 = 2;
const uint8_t ledPin3 = 3;
const uint8_t ledPin4 = 4;
const uint8_t ledPin5 = 5;
const uint8_t ledPin6 = 6;
const uint8_t ledPin7 = 7;
const uint8_t ledPin8 = 11;



const uint8_t led_bm[NBR_OF_LED] = {PIN_BM_LED_1, PIN_BM_LED_2, PIN_BM_LED_3, PIN_BM_LED_4, PIN_BM_LED_5, PIN_BM_LED_6, PIN_BM_LED_7, PIN_BM_LED_8 };
const uint8_t led_port[NBR_OF_LED] = {PORT_A, PORT_A, PORT_A, PORT_A, PORT_A, PORT_A, PORT_A, PORT_B};

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
  { 1, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 1},
  { 1, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 1},
  { 1, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 1},
  { 1, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 1},
  { 1, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 1},
  { 1, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 1},
  { 1, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 1},
  { 1, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 1},
};

uint8_t  led_pgm_indx[NBR_OF_LED]      = { 0, 0, 0, 0, 0, 0, 0, 0};
uint16_t led_iter_max[NBR_OF_LED]      = { 1000, 423, 332, 220, 411, 299, 2000, 1222,};
uint16_t led_iter[NBR_OF_LED]          = { 3, 4, 5, 6, 7, 8, 9,10,};;


void setup() {
  // for (uint8_t lindex = 0; lindex < NBR_OF_LED; lindex++) pinMode(led_pin[lindex],OUTPUT);
  for (uint8_t i= 0; i < 7; i++) PORTA.DIRSET = led_bm[i];
  PORTB.DIRSET = led_bm[7];
}

uint8_t mask_bit_pos = 0;

void loop() 
{ 
  if (++mask_bit_pos >= NBR_OF_BIT) mask_bit_pos = 0; 
  uint16_t pwm_mask = 1u << mask_bit_pos;

  for (uint8_t lindex = 0; lindex < NBR_OF_LED; lindex++)
  {
      led_iter[lindex]++;
      if (led_iter[lindex] >= led_iter_max[lindex])
      {
        led_iter[lindex] = 0;
        if (led_pgm_indx[lindex] < NBR_OF_PGM - 1) led_pgm_indx[lindex]++;
        else led_pgm_indx[lindex] = 0;
      }
      uint8_t  pgm_indx       = led_pgm_indx[lindex];           // 0..31 -> intensity index
      uint16_t led_mask_indx  = led_intens[lindex][pgm_indx];   // intensity index 0..15
      uint16_t led_mask       = on_pattern[led_mask_indx];      // PWM Mask 16 bit

      if((led_mask & pwm_mask) != 0)
      {
        //digitalWrite(led_pin[lindex], HIGH);
        if (led_port[lindex] ==1) PORTA.OUTSET = led_bm[lindex];
        else PORTB.OUTSET = led_bm[lindex];
      } 
      else 
      {
        // digitalWrite(led_pin[lindex], LOW);
        if (led_port[lindex] ==1) PORTA.OUTCLR = led_bm[lindex];
        else PORTB.OUTCLR = led_bm[lindex];
      }
      //delay(1);
  }
  //delay(10);
  
}
