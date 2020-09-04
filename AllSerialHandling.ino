
//////////
/////////  All Serial Handling Code,
/////////  It's Changeable with the 'outputType' variable
/////////  It's declared at start of code.
/////////

void serialOutput(){   // Decide How To Output Serial.
  switch(outputType){
    case PROCESSING_VISUALIZER:
      sendDataToSerial('S', Signal);     // goes to sendDataToSerial function
      break;
    case SERIAL_PLOTTER:  // open the Arduino Serial Plotter to visualize these data
      GSR_Value=analogRead(GSR);
      Serial.print(GSR_Value);
      Serial.print(",");
      Serial.print(BPM);
      Serial.print(",");
      Serial.print(IBI);
      Serial.print(",");
      Serial.println(Signal);
      writeDataToSDCard("S",Signal);

      writeDataToSDCard("GSR",GSR_Value);
      break;
    default:
      break;
  }

}

//  Decides How To OutPut BPM and IBI Data
void serialOutputWhenBeatHappens(){
  switch(outputType){
    case PROCESSING_VISUALIZER:    // find it here https://github.com/WorldFamousElectronics/PulseSensor_Amped_Processing_Visualizer
      sendDataToSerial('B',BPM);   // send heart rate with a 'B' prefix
      sendDataToSerial('Q',IBI);   // send time between beats with a 'Q' prefix
      //writeDataToSDCard("BPM",BPM);
      //writeDataToSDCard("IBI",IBI);
      
      
      break;

    default:
      Serial.print("-------beat!------");
      writeDataToSDCard("BPM",BPM);
      writeDataToSDCard("IBI",IBI);
      break;
  }
}

//  Sends Data to Pulse Sensor Processing App, Native Mac App, or Third-party Serial Readers.
void sendDataToSerial(char symbol, int data ){
    Serial.print(symbol);
    Serial.println(data);
  }

void writeDataToSDCard(String type,int data){
      //写入SD卡
  float TimeFS=millis();
  TimeFS=TimeFS/1000;
  type =String(ex_times,DEC)+"_"+type+".csv";
  File dataFile = SD.open(type, FILE_WRITE);
  if (dataFile) {
    String dataString="";
    dataString += TimeFS;
    dataString += ",";
    dataString += data;
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    //Serial.println(dataString);
   }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening "+type);
   }
  //SD卡写入结束
  }
