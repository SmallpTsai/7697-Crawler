/*
  This example configures LinkIt 7697 to a reciver of the iOS LinkIt Remote App

  created Aug 2017
*/
#include <LRemote.h>

LRemoteLabel label;
LRemoteSwitch switchButton;
LRemoteButton buttonLForward;
LRemoteButton buttonLBackward;
LRemoteButton buttonRForward;
LRemoteButton buttonRBackward;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  Serial.println("Start configuring remote");

  // Initialize GPIO
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 0);

  // Setup the Remote Control's UI canvas
  LRemote.setName("Charlie");
  LRemote.setOrientation(RC_PORTRAIT);
  LRemote.setGrid(3, 5);

  // Add a simple text label
  label.setText("Crawler");
  label.setPos(0, 0);
  label.setSize(2, 1);
  label.setColor(RC_GREY);
  LRemote.addControl(label);

  // Add an on/off switch
  switchButton.setText("USR LED");
  switchButton.setPos(2, 0);
  switchButton.setSize(1, 1);
  switchButton.setColor(RC_GREY);
  LRemote.addControl(switchButton);

  // Add a push button
  buttonLForward.setText("Forward");
  buttonLForward.setPos(0, 1);
  buttonLForward.setSize(1, 1);
  buttonLForward.setColor(RC_PINK);
  LRemote.addControl(buttonLForward);

  // Add a push button
  buttonLBackward.setText("Backward");
  buttonLBackward.setPos(0, 3);
  buttonLBackward.setSize(1, 1);
  buttonLBackward.setColor(RC_PINK);
  LRemote.addControl(buttonLBackward);

  // Add a push button
  buttonRForward.setText("Forward");
  buttonRForward.setPos(2, 1);
  buttonRForward.setSize(1, 1);
  buttonRForward.setColor(RC_PINK);
  LRemote.addControl(buttonRForward);

  // Add a push button
  buttonRBackward.setText("Backward");
  buttonRBackward.setPos(2, 3);
  buttonRBackward.setSize(1, 1);
  buttonRBackward.setColor(RC_PINK);
  LRemote.addControl(buttonRBackward);

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
  
  if(buttonLForward.getValue() == 1){
    digitalWrite(16, 1);
    digitalWrite(17, 0);
  }
  else if(buttonLBackward.getValue() == 1){
    digitalWrite(16, 0);
    digitalWrite(17, 1);
  }
  else {
    digitalWrite(16, 0);
    digitalWrite(17, 0);   
  }

  if(buttonRForward.getValue() == 1){
    digitalWrite(14, 1);
    digitalWrite(15, 0);
  }
  else if(buttonRBackward.getValue() == 1){
    digitalWrite(14, 0);
    digitalWrite(15, 1);
  }
  else {
    digitalWrite(14, 0);
    digitalWrite(15, 0);   
  }

  if(switchButton.isValueChanged()){
    digitalWrite(LED_BUILTIN, switchButton.getValue());
    Serial.print("USR LED new value =");
    Serial.println(switchButton.getValue());
  }
}
