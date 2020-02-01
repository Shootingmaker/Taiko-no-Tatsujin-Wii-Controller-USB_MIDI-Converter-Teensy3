# Taiko-no-Tatsujin-Wii-Controller-USB_MIDI-Converter-Teensy3
Taiko-no-Tatsujin-Wii-Controller-USB_MIDI-Converter-Teensy3

// Taiko-no-Tatsujin-Wii-Controller-USB_MIDI-Converter-Teensy3
// TATA-con USB-MIDI Converter 
// Kotohiro Masuda 
// 2020-02-01
//　Ver 1.00 First Release. 
// Test enviroment : Synthetia / Windows10 64bit. 

/* TATA-Con to Teensy3.2 CONNECT.
TP5 --- Tennsy3.2  Pin: 23
TP4 --- Tennsy3.2  Pin: 22
TP3 --- Tennsy3.2  Pin: 21
TP2 --- Tennsy3.2  Pin: 20
and 3.3V and GND.
*/

/* Use in this Library.
  MIDIcontroller
  https://github.com/joshnishikawa/MIDIcontroller

  Teensyduino
  https://www.pjrc.com/teensy/teensyduino.html
*/

/* Compile setting 
  Teensy 3.2 
  72Mhz
  Serial + MIDI or MIDI
*/

// If you USE this setting MIDI channel and Threshold_Point.
