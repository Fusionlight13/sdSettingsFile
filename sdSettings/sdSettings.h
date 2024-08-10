#ifndef sdSettings_h
#define sdSettings_h

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

class sdSettings
{
    public:
        sdSettings(String fileLocation, int chipSelect, int maxLines);
        void SDInit();
        void readSD(bool debugMode);
        void packAndSave(bool debugMode);
        void unpackAndSplit(bool debugMode);
        int returnLineCount();
        String* settingName;
        String* settingValue;

    private:
        String _fileLocation;
        int _maxLines;
        int _chipSelect;
        int _lineCount;
        String* _lines;
        bool fileExists();
        void debugMessage(String message, bool debugMode);


     

};

#endif