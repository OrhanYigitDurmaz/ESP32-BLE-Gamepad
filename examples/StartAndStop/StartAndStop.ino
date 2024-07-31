/*
 * 
 * Adds start and stop functionality.
 *
 */

#include <Arduino.h>
#include <BleGamepad.h>

BleGamepad* bleGamepad = nullptr;              //sett null pointer to bleGamepad object, so we can declare it globally and start and stop it
BleGamepadConfiguration bleGamepadConfig;                          // Create a BleGamepadConfiguration object to store all of the options

    
void setup()
{
    Serial.begin(115200);
    Serial.println("Starting BLE work!");
    bleGamepadConfig.setAutoReport(false);
    bleGamepadConfig.setControllerType(CONTROLLER_TYPE_GAMEPAD); // CONTROLLER_TYPE_JOYSTICK, CONTROLLER_TYPE_GAMEPAD (DEFAULT), CONTROLLER_TYPE_MULTI_AXIS
    bleGamepadConfig.setVid(0xe502);
    bleGamepadConfig.setPid(0xabcd);
    
    bleGamepadConfig.setModelNumber("1.0");
    bleGamepadConfig.setSoftwareRevision("Software Rev 1");
    bleGamepadConfig.setSerialNumber("9876543210");
    bleGamepadConfig.setFirmwareRevision("2.0");
    bleGamepadConfig.setHardwareRevision("1.7");
    
    // Some non-Windows operating systems and web based gamepad testers don't like min axis set below 0, so 0 is set by default
    //bleGamepadConfig.setAxesMin(0x8001); // -32767 --> int16_t - 16 bit signed integer - Can be in decimal or hexadecimal
	  bleGamepadConfig.setAxesMin(0x0000); // 0 --> int16_t - 16 bit signed integer - Can be in decimal or hexadecimal    
    bleGamepadConfig.setAxesMax(0x7FFF); // 32767 --> int16_t - 16 bit signed integer - Can be in decimal or hexadecimal  

    bleGamepad = new BleGamepad("Custom Controller Name", "lemmingDev", 100);

    if (bleGamepad == nullptr) {
        ESP_LOGE(LOG_TAG, "Pointer Error! Rebooting in 3 seconds...");
        delay(3000);
        ESP.restart();
    }   
    
    bleGamepad->begin(&bleGamepadConfig); // Begin gamepad with configuration options
    bleGamepad->startAdvertising();
}

void loop()
{
    if (bleGamepad != nullptr && bleGamepad->isConnected())
    {
        // your code when connected
    }



    delay(7000); //7 seconds
    //if you want to stop advertising:
    bleGamepad->stopAdvertising();

    //if you want to stop the ble stack:
    bleGamepad->end();

    //and now delete it:
    delete bleGamepad;
    bleGamepad = nullptr;

    delay(7000); //7 seconds

    //if you want to start it again now you need to declare it again
    bleGamepad = new BleGamepad("Custom Controller 2", "lemmingDev", 50);

}