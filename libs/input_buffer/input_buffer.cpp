#include <Arduino.h>
#include "input_buffer.h"

String inputBuffer(bool allowBlankInput, bool sensitiveInfo) {
    String bufferedInput = "";
    while (true) {
        if (Serial0.available() > 0) {
            char ch = Serial0.read(); // save every single character in each iteration
            // when ch is the enter key
            if (ch == '\r' || ch == '\n') {
                // Serial0.println();
                // return bufferedInput;
                if (allowBlankInput || bufferedInput.length() > 0) {
                    Serial0.println();
                    return bufferedInput;
                }
            }
            // when ch is the backspace key
            else if (ch == 8 || ch == 127) {
                bufferedInput.remove(bufferedInput.length() - 1); // removes the last character

                // move cursor left by one character, then overwrites the character in that position with a space
                Serial0.print("\b \b");
            }
            // when ch is other keys
            else {
                bufferedInput += ch;
                
                // prints out '*' if the input is a sensitive information
                char printChar = (sensitiveInfo) ? '*' : ch;
                Serial0.print(printChar);
            }
            delay(5);
        }
    }
}