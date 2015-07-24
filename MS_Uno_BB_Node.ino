#include <SPI.h>
#include <MySensor.h>  

#define CHILD_ID_LIGHT 55
#define LIGHT_SENSOR_ANALOG_PIN 0

unsigned long SLEEP_TIME = 30000; // Sleep time between reads (in milliseconds)

MySensor gw;
MyMessage msg(CHILD_ID_LIGHT, V_LIGHT_LEVEL);
int lastLightLevel;

void setup()  
{ 
  gw.begin(incomingMessage, 202, false);

  // Send the sketch version information to the gateway and Controller
  gw.sendSketchInfo("UNO BB Light Sensor", "1.0");

  // Register all sensors to gateway (they will be created as child devices)
  gw.present(CHILD_ID_LIGHT, S_LIGHT_LEVEL);
}

void loop()      
{     
  int lightLevel=66;
  //int lightLevel = (1023-analogRead(LIGHT_SENSOR_ANALOG_PIN))/10.23; 
  Serial.println(lightLevel);
  if (lightLevel != lastLightLevel) {
      gw.send(msg.set(lightLevel));
      lastLightLevel = lightLevel;
  }
  gw.wait(15000);
  
  
  // REQUEST CID_BTEMP(8) FROM UNO(209)
  Serial.println("requesting");
  gw.request(8,  V_TEMP, 209);
  gw.wait(5000);
  
}



//	uint8_t last;            	 // 8 bit - Id of last node this message passed
//	uint8_t sender;          	 // 8 bit - Id of sender node (origin)
//	uint8_t destination;     	 // 8 bit - Id of destination node
//
//	uint8_t version_length;      // 3 bit - Protocol version
//			                     // 5 bit - Length of payload
//	uint8_t command_ack_payload; // 3 bit - Command type
//	                             // 1 bit - Request an ack - Indicator that receiver should send an ack back.
//								 // 1 bit - Is ack messsage - Indicator that this is the actual ack message.
//	                             // 3 bit - Payload data type
//	uint8_t type;            	 // 8 bit - Type varies depending on command
//	uint8_t sensor;          	 // 8 bit - Id of sensor that this message concerns.


void incomingMessage(const MyMessage &message)
{
  //int CID = (int)message.sensor;
  //uint8_t type_uno = message.type;
  //uint16_t destination_uno message.destination;
  int barrotemp = atoi(message.data);
  //String dimvalue = String(message.data);
  Serial.println("Rcvd from UNO");
  Serial.print("Sender: "); Serial.println(message.sender);
  Serial.print("Last: "); Serial.println(message.last);
  Serial.print("Sensor: "); Serial.println(message.sensor);
  //Serial.print(": "); Serial.println(message.);
  //Serial.print(": "); Serial.println(message.);
  Serial.print("Type: "); Serial.println(message.type);
  Serial.print("Data: "); Serial.println(message.getFloat(), 1);
  
  
//  if(message.destination==209){
//   Serial.println("RECEOVED FROM UNO..."); 
//   Serial.print("VALUE:"); 
//   Serial.println(message.data);
//  } else {
//     Serial.println("error"); 
//  }
  
  
  
  
  
}



