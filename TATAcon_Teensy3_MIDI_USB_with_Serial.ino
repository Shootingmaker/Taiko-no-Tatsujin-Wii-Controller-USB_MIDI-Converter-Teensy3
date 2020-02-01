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


// A/D conveter Setting.
#include <ADC.h>

const int RKATU = A9; // Tennsy3.2  Pin: 23
const int LDON  = A8; // Tennsy3.2  Pin: 22
const int RDON  = A7; // Tennsy3.2  Pin: 21
const int LKATU = A6; // Tennsy3.2  Pin: 20

ADC *adc = new ADC(); // adc object;

unsigned int RKATU_Value = 0; // Senser_Value
unsigned int LDON_Value  = 0; // Senser_Value
unsigned int RDON_Value  = 0; // Senser_Value
unsigned int LKATU_Value = 0; // Senser_Value

unsigned int RKATU_flag = 0; // Senser_Value
unsigned int LDON_flag  = 0; // Senser_Value
unsigned int RDON_flag  = 0; // Senser_Value
unsigned int LKATU_flag = 0; // Senser_Value

// Setting threshold
const int Threshold_Point = 5; // Setting threshold

//MIDI Setting.
#include "MIDIcontroller.h"
byte channel = 12;


void setup() {

    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(RKATU, INPUT);
    pinMode(LKATU, INPUT);
    pinMode(RDON, INPUT);
    pinMode(LDON, INPUT);

    int RKATU_Value = 0;
    int LKATU_Value = 0;
    int RDON_Value  = 0;
    int LDON_Value  = 0;
    
    Serial.begin(9600);
    //MIDI.begin();           // Launch MIDI, by default listening to channel 1.
}

void loop() {
  usbMIDI.sendProgramChange (117,channel);    // MIDI Program Change "TAIKO".
  usbMIDI.sendControlChange (0,0,channel);    // 
  
  // read the analog in value:
  RKATU_Value = 1023 - analogRead(RKATU);
  LKATU_Value = 1023 - analogRead(LKATU);
  RDON_Value  = 1023 - analogRead(RDON);
  LDON_Value  = 1023 - analogRead(LDON);

  RKATU_Value = map (RKATU_Value,0,1023,0,127);
  LKATU_Value = map (LKATU_Value,0,1023,0,127);
  RDON_Value  = map (RDON_Value ,0,1023,0,127);
  LDON_Value  = map (LDON_Value ,0,1023,0,127);  

  // print the results to the Serial Monitor:
  Serial.print(RDON_Value);   Serial.print(",");
  Serial.print(LDON_Value);   Serial.print(",");
  Serial.print(RKATU_Value);  Serial.print(",");
  Serial.print(LKATU_Value);  Serial.print(",");
  Serial.println();

  // Note On messages when each button is pressed
  if (RKATU_Value > Threshold_Point && RKATU_flag == 0) {
    usbMIDI.sendNoteOn(108, RKATU_Value, channel);  // 108 = C8
    RKATU_flag = 1;
  }
  if (LKATU_Value > Threshold_Point && LKATU_flag == 0) {
    usbMIDI.sendNoteOn(107, LKATU_Value, channel);  // 107 = B7
    LKATU_flag = 1; 
  }
  if (RDON_Value > Threshold_Point && RDON_flag == 0) {
    usbMIDI.sendNoteOn(24, RDON_Value, channel);  // 24 = C1
    RDON_flag = 1;
  }
  if (LDON_Value > Threshold_Point && LDON_flag == 0) {
    usbMIDI.sendNoteOn(23, LDON_Value, channel);  // 23 = B0
    LDON_flag = 1;
  }

  
  // Note Off messages when each button is released
  if (RKATU_Value < Threshold_Point) {
    usbMIDI.sendNoteOff(108, 0, channel);  // 108 = C8
    RKATU_flag = 0;
  }
  if (LKATU_Value < Threshold_Point) {
    usbMIDI.sendNoteOff(107, 0, channel);  // 107 = B7
    LKATU_flag = 0;
  }
  if (RDON_Value < Threshold_Point) {
    usbMIDI.sendNoteOff(24, 0, channel);  // 24 = C1
    RDON_flag = 0;
  }
  if (LDON_Value < Threshold_Point) {
    usbMIDI.sendNoteOff(23, 0, channel);  // 23 = B0
    LDON_flag = 0;
  }
  

  // MIDI Controllers should discard incoming MIDI messages.
  while(usbMIDI.read()){}
  

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  //delay(3);
}
