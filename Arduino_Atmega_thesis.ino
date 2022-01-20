

// defines used by the serial event
// do not modify
#define  STX 2
#define  ETX 3
#define  SERIALSTX 0
#define  SERIALETX 1
#define  SERIALRDY 2

// Energy Meter read results
String  EM;
String  EM_version;
String  EM_Vrms;
String  EM_Irms;
String  EM_RealPower;
String  EM_VA;
String  EM_QPower;
String  EM_QInstant;
String  EM_PowerFactor;
String  EM_Temperature;
String  EM_Harmonic;
String  EM_Fundamental;
String  EM_FundReact;
String  EM_WattHour;
String  EM_IntegrationTime;
String  myTime;

byte  serial_state;
String serialinput;
boolean  carddetected = false;
char a = 0;


void setup() {
  // initialize serial:
  Serial.begin(9600);
  Serial2.begin(9600);
  delay(1000);
  serial_state = SERIALSTX;
  serialinput = "";
  check_EnergyMeter();


}

void loop() {

  if (check_EnergyMeter() == true) {

    /* Replace the following demo codes with your own
    */
    Serial.print("Version: ");
    Serial.println(EM_version);
    Serial.print("Volt RMS: ");
    Serial.print(EM_Vrms);
    Serial.print(" Amp RMS: ");
    Serial.print(EM_Irms);
    Serial.print(" Real Power: ");
    Serial.println(EM_RealPower);

    Serial.print("VA: ");
    Serial.print(EM_VA);
    Serial.print(" Q Power: ");
    Serial.print(EM_QPower);
    Serial.print(" Q Instant: ");
    Serial.println(EM_QInstant);

    Serial.print("PF: ");
    Serial.print(EM_PowerFactor);
    Serial.print(" Temperature: ");
    Serial.println(EM_Temperature);

    Serial.print("Harmonic: ");
    Serial.print(EM_Harmonic);
    Serial.print(" Fundamental: ");
    Serial.print(EM_Fundamental);
    Serial.print(" Fundamental Reactive: ");
    Serial.println(EM_FundReact);

    Serial.print("Watt-Hour: ");
    Serial.println(EM_WattHour);
    Serial.print("Integration Time: ");
    Serial.println(EM_IntegrationTime);
    Serial.println("");

    Serial.print("Time: ");
    myTime = millis();
    Serial.println(myTime);
    delay(1000);
  }


  /*
    //Uncomment this to check the Energy meter data, if it is in ASCII CSV format
    //Then comment out the above sample code.
    // This is for checking only
    if(Serial.available()){
    a = Serial.read();
    Serial.print(a);
    }

  */

}


/* Do not modify anything in the following codes unless
  you absolutely know what you are doing :-) */

boolean check_EnergyMeter(void) {

  int  strindex;
  int  strindexe;

  // Read if Energy Meter II data is available
  if (serial_state == SERIALRDY) {

    //extract waiting for response portion
    strindex = serialinput.indexOf(",");
    EM = serialinput.substring(strindex, strindexe);

    //extract version portion
    strindex++;
    strindexe = serialinput.indexOf(",", strindex);
    EM_version = serialinput.substring(strindex, strindexe);

    //extract volt rms portion
    strindex = strindexe + 1;
    strindexe = serialinput.indexOf(",", strindex);
    EM_Vrms = serialinput.substring(strindex, strindexe);

    //extract amp rms portion
    strindex = strindexe + 1;
    strindexe = serialinput.indexOf(",", strindex);
    EM_Irms = serialinput.substring(strindex, strindexe);

    //extract real power portion
    strindex = strindexe + 1;
    strindexe = serialinput.indexOf(",", strindex);
    EM_RealPower = serialinput.substring(strindex, strindexe);

    //extract va portion
    strindex = strindexe + 1;
    strindexe = serialinput.indexOf(",", strindex);
    EM_VA = serialinput.substring(strindex, strindexe);

    //extract q power portion
    strindex = strindexe + 1;
    strindexe = serialinput.indexOf(",", strindex);
    EM_QPower = serialinput.substring(strindex, strindexe);

    //extract q instant portion
    strindex = strindexe + 1;
    strindexe = serialinput.indexOf(",", strindex);
    EM_QInstant = serialinput.substring(strindex, strindexe);

    //extract power factor portion
    strindex = strindexe + 1;
    strindexe = serialinput.indexOf(",", strindex);
    EM_PowerFactor = serialinput.substring(strindex, strindexe);

    //extract temperature portion
    strindex = strindexe + 1;
    strindexe = serialinput.indexOf(",", strindex);
    EM_Temperature = serialinput.substring(strindex, strindexe);

    //extract harmonic portion
    strindex = strindexe + 1;
    strindexe = serialinput.indexOf(",", strindex);
    EM_Harmonic = serialinput.substring(strindex, strindexe);

    //extract fundamental portion
    strindex = strindexe + 1;
    strindexe = serialinput.indexOf(",", strindex);
    EM_Fundamental = serialinput.substring(strindex, strindexe);

    //extract fundamental reactive portion
    strindex = strindexe + 1;
    strindexe = serialinput.indexOf(",", strindex);
    EM_FundReact = serialinput.substring(strindex, strindexe);

    //extract watt hour portion
    strindex = strindexe + 1;
    strindexe = serialinput.indexOf(",", strindex);
    EM_WattHour = serialinput.substring(strindex, strindexe);

    //extract integration portion
    strindex = strindexe + 1;
    strindexe = serialinput.indexOf(",", strindex);
    EM_IntegrationTime = serialinput.substring(strindex, strindexe);

    // clear received string and ready SERIAL for new stream
    serialinput = "";
    serial_state = SERIALSTX;
    return (true);
  }
  return (false); // return false if RFID data is not available
}


/* This is a interrupt driven serial Rx routine */

void serialEvent2() {
  while (Serial2.available()) {
    // get the new byte:
    char inChar = (char)Serial2.read();

    // Wait for the STX character
    if (serial_state == SERIALSTX) {
      if (inChar == STX) {
        serial_state = SERIALETX;  // STX character detected, enable next phase
        return;
      }
    }

    // Store rx character to serial input until ETX is detected
    if (serial_state == SERIALETX) {
      if (inChar != ETX) {
        serialinput += inChar;
        return;
      }
    }

    // Indicate serial data is ready after ETX is detected
    serial_state = SERIALRDY;
  }
}
