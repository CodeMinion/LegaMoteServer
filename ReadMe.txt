Arduino sketch for the LegaMote companion Android app.

This sketch allows you to control a regular (non-Bluetooth or legacy) switch at home by using you Android device. 

Hardware you will need:
1- Arudino Board - (I used Arduino Uno)
2- Relay Module - (I used a 2 Relay Module from Ebay)
3- Bluetooth Module - (I used HC06 from Ebay)

Wiring:

Bluetooth Module:
	BT TX to Arduino Pin 0
	BT RX to Arduino Pin 1
	BT Power to Arduino 3V
	BT Ground to Arduino Ground
 
Relay Module:
	Module Power to Arduino 5v.
	Module Ground to Arduino Ground
	Module In 1 to Arudion RELAY_PIN_BASE_NUM (See sketch for actual pin number)
	Module In 2 to Arduino RELAY_PIN_BASE_NUM + 1
	Main power 110V wired to COM
	Load (Switch) wired to NO
	
	
Pictures: https://www.flickr.com/photos/codeminion/21009009965/in/album-72157652048229075/
