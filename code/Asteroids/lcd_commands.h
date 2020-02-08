#define DISPLAY_OFF       0b10101110
#define DISPLAY_ON        0b10101111
#define SET_STARTLINE     0b01000000  //last 6 bits are display start address
#define SET_PAGE_ADDR     0b10110000  //last 4 bits are page address
#define UPPER_COL_ADDR    0b00010000  //last 4 bits are MS column address
#define LOWER_COL_ADDR    0b00000000  //last 4 bits are LS column address
#define ADC_NORMAL        0b10100000
#define ADC_REVERSE       0b10100001
#define DISPLAY_NORMAL    0b10100110
#define DISPLAY_REVERSE   0b10100111
#define DISPLAY_ALL_OFF   0b10100100
#define DISPLAY_ALL_ON    0b10100101
#define LCD_BIAS_NINTH    0b10100010
#define LCD_BIAS_SEVENTH  0b10100011
#define INTERNAL_RESET    0b11100010
#define COM_OUTPUT_NORM   0b11000000  //don't care about last 3 bits
#define COM_OUTPUT_REV    0b11001000
#define POWER_MODE_SET    0b00101000  //last 3 bits are mode
#define RESISTOR_RATIO    0b00100000  //last 3 bits are resistor ratio
#define ELEC_VOL_MODE     0b10000001
#define ELEC_VOL_SET      0b00000000  //last 6 bits are electronic volume
