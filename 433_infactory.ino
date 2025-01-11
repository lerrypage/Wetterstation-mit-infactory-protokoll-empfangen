
#include "RF433recv.h"
#include <Arduino.h>

//#define PIN_RFINPUT  4   //ESP8266  (D2)
#define PIN_RFINPUT  2  //UNO
    // Specifying the interrupt number is optional, you can leave it to the
    // constructor to work it out.
//#define INT_RFINPUT  0  //UNO 

void callback(const BitVector *recorded) {

    byte my_ID = (recorded->get_nth_byte(4));
    Serial.print(F("ID: "));
    Serial.println (my_ID, HEX);

    int my_CANNEL = (recorded->get_nth_byte(0)) & 0x03;
    Serial.print(F("CH: "));
    Serial.println (my_CANNEL);

    int my_TEMP_RAW = (recorded->get_nth_byte(2) << 4)|(recorded->get_nth_byte(1) >> 4) ;
    float my_TEMP   = (my_TEMP_RAW - 900) * 0.1f;
    my_TEMP = ((my_TEMP  -32)/1.8); //Fahrenheit ->Celsius
    Serial.print(F("TEMP: "));
    Serial.print (my_TEMP,1);
    Serial.println(F(" °C"));

    int my_HUM = (recorded->get_nth_byte(1)& 0x0F)*10 + (recorded->get_nth_byte(0)>> 4) ;
    Serial.print(F("HUM: "));
    Serial.print (my_HUM);
    Serial.println(F(" %"));

    int my_BATT = (recorded->get_nth_byte(3) >> 2) & 1;
    Serial.print(F("BATT: "));
    if (my_BATT == 0){
    Serial.println ("OK");
    }
    else {
       Serial.println ("LOW");
    }


    
    Serial.print(F("Code received: "));
    char *printed_code = recorded->to_str();

    if (printed_code) {
        Serial.print(recorded->get_nb_bits());
        Serial.print(F(" bits: ["));
        Serial.print(printed_code);
        Serial.print(F("]\n"));

        free(printed_code);
    }
}

RF_manager rf(PIN_RFINPUT);

void setup() {
    pinMode(PIN_RFINPUT, INPUT);
    Serial.begin(115200);


        // [inFactory]
    rf.register_Receiver(
        RFMOD_TRIBIT_INVERTED, // mod
        7000,         // initseq
        0,            // lo_prefix
        0,            // hi_prefix
        500,          // first_lo_ign
        500,          // lo_short
        500,          // lo_long
        2000,         // hi_short (0 => take lo_short)
        4000,         // hi_long  (0 => take lo_long)
        0,            // lo_last
        5000,         // sep
        40,           // nb_bits
        callback,
        0
    );

    Serial.print(F("Waiting for signal\n"));

    rf.activate_interrupts_handler();
}

void loop() {
    rf.do_events();
}
