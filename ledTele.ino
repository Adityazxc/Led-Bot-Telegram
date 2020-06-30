//subscribe channel youtube.com/mohamadidrus
//untuk mendapapatkan tutorial project arduino/IoT lainnya
#include "CTBot.h"
CTBot myBot;

String ssid = "Hole";     // REPLACE mySSID WITH YOUR WIFI SSID
String pass = "iyaaituu"; // REPLACE myPassword YOUR WIFI PASSWORD, IF ANY
String token = "1263893915:AAEZ6Luam0fUtHPRjuKSYoCWAifyAELTV6I";   // REPLACE myToken WITH YOUR TELEGRAM BOT TOKEN
uint8_t led = BUILTIN_LED;            // the onboard ESP8266 LED.    
                            // If you have a NodeMCU you can use the BUILTIN_LED pin
                            // (replace 2 with BUILTIN_LED)							

void setup() {
	// initialize the Serial
	Serial.begin(115200);
	Serial.println("Starting TelegramBot...");
  pinMode(D1, OUTPUT);
	// connect the ESP8266 to the desired access point
	myBot.wifiConnect(ssid, pass);

	// set the telegram bot token
	myBot.setTelegramToken(token);

	// check if all things are ok
	if (myBot.testConnection())
		Serial.println("\ntestConnection OK");
	else
		Serial.println("\ntestConnection NOK");

	// set the pin connected to the LED to act as output pin
	pinMode(led, OUTPUT);
	digitalWrite(led, HIGH); // turn off the led (inverted logic!)
  
}

void loop() {
	// a variable to store telegram message data
	TBMessage msg;

	// if there is an incoming message...
	if (myBot.getNewMessage(msg)) {

		if (msg.text.equalsIgnoreCase("nyalakan lampu")) {              // if the received message is "LIGHT ON"...
			digitalWrite(led, LOW);                               // turn on the LED (inverted logic!)
      digitalWrite(D1, LOW); 
			myBot.sendMessage(msg.sender.id, "Lampu sudah menyala bosss");  // notify the sender
		}
		else if (msg.text.equalsIgnoreCase("matikan lampu")) {        // if the received message is "LIGHT OFF"...
			digitalWrite(led, HIGH);                              // turn off the led (inverted logic!)
     digitalWrite(D1,HIGH);
			myBot.sendMessage(msg.sender.id, "Lampu sudah mati sultan"); // notify the sender
		}
		else {                                                    // otherwise...
			// generate the message for the sender
			String reply;
			reply = (String)"Welcome " + msg.sender.username + (String)". Try LIGHT ON or LIGHT OFF.";
			myBot.sendMessage(msg.sender.id, reply);             // and send it
		}
	}
	// wait 500 milliseconds
	delay(500);
}
