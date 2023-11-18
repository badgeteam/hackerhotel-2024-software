// the setup function runs once when you press reset or power the board

#define SW1 0
#define SW2 1
#define SW3 2
#define SW4 3
#define SW5 4

//debug
int incomingcommand = 0;
void serialdebug (int incomingcommand_);
int lastinputstatus = 0;

int selectedswitch = 0;
int inputstatus = 0;
int cycleshort = 0;
int cyclelong = 0;
bool inputflag = false;

void SetMultiplexSwitch(int selectedswitch_, bool state);

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {

  cycleshort++;
  if (cycleshort > 4) cycleshort = 0; // cycle between 5 state each loop
  cyclelong++;
  if (cyclelong > 99) cyclelong = 0; // cycle between 100 state each loop

  SetMultiplexSwitch (cycleshort, LOW);
  if (ReadSwitch()) inputflag = true;
//  if (digitalRead(10) == 0) {
//    inputstatus = 1 + cycleshort * 3;
//  }
//  if (digitalRead(9) == 0) {
//    inputstatus = 2 + cycleshort * 3;
//  }
//  if (digitalRead(8) == 0) {
//    inputstatus = 3 + cycleshort * 3;
//  }
//  if (inputstatus > 0) inputflag = true;
  SetMultiplexSwitch (cycleshort, HIGH);

  //  SetMultiplexSwitch (SW4, LOW);
  //  if (digitalRead(10) == 0) Serial.println("SW4 Right");
  //  if (digitalRead(9) == 0) Serial.println("SW4 Button");
  //  if (digitalRead(8) == 0)Serial.println("SW4 Left");
  //  SetMultiplexSwitch (SW4, HIGH);

  //debug
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingcommand = Serial.read();
    //    Serial.print("I received: ");
    //    Serial.println(incomingcommand, DEC);
    serialdebug (incomingcommand);
  }
  if (lastinputstatus != inputstatus)
  {
    lastinputstatus = inputstatus;
    serialdebug ('d');
    serialdebug ('b');
  }
  //if (cyclelong == 98) serialdebug ('d');
}

void serialdebug (int incomingcommand_)
{
  switch (incomingcommand_)
  {
    case 'd':
      Serial.print("shortcycle: ");
      Serial.print(cycleshort);
      Serial.print("    Longcycle: ");
      Serial.println(cyclelong);
      Serial.print("inputstatus: ");
      Serial.println(inputstatus);
      Serial.print("inputflag: ");
      Serial.println(inputflag);
      Serial.println("");
      break;

    case 'b':
      Serial.print("SW");
      Serial.print((inputstatus - 1) / 3 + 1);
      if (inputstatus % 3 == 1) Serial.println(" Left");
      if (inputstatus % 3 == 2) Serial.println(" Button");
      if (inputstatus % 3 == 0) Serial.println(" Right");
      break;
  }
}

// sets the enable pin of the requested switch to the requested state
void SetMultiplexSwitch(int selectedswitch_, bool state)
{
  switch (selectedswitch_)
  {
    /*  case SW1: //PD6
          digitalWrite(12, state);
          break;
        case SW2: //PD5
          digitalWrite(12, state);
          break;
        case SW3: //PD4
          digitalWrite(12, state);
          break;*/
    case SW4: //PD3
      digitalWrite(11, state);
      break;
    case SW5: //PD2
      digitalWrite(12, state);
      break;
  }
}

bool ReadSwitch (void)
{
  if (digitalRead(10) == 0) {
    inputstatus = 1 + cycleshort * 3;
    return true;
  }
  else if (digitalRead(9) == 0) {
    inputstatus = 2 + cycleshort * 3;
    return true;
  }
  else if (digitalRead(8) == 0) {
    inputstatus = 3 + cycleshort * 3;
    return true;
  }
  else return false;
}
