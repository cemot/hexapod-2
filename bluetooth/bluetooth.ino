#include <SoftwareSerial.h>
#define RxD 9
#define TxD 10
#define DEBUG_ENABLED 1
SoftwareSerial blueToothSerial(RxD,TxD);
char incoming;
void setup()
{
	pinMode(RxD, INPUT);
	pinMode(TxD, OUTPUT);
	setupBlueToothConnection();
	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
}
void setupBlueToothConnection()
{
	blueToothSerial.begin(38400); //Set BluetoothBee BaudRate to default baud rate 38400 // other: Serial.begin(57600);
	delay(1000);
	sendBlueToothCommand("\r\n+STWMOD=0\r\n");
	sendBlueToothCommand("\r\n+STNA=SeeeduinoBluetooth\r\n");
	sendBlueToothCommand("\r\n+STAUTO=0\r\n");
	sendBlueToothCommand("\r\n+STOAUT=1\r\n");
	sendBlueToothCommand("\r\n +STPIN=0000\r\n");
	delay(2000); // This delay is required.
	sendBlueToothCommand("\r\n+INQ=1\r\n");
	delay(2000); // This delay is required.
}
//Checks if the response "OK" is received
void CheckOK()
{
	char a,b;
	while(1)
	{
		if(blueToothSerial.available())
		{
			a = blueToothSerial.read();
			if('O' == a)
			{
				// Wait for next character K. available() is required in some cases, as K is not immediately available.
				while(blueToothSerial.available())
				{
					b = blueToothSerial.read();
					break;
				}
				if('K' == b)
				{
					break;
				}
			}
		}
	}
	while( (a = blueToothSerial.read()) != -1)
	{
		//Wait until all other response chars are received
	}
}
void sendBlueToothCommand(char command[])
{
	blueToothSerial.print(command);
	CheckOK();
}
void loop()
{
	// get character sent from Android device
	incoming=blueToothSerial.read();
	// decide what to do with it
	switch (incoming)
	{
	case '1':
		digitalWrite(4, HIGH);
		blueToothSerial.println("pin 4 HIGH");
		break;
	case '2':
		digitalWrite(5, HIGH);
		blueToothSerial.println("pin 5 HIGH");
		break;
	case '3':
		digitalWrite(6, HIGH);
		blueToothSerial.println("pin 6 HIGH");
		break;
	case '4':
		digitalWrite(7, HIGH);
		blueToothSerial.println("pin 7 HIGH");
		break;
	case '5':
		digitalWrite(4, LOW);
		blueToothSerial.println("pin 4 LOW");
		break;
	case '6':
		digitalWrite(5, LOW);
		blueToothSerial.println("pin 5 LOW");
		break;
	case '7':
		digitalWrite(6, LOW);
		blueToothSerial.println("pin 6 LOW");
		break;
	case '8':
		digitalWrite(7, LOW);
		blueToothSerial.println("pin 7 LOW");
		break;
	}
	delay(100);
}
