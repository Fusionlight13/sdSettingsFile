
#Setting Configuration File

This is a library that lets you easily make a configuration file and then update and read the values with few lines of code.
## Usage/Examples

```c++
#include <sdSettings.h>
//Location of file, Chip Select, Amount of lines being used.
sdSettings myCard("MYSETT~1.TXT", 4, 10);
void setup() {
  
  
  Serial.begin(9600);
  //Runs the SD initial code.
  myCard.SDInit();
  //Extracts all the lines from the text file and stores it into an array.
  myCard.readSD(false);
  //Splits the name and value of the line into separate arrays to access publically.
  myCard.unpackAndSplit(false);
  //Loop through all the settings using the returned length of the arrays.
  for(int a = 0; a < myCard.returnLineCount() ; a++)
  {
    Serial.print(myCard.settingName[a]);
    Serial.print(": ");
    Serial.print(myCard.settingValue[a]);
    Serial.println();
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
