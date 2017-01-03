#ifdef __cplusplus
extern "C" {
#endif

// Each line (8 bytes) is an entire cube, with two consecutive bytes per plane of LEDS,
// and 16 LEDS per plane. LEDs are encoded in the following order:
//    Lowest plane byte 1, lowest plane byte 2, second lowerst plane 1, then 2,
//    second from top plane 1, then 2, highest plane 1, highest plane 2.
//
//    Each plane is encoded looking at the Arduino oriented with the USB/power
//    designated by 'south' by started 'north west' as follows:
//        D0    D1    D2    D3
//        D4    D5    D6    D7
//        D8    D9    D10   D11
//        D12   D13   D14   D15
//
//        D16   D17   D18   D19
//          (USB)      (Power)
//    With D16 being the lowest plane, through to D19 being the highest plane
//    Of course, if you wire the planes up differently, that is up to you!
//
//    Each two bytes of the pattern are therefore:
//        B00000000, B00000000 -> D0-7, D8-15
//    with D0 = msb of the first value, D7 being the lsb of the first value,
//    and  D8 = msb of the second value, D15 being the lsb of the second value.
//
//    So the entire pattern is:
//    B10010000,B00001001,B00000000,B00000000,B00000000,B00000000,B10010000,B00001001,
//     |      |  |     ||                                          |      |  |     ||
//     |      |  |     |\ D15 bottom plane                         |      |  |     |\ D15 top plane
//     |      |  |     \ D14 bottom plane                          |      |  |     \ D14 top plane
//     |      |  \ D8 bottom plane                                 |      |  \ D8 top plane
//     |      \ D7 bottom plane                                    |      \ D7 top plane
//     \ D0 bottom plane                                           \ D0 top plane
//

// Comment following in or out to switch patterns in or out
//#define SWAP   0
//#define SNAKE  0
//#define BURST  0
//#define SPIRAL 0
//#define ALT    0
#define TEST 1

unsigned char pattern[] = {
#ifdef TEST 
  B10000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000,
  B00000000,B00000000, B10000000,B00000000, B00000000,B00000000, B00000000,B00000000,
  B00000000,B00000000, B00000000,B00000000, B10000000,B00000000, B00000000,B00000000,
  B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B10000000,B00000000,
  
  B01000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000,
  B00000000,B00000000, B01000000,B00000000, B00000000,B00000000, B00000000,B00000000,
  B00000000,B00000000, B00000000,B00000000, B01000000,B00000000, B00000000,B00000000,
  B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B01000000,B00000000,
  
  B00100000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000,
  B00000000,B00000000, B00100000,B00000000, B00000000,B00000000, B00000000,B00000000,
  B00000000,B00000000, B00000000,B00000000, B00100000,B00000000, B00000000,B00000000,
  B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00100000,B00000000,
  
  B00010000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000,
  B00000000,B00000000, B00010000,B00000000, B00000000,B00000000, B00000000,B00000000,
  B00000000,B00000000, B00000000,B00000000, B00010000,B00000000, B00000000,B00000000,
  B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00010000,B00000000,
    
  B00000000,B10000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000,
  B00000000,B00000000, B00000000,B10000000, B00000000,B00000000, B00000000,B00000000,
  B00000000,B00000000, B00000000,B00000000, B00000000,B10000000, B00000000,B00000000,
  B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B10000000,
  
  B10000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000,
  B01000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000,
  B00100000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000,
  B00010000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000,
#endif	
#ifdef TEST2 
//L0
  B00000100,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, // D5 on
  B00000100,B01000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, // D9 on
  B00000100,B01100000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, // D10 on
  B00000110,B01100000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, // D6 on
  B00100110,B01100000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, // D2 on
  B01100110,B01100000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, // D1 on
  B11100110,B01100000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, // D0 on
  B11101110,B01100000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, // D4 on
  B11101010,B11100000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, // D8 on, D5 off
  B11101010,B10101000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, // D12 on D9 off
  B11101010,B10001100, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, // D13 on D10 off
  B11101000,B10001110, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, // D14 on D6 off

//L1
  B11001000,B10001110, B00000000,B00000010, B00000000,B00000000, B00000000,B00000000, // D14(L1) on D2(L0) off
  B10001000,B10001110, B00000000,B00000110, B00000000,B00000000, B00000000,B00000000, // D13(L1) on D1(L0) off
  B00001000,B10001110, B00000000,B00001110, B00000000,B00000000, B00000000,B00000000, // D12(L1) on D0(L0) off
  B00000000,B10001110, B00000000,B10001110, B00000000,B00000000, B00000000,B00000000, // D8(L1) on D4(L0) off
  B00000000,B00001110, B00001000,B10001110, B00000000,B00000000, B00000000,B00000000, // D4(L1) on D8(L0) off
  B00000000,B00000110, B10001000,B10001110, B00000000,B00000000, B00000000,B00000000, // D0(L1) on D12(L0) off
  B00000000,B00000010, B11001000,B10001110, B00000000,B00000000, B00000000,B00000000, // D1(L1) on D13(L0) off
  B00000000,B00000000, B11101000,B10001110, B00000000,B00000000, B00000000,B00000000, // D2(L1) on D14(L0) off
  B00000000,B00000000, B11101010,B10001100, B00000000,B00000000, B00000000,B00000000, // D6(L1) on D14(L1) off
  B00000000,B00000000, B11101110,B10001000, B00000000,B00000000, B00000000,B00000000, // D5(L1) on D13(L1) off
  B00000000,B00000000, B11101110,B10000000, B00000100,B00000000, B00000000,B00000000, // D5(L2) on D12(L1) off
  B00000000,B00000000, B11101110,B00000000, B00000100,B00000000, B00000100,B00000000, // D5(L3) on D8(L1) off
  B00000000,B00000000, B11100110,B00000000, B00000100,B00000000, B00000100,B01000000, // D9(L3) on D4(L1) off

  B00000000,B00000000, B01100110,B00000000, B00000100,B01000000, B00000100,B01000000, // D9(L2) on D0(L1) off
  B00000000,B00000000, B00100110,B01000000, B00000100,B01000000, B00000100,B01000000, // D9(L1) on D1(L1) off
  B00000000,B00100000, B00000110,B01000000, B00000100,B01000000, B00000100,B01000000, // D9(L0) on D2(L1) off
  B00000100,B00100000, B00000100,B01000000, B00000100,B01000000, B00000100,B01000000, // D5(L0) on D6(L1) off
  B01000100,B00100000, B00000000,B01000000, B00000100,B01000000, B00000100,B01000000, // D1(L0) on D5(L1) off
  
  B01100100,B01000000, B00000000,B01000000, B00000000,B01000000, B00000100,B01000000, // D2L0 on D5L2 off
  B01110100,B01000000, B00000000,B01000000, B00000000,B01000000, B00000100,B01000000, // D3L0 on D5L3 off
  B01110100,B01000000, B00000000,B01000000, B00000000,B01000000, B00000100,B00000000, // D7L0 on D9L3 off
// 01234567  89012345  
  B01110101,B01010000, B00000000,B01000000, B00000000,B00000000, B00000100,B00000000, // D11L0 on D9L2 off
  B01110101,B01010001, B00000000,B00000000, B00000000,B00000000, B00000100,B00000000, // D15L0 on D9L1 off
  B01110101,B00010001, B00000000,B00000000, B00000000,B00000000, B00000100,B00000000, // D15L1 on D9L0 off
  B01110001,B00010001, B00000000,B00000000, B00000000,B00000001, B00000100,B00000000, // D15L2 on D5L0 off
  
  B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000,
  B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000,
  B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000,
  B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000,
  B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000,
  
#endif  
#ifdef SWAP
  B10010000,B00001001,B00000000,B00000000,B00000000,B00000000,B10010000,B00001001,
  B00000000,B00000000,B10010000,B00001001,B10010000,B00001001,B00000000,B00000000,
  B00000000,B00000000,B01100000,B00000110,B01100000,B00000110,B00000000,B00000000,
  B01100000,B00000110,B00000000,B00000000,B00000000,B00000000,B01100000,B00000110,
  B00001001,B10010000,B00000000,B00000000,B00000000,B00000000,B00001001,B10010000,
  B00000000,B00000000,B00001001,B10010000,B00001001,B10010000,B00000000,B00000000,
  B00000000,B00000000,B00000110,B01100000,B00000110,B01100000,B00000000,B00000000,
  B00000110,B01100000,B00000000,B00000000,B00000000,B00000000,B00000110,B01100000,
#endif
#ifdef SNAKE
  B11001100,B00000000,B11001100,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B11001100,B00000000,B11001100,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B11001100,B00000000,B11001100,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00001100,B11000000,B00001100,B11000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B11001100,B00000000,B11001100,
  B00000000,B00000000,B00000000,B00000000,B00000000,B01100110,B00000000,B01100110,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00110011,B00000000,B00110011,
  B00000000,B00000000,B00000000,B00110011,B00000000,B00110011,B00000000,B00000000,
  B00000000,B00110011,B00000000,B00110011,B00000000,B00000000,B00000000,B00000000,
  B00000011,B00110000,B00000011,B00110000,B00000000,B00000000,B00000000,B00000000,
  B00110011,B00000000,B00110011,B00000000,B00000000,B00000000,B00000000,B00000000,
  B01100110,B00000000,B01100110,B00000000,B00000000,B00000000,B00000000,B00000000,
#endif
#ifdef BURST
  B00000000,B00000000,B00000110,B01100000,B00000110,B01100000,B00000000,B00000000,
  B00000110,B01100000,B01101001,B10010110,B01101001,B10010110,B00000110,B01100000,
  B01101001,B10010110,B10010000,B00001001,B10010000,B00001001,B01101001,B10010110,
  B10010000,B00001001,B00000000,B00000000,B00000000,B00000000,B10010000,B00001001,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
#endif
#ifdef SPIRAL
  B11001100,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B01100110,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00110011,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000011,B00110000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00110011,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B01100110,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B11001100,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00001100,B11000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B11001100,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B11001100,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B01100110,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00110011,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000011,B00110000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00110011,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B01100110,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B11001100,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00001100,B11000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B11001100,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B11001100,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B01100110,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00110011,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000011,B00110000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00110011,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B01100110,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B11001100,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00001100,B11000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B11001100,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B11001100,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B01100110,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00110011,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000011,B00110000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00110011,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B01100110,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B11001100,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00001100,B11000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B11001100,B00000000,
#endif
#ifdef ALT
  B11111001,B10011111,B10010000,B00001001,B10010000,B00001001,B11111001,B10011111,
  B00000110,B01100000,B01101001,B10010110,B01101001,B10010110,B00000110,B01100000,
  B00000000,B00000000,B00000110,B01100000,B00000110,B01100000,B00000000,B00000000,
  B00000110,B01100000,B01101001,B10010110,B01101001,B10010110,B00000110,B01100000,
#endif

}

#ifdef __cplusplus
}
#endif

