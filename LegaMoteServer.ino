/*
 * LegaMote Server - Server script for the LegaMote Android
 * application. LegaMote allows you to cotrol legacy switches
 * like your light switches on the wall via bluetooth. This
 * allows you to control other non-bluetooth items in your
 * home.
 *
 * This server receives commands through its bluetooth
 * module (Bluetooth over Serial) and toggles the state
 * of a relay in the Relay Module. 
 *
 * Input Format: 2 bytes
 * Byte Position 0: Command
 * Byte Position 1: Line terminator '\n'
 *
 * Command (1 byte)
 * Bits 8-4 : Relay ID with range 0-15
 * Bits 0-3 : Relay State Range 0-1
 *
 * Author: Frank E. Hernandez
 *
 * Hardware Needed:
 * 1 - Arduino
 * 2 - Bluetooth Module (I used HC6)
 * 3 - Relay Module ( I used a 2 Relay Module)
 * 4 - (Optional) PowerBoost 500 (From Adafruit)
 * 5 - (Optional) Lithium Ion Battery 3.7v 2000mAh (From Adafruit)
 *
 * Note: This is intended to be mainly used with its Android
 * companion app LegaMote. 
 */

/*
 * Starting pin for the relays.
 * For this implementation the relay pin is calculated
 * by adding the relay ID to the base pin. However,
 * you can chose any relay finding scheme you like 
 * by implemeting your own getRelayPinFromId() function.
 */
int RELAY_PIN_BASE_NUM = 3;

int incomingByte = 0;
int commandByte = 0;
bool commandComplete = false;
bool commandEntered = false;

int relayId;
int relayState;
int relayPin;

void setup() 
{
   setupRelayPins();
   
   Serial.begin(9600);
   while(!Serial)
   {
      // Wait for serial port to open. 
   }
   Serial.println("LegaMote Read\n");
}

void setupRelayPins()
{
    // RELAY_PIN_BASE_NUM + 0
    pinMode(RELAY_PIN_BASE_NUM + 3, OUTPUT);
    
    pinMode(RELAY_PIN_BASE_NUM + 4, OUTPUT);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  if(!commandComplete)
  {
     return; 
  }
  
  if(!commandEntered)
  {
     return; 
  }
  relayId = (commandByte >> 4) & 0x0F;
  relayState = commandByte & 0x0F;
  
  handleSwitch(relayId, relayState);
  
  commandByte = 0;
  commandComplete = false;
  commandEntered = false;
}

void serialEvent()
{
   retrieveCommand(); 
}

void retrieveCommand()
{
  while(Serial.available())
  {
     incomingByte = Serial.read();
     if(incomingByte != (int)'\n' 
         && incomingByte != (int)'\r')
     {
        commandByte = incomingByte;
        commandEntered = true;
     }
     else
     {
        //Our commands are 1 byte long followed
        // by the end of line \n character.
        // so once we read the end of line we stop. 
        commandComplete = true;
        break; 
     }
  }
  
}

void handleSwitch(int relayId, int relayState)
{
    relayPin = getRelayPinFromId(relayId);
    digitalWrite(relayPin, relayState);
 
    Serial.println(String("Relay Id: ") + relayPin + String(" Relay State: ") + relayState);   
}

int getRelayPinFromId(int relayId)
{
   return RELAY_PIN_BASE_NUM + relayId;
}