#define SW1 0
#define SW2 1
#define SW3 2
#define SW4 3
#define SW5 4

#define A 0
#define B 1
#define C 2
#define D 3
#define E 4

#define LEDINPUT 0
#define LEDLOW   1
#define LEDHIGH  2

//debug
int incomingcommand = 0;
void serialdebug (int incomingcommand_);
int lastinputstatus = 0;
//debug end

int selectedswitch = 0;
int inputstatus = 0;
int cycleshort = 0;
int cyclelong = 0;
bool inputflag = false;
int LEDPWM [20];

void SetMultiplexSwitch(int selectedswitch_, bool state);
bool ReadSwitch (void);
void SetLEDpin (int state);

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);

// initialise LEDs
//  for (int n = 0; n < 5; n++) SetLEDpin(n, LEDINPUT);

  pinMode(3, INPUT); // D
  pinMode(4, INPUT); // B
  pinMode(5, INPUT); // A
  pinMode(6, INPUT); // E
  pinMode(7, INPUT); // C

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  // Set all LEDs to maximum brightness
  for (int n = 0; n < 20; n++) LEDPWM = 99;
}

void loop() {



  
  //  pinMode(3, INPUT); // D
  //  pinMode(4, INPUT); // B
  //  pinMode(5, INPUT); // A
  //  pinMode(6, INPUT); // E
  //  pinMode(7, INPUT); // C

  cycleshort++;
  if (cycleshort > 4) cycleshort = 0; // cycle between 5 state each loop
  cyclelong++;
  if (cyclelong > 99) cyclelong = 0; // cycle between 100 state each loop

  //  if (cycleshort == 0) {
  //    pinMode(3, OUTPUT); // D
  //    digitalWrite(3, HIGH);
  //    pinMode(4, OUTPUT); // C
  //    pinMode(5, OUTPUT); // A
  //    pinMode(6, OUTPUT); // E
  //    pinMode(7, OUTPUT); // C
  //    digitalWrite(4, LOW);
  //    digitalWrite(5, LOW);
  //    digitalWrite(6, LOW);
  //    digitalWrite(7, LOW);
  //  }
  //
  //  if (cycleshort == 1) {
  //    pinMode(4, OUTPUT); // D
  //    digitalWrite(4, HIGH);
  //    pinMode(3, OUTPUT); // C
  //    pinMode(5, OUTPUT); // A
  //    pinMode(6, OUTPUT); // E
  //    pinMode(7, OUTPUT); // C
  //    digitalWrite(3, LOW);
  //    digitalWrite(5, LOW);
  //    digitalWrite(6, LOW);
  //    digitalWrite(7, LOW);
  //  }
  //
  //  if (cycleshort == 2) {
  //    pinMode(5, OUTPUT); // D
  //    digitalWrite(5, HIGH);
  //    pinMode(4, OUTPUT); // C
  //    pinMode(3, OUTPUT); // A
  //    pinMode(6, OUTPUT); // E
  //    pinMode(7, OUTPUT); // C
  //    digitalWrite(4, LOW);
  //    digitalWrite(3, LOW);
  //    digitalWrite(6, LOW);
  //    digitalWrite(7, LOW);
  //  }
  //
  //  if (cycleshort == 3) {
  //    pinMode(6, OUTPUT); // D
  //    digitalWrite(6, HIGH);
  //    pinMode(4, OUTPUT); // C
  //    pinMode(5, OUTPUT); // A
  //    pinMode(3, OUTPUT); // E
  //    pinMode(7, OUTPUT); // C
  //    digitalWrite(4, LOW);
  //    digitalWrite(5, LOW);
  //    digitalWrite(3, LOW);
  //    digitalWrite(7, LOW);
  //  }
  //
  //  if (cycleshort == 4) {
  //    pinMode(7, OUTPUT); // D
  //    digitalWrite(7, HIGH);
  //    pinMode(3, OUTPUT); // C
  //    pinMode(5, OUTPUT); // A
  //    pinMode(6, OUTPUT); // E
  //    pinMode(4, OUTPUT); // C
  //    digitalWrite(3, LOW);
  //    digitalWrite(5, LOW);
  //    digitalWrite(6, LOW);
  //    digitalWrite(4, LOW);
  //  }

  // debug
  //  SetMultiplexSwitch (cycleshort, LOW);
  //  if (ReadSwitch()) inputflag = true;
  //  SetMultiplexSwitch (cycleshort, HIGH);
  // debug end

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

  //debug end
}

//debug
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

    // test function
    case 't':
      for (int n = 0; n < 5; n++) SetLEDpin(n, LEDINPUT);
      break;

    case'l':
      Serial.print("enter LED pin: ");
      bool characterselected = true;
      int debugLEDPIN = -1;
      int debugledselected;
      while (characterselected)
      {
        switch (debugLEDPIN)
        {
          case 'a':
            Serial.print("A selected, enter state: ");
            characterselected = false;
            debugledselected = 0;
            break;

          case 'b':
            Serial.print("B selected, enter state: ");
            characterselected = false;
            debugledselected = 1;
            break;

          case 'c':
            Serial.print("C selected, enter state: ");
            characterselected = false;
            debugledselected = 2;
            break;

          case 'd':
            Serial.print("D selected, enter state: ");
            characterselected = false;
            debugledselected = 3;
            break;

          case 'e':
            Serial.print("E selected, enter state: ");
            characterselected = false;
            debugledselected = 4;
            break;

          default:
            if (Serial.available() > 0) debugLEDPIN = Serial.read();
            break;
        }
      }

      bool stateselected = true;
      debugLEDPIN = -1;
      while (stateselected)
      {
        switch (debugLEDPIN)
        {
          case 'i':
            Serial.println("Input selected");
            SetLEDpin (debugledselected, LEDINPUT);
            stateselected = false;
            break;

          case 'l':
            Serial.println("Output Low selected");
            SetLEDpin (debugledselected, LEDLOW);
            stateselected = false;
            break;

          case 'h':
            Serial.println("Output High selected");
            SetLEDpin (debugledselected, LEDHIGH);
            stateselected = false;
            break;

          default:
            if (Serial.available() > 0) debugLEDPIN = Serial.read();
            break;
        }
      }
  }
}
//debug end

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

// Reads the switches state and populate input status, returns 1 if an input is detected
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

// Sets the 5 LED pins either as input, high or low
void SetLEDpin (int pin, int state)
{
  int LEDinputLUT [5] = {5, 4, 7, 3, 6};
  switch (state)
  {
    case LEDINPUT:
      pinMode(LEDinputLUT[pin], INPUT);
      break;

    case LEDLOW:
      pinMode(LEDinputLUT[pin], OUTPUT);
      digitalWrite(LEDinputLUT[LEDinputLUT[pin]], LOW);
      break;

    case LEDHIGH:
      pinMode(LEDinputLUT[pin], OUTPUT);
      digitalWrite(LEDinputLUT[pin], HIGH);
      break;
  }
}
