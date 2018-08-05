/*
  This example configures LinkIt 7697 to a reciver of the iOS LinkIt Remote App

  created Aug 2017
*/
#include <LRemote.h>

LRemoteCircleButton button1;
LRemoteCircleButton button2;
LRemoteCircleButton button3;
LRemoteCircleButton button4;
LRemoteCircleButton button5;
LRemoteCircleButton button6;
LRemoteCircleButton button7;
LRemoteCircleButton button8;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  Serial.println("Start configuring remote");

  // Initialize GPIO
  pinMode(17, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(17, 0);
  digitalWrite(16, 0);
  digitalWrite(15, 0);
  digitalWrite(14, 0);
  digitalWrite(13, 0);
  digitalWrite(12, 0);

  // Setup the Remote Control's UI canvas
  LRemote.setName("Jenny");
  LRemote.setOrientation(RC_LANDSCAPE);
  LRemote.setGrid(5, 3);

  // Add a push button
  button1.setText("Forward");
  button1.setPos(1, 0);
  button1.setSize(1, 1);
  button1.setColor(RC_GREEN);
  LRemote.addControl(button1);

  button2.setText("Left");
  button2.setPos(0, 1);
  button2.setSize(1, 1);
  button2.setColor(RC_BLUE);
  LRemote.addControl(button2);

  button3.setText("Right");
  button3.setPos(2, 1);
  button3.setSize(1, 1);
  button3.setColor(RC_BLUE);
  LRemote.addControl(button3);

  button4.setText("Backward");
  button4.setPos(1, 2);
  button4.setSize(1, 1);
  button4.setColor(RC_GREEN);
  LRemote.addControl(button4);

  button5.setText("Right U");
  button5.setPos(4, 0);
  button5.setSize(1, 1);
  button5.setColor(RC_YELLOW);
  LRemote.addControl(button5);

  button6.setText("Grab");
  button6.setPos(4, 1);
  button6.setSize(1, 1);
  button6.setColor(RC_ORANGE);
  LRemote.addControl(button6);

  button7.setText("Left U");
  button7.setPos(4, 2);
  button7.setSize(1, 1);
  button7.setColor(RC_YELLOW);
  LRemote.addControl(button7);

  button8.setText("Grab2");
  button8.setPos(3, 1);
  button8.setSize(1, 1);
  button8.setColor(RC_ORANGE);
  LRemote.addControl(button8);

  // Start broadcasting our remote contoller
  // This method implicitly initialized underlying BLE subsystem
  // to create a BLE peripheral, and then
  // start advertisement on it.
  LRemote.begin();
  Serial.println("begin() returned");
}

void loop() {

  // check if we are connect by some 
  // BLE central device, e.g. an mobile app
  if(!LRemote.connected()) {
    Serial.println("waiting for connection");
    delay(1000);
  } else {
    // The interval between button down/up
    // can be very short - e.g. a quick tap
    // on the screen.
    // We could lose some event if we
    // delay something like 100ms.
    delay(15);
  }
  
  // Process the incoming BLE write request
  // and translate them to control events
  LRemote.process();

  // Now we poll each control's status
  if(button1.isValueChanged()){    
    digitalWrite(17, LOW);
    digitalWrite(16, button1.getValue());
    digitalWrite(15, LOW);
    digitalWrite(14, button1.getValue());
  }

  if(button4.isValueChanged()){    
    digitalWrite(17, button4.getValue());
    digitalWrite(16, LOW);
    digitalWrite(15, button4.getValue());
    digitalWrite(14, LOW);
  }
 if(button2.isValueChanged()){    
//    digitalWrite(17, LOW);
//    digitalWrite(16, button2.getValue());
    digitalWrite(15, LOW);
    digitalWrite(14, button2.getValue());
  }
 if(button3.isValueChanged()){    
    digitalWrite(17, LOW);
    digitalWrite(16, button3.getValue());
 }
 
  if(button5.isValueChanged()){    
    digitalWrite(17, LOW);
    digitalWrite(16, button5.getValue());
    digitalWrite(15, button5.getValue());
    digitalWrite(14, LOW);
  }  
 if(button7.isValueChanged()){    
    digitalWrite(16, LOW);
    digitalWrite(17, button7.getValue());
    digitalWrite(14, button7.getValue());
    digitalWrite(15, LOW);
  }  
if(button6.isValueChanged()){    
    digitalWrite(13, LOW);
    digitalWrite(12, button6.getValue());
 }
if(button8.isValueChanged()){    
    digitalWrite(12, LOW);
    digitalWrite(13, button8.getValue());
  }  
  
//  if(button.isValueChanged()){
//    Serial.print("button new value =");
//    Serial.println(button.getValue());
//  }

//  if(bigButton.isValueChanged()){
//    Serial.print("big button new value =");
//    Serial.println(bigButton.getValue());
//  }
//
//  if(switchButton.isValueChanged()){
//    digitalWrite(17, switchButton.getValue());
//    Serial.print("USR LED new value =");
//    Serial.println(switchButton.getValue());
//  }
//
//  if(slider.isValueChanged()){
//    Serial.print("slider to new value = ");
//    Serial.println(slider.getValue());
//  }
}
