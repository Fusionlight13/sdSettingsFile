#include <sdSettings.h>
#include <SPI.h>
#include <SD.h>
#include <Arduino.h>

sdSettings::sdSettings(String fileLocation, int chipSelect, int maxLines)
{
    _maxLines = maxLines;
    _fileLocation = fileLocation;
    _lines = new String[_maxLines];
    _settingName = new String[_maxLines];
    _settingValue = new String[_maxLines];
    _chipSelect = chipSelect;
}

void sdSettings::SDInit()
{
    Serial.begin(9600);
    while (!Serial)
    {
        ;
    }
    if (!SD.begin(_chipSelect))
    {
        Serial.println("Card failed, or not present");
        // don't do anything more:
        while (1)
        {
            ;
        }
    }
    Serial.println("card initialized.");
}

void sdSettings::readSD(bool debugMode = true)
{
    int lineCount = 0;
    File myData;

    if (fileExists())
    {
        myData = SD.open(_fileLocation, FILE_READ);
        debugMessage("File opened!", debugMode);
    }
    else
    {
        debugMessage("File did not open correctly", debugMode);
        return;
    }

    if (myData)
    {
        while (myData.available() && lineCount < _maxLines)
        {
            String line = myData.readStringUntil('\n');
            line.trim();
            _lines[lineCount] = line;
            lineCount++;
        }
        _lineCount = lineCount; //Needs to run this line just once in the program so it can access it globally in the read/unpack/and pack functions.
        myData.close();
    }
    else
    {
        debugMessage("Error opening file.", debugMode);
    }
}

void sdSettings::packAndSave(bool debugMode = true)
{
    SD.remove(_fileLocation);
    File myData = SD.open(_fileLocation, FILE_WRITE);
    if (fileExists())
    {
        if (myData)
        {
            for (int a = 0; a < _lineCount; a++)
            {
                String fullLine = String(_settingName[a]) + String(": ") + String(_settingValue[a]);
                debugMessage(fullLine, debugMode);
            }
        }
    }
    else
    {
        debugMessage("Critical error occured overwritting settings file!", true);
    }
}

void sdSettings::unpackAndSplit(bool debugMode = true)
{
    for (int i = 0; i < _lineCount; i++)
    {
        String currentLine = _lines[i];
        debugMessage("Unpacking Line " + String(i) + String(": "), debugMode);
        debugMessage(currentLine, debugMode);

        int colonIndex = currentLine.indexOf(':');
        String value = currentLine.substring(colonIndex + 1, _lines[i].length());
        String primary = currentLine.substring(0, colonIndex);
        primary.trim();
        value.trim();
        debugMessage(value, debugMode);
        _settingName[i] = primary;
        _settingValue[i] = value;

    }
}

int sdSettings::returnLineCount()
{
    return _lineCount;
}

bool sdSettings::fileExists()
{
    return SD.exists(_fileLocation);
}

void sdSettings::debugMessage(String message, bool debugMode)
{
    if (debugMode)
    {
        Serial.println(message);
    }

}

void sdSettings::setOption(String name, String value, int placement)
{
    _settingName[placement] = name;
    _settingValue[placement] = value;
}

void sdSettings::returnOption(String& name, String& value, int placement)
{
    name = _settingName[placement];
    value = _settingValue[placement];
}
