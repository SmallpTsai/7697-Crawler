/*
  This example configures LinkIt 7697 to a reciver of the iOS LinkIt Remote App

  created Aug 2017
*/
#include <LRemote.h>

LRemoteCircleButton buttonLeft;
LRemoteJoyStick stickRight;
LRemoteLabel labelRight;
LRemoteCircleButton buttonup;
void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  Serial.println("Start configuring remote");

  // Initialize GPIO
  pinMode(17, OUTPUT);
  digitalWrite(17, 0);
  pinMode(16, OUTPUT);
  digitalWrite(16, 0);
  pinMode(15, OUTPUT);
  digitalWrite(15, 0);
  pinMode(14, OUTPUT);
  digitalWrite(14, 0);
  pinMode(13, OUTPUT);
  digitalWrite(13, 0);
  pinMode(12, OUTPUT);
  digitalWrite(12, 0);


  // Setup the Remote Control's UI canvas
  LRemote.setName("HANNY yay!");
  
  // We use a landscape since it is easir to contorl joysticks
  LRemote.setOrientation(RC_LANDSCAPE);
  LRemote.setGrid(5, 3);

  // Add left stick
  buttonLeft.setText("Grab");
  buttonLeft.setPos(0, 1);
  buttonLeft.setSize(2, 2);
  buttonLeft.setColor(RC_ORANGE);
  LRemote.addControl(buttonLeft);

  // Add Right stick
  stickRight.setPos(3, 1);
  stickRight.setSize(2, 2);
  stickRight.setColor(RC_BLUE);
  LRemote.addControl(stickRight);

    

  labelRight.setText("(0, 0)");
  labelRight.setPos(3, 0);
  labelRight.setSize(2, 1);
  labelRight.setColor(RC_PINK);
  LRemote.addControl(labelRight);

  buttonup.setText("DOWN");
  buttonup.setPos(0, 1);
  buttonup.setSize(1, 1);
  buttonup.setColor(RC_YELLOW);
  LRemote.addControl(buttonup);



  // Start broadcasting our remote contoller
  // This method implicitly initialized underlying BLE subsystem
  // to create a BLE peripheral, and then
  // start advertisement on it.
  LRemote.begin();
  Serial.println("begin() returned");
}

void checkAndUpdateLabel(LRemoteLabel& label, LRemoteJoyStick& stick) {
  if(stick.isValueChanged()){
    LRemoteDirection d = stick.getValue();
    // d.x and d.y are the value from the Joystick component:
    // d.x : -100 ~ 100, where 0 is center, -100 is leftmost, and 100 is rightmost.
    // d.y : -100 ~ 100, where 0 is center, -100 is bottommost, and 100 is topmost.

    // you can print d directly.
    Serial.println(d);
  if(d.y >50) {
    digitalWrite(17, 0);
    digitalWrite(16, 1);
    digitalWrite(15, 0);
    digitalWrite(14, 1);
  }
  else if(d.y <-50) {
    digitalWrite(17, 1);
    digitalWrite(16, 0);
    digitalWrite(15, 1);
    digitalWrite(14, 0);
}
  else if(d.x > 50)
  {
    digitalWrite(17, 0);
    digitalWrite(16, 1);
    digitalWrite(15, 1);
    digitalWrite(14, 0);
  }
   else if (d.x < -50){
    digitalWrite(17, 1);
    digitalWrite(16, 0);
    digitalWrite(15, 0);
    digitalWrite(14, 1);
   }
   else {
    digitalWrite(17, 0);
    digitalWrite(16, 0);
    digitalWrite(15, 0);
    digitalWrite(14, 0);
   }



    // in this example, we simply pass the value of d.x/d.y
    // back to the LinkIt Remote app.
    label.updateText(d.toString());
  } 
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

  // refer to this function to know how to parse the values from joystick.
  //checkAndUpdateLabel(labelLeft, buttonLeft);
  checkAndUpdateLabel(labelRight, stickRight);

  if(buttonLeft.isValueChanged()){
    digitalWrite(13, buttonLeft.getValue());
    digitalWrite(12, 0);
  }
  if(buttonup.isValueChanged()){
    digitalWrite(12, buttonup.getValue());
    digitalWrite(13, 0);
  }
  
}
