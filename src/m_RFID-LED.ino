/**
 * @file RFID_LED.ino for Analyzer Pod83
 * @author Christian Walter (pauseandplay@cybwalt.de)
 * @brief 
 * @version 1.6.2
 * @date 04.02.2023
 * build with lib_arduino v0.6.2
 */


#include "header_st.h"

#include <stb_common.h>
#include <avr/wdt.h>

#include <stb_brain.h>
#include <stb_servo.h>

STB_BRAIN Brain;


#ifndef ServoDisable 
    STB_SERVO Servos;
#endif


void servoRecieve() {

    while (Brain.STB_.rcvdPtr != NULL) {
        Servos.evaluateCmds(Brain);
        Brain.nextRcvdLn();
    }
}


void setup() {
    Brain.begin();
    Brain.setSlaveAddr(1);
    Brain.dbgln(F("WDT endabled"));
    wdt_enable(WDTO_8S);
    wdt_reset();

    Brain.flags = servoFlag;
}

void loop() {
    //Serial.println(millis());

    if (Brain.slaveRespond()) {
        Serial.println("slave got pushed");
        Serial.println(Brain.STB_.rcvdPtr);
        servoRecieve();
    }    

    wdt_reset();
    
}

