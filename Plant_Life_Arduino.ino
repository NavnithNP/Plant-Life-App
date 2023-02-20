#include <ArduinoBLE.h>           // Bluetooth Library
#include <DHT.h>
#include <DHT_U.h>

// Initalizing global variables for sensor data to pass onto BLE
const  char * UUID_myservice          =  "a0c513b8-46c5-49f4-9eae-0407c5012e7b" ; 
const  char * UUID_mycharacteristic =  "a0c513b9-46c5-49f4-9eae-0407c5012e7b" ;

// BLE Service Name
BLEService myService ( UUID_myservice ) ;

// BLE Characteristics
BLEFloatCharacteristic ble_temperature ( UUID_mycharacteristic , BLERead | BLENotify ) ;

#define Type DHT22
int sensePin=2;
DHT HT(sensePin,Type);
float tempF;


void setup()
{
  // Initalizing Sensor
    HT.begin();
 
     
    if (!BLE.begin())
    {
        Serial.println("BLE failed to Initiate");
        delay(500);
        while (1);
    }

    // Setting BLE Name
    BLE.setLocalName("Nano");
    
    // Setting BLE Service Advertisment
    BLE.setAdvertisedService ( myService ) ;
        
    // Adding characteristics to BLE Service Advertisment
    myService.addCharacteristic(ble_temperature);
    
    // Adding the service to the BLE stack
    BLE.addService ( myService ) ;

    // Start advertising
    BLE.advertise ( ) ;
    Serial.println("Bluetooth device is now active, waiting for connections...");
}

void loop()
{
    // Variable to check if cetral device is connected
    BLEDevice central = BLE.central ( ) ;
    central.connected ( ) ;

    float tempF = HT.readTemperature(true);
  

    // Writing sensor values to the characteristic
    ble_temperature.writeValue(tempF);

    // Displaying the sensor values on the Serial Monitor
    Serial.println("Reading Sensors");
    Serial.println(tempF);
    Serial.println("\n");
}


