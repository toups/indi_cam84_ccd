#ifndef CAM84CCD_H
#define CAM84CCD_H

/*
   Code derived from:

   INDI Developers Manual
   Tutorial #3

   "Simple CCD Driver"

 */

/** \file simpleccd.h
    \brief Construct a basic INDI CCD device that simulates exposure & temperature settings. It also generates a random pattern and uploads it as a FITS file.
    \author Jasem Mutlaq

    \example simpleccd.h
    A simple CCD device that can capture images and control temperature. It returns a FITS image to the client. To build drivers for complex CCDs, please
    refer to the INDI Generic CCD driver template in INDI SVN (under 3rdparty).
*/


class Cam84CCD : public INDI::CCD
{
public:
    Cam84CCD();

    bool ISNewNumber (const char *dev, const char *name, double values[], char *names[], int n);
    bool ISNewSwitch (const char *dev, const char *name, ISState *states, char *names[], int n);


protected:
    // General device functions
    bool Connect();
    bool Disconnect();
    const char *getDefaultName();
    bool initProperties();
    bool updateProperties();

    // CCD specific functions
    bool StartExposure(float duration);
    bool AbortExposure();
    int SetTemperature(double temperature);
    void TimerHit();

private:
   // Utility functions
    float CalcTimeLeft();
    void  setupParams();
    void  grabImage();

    // Are we exposing?
    bool InExposure;
    // Struct to keep timing
    struct timeval ExpStart;

    INumber GainN[1];
    INumberVectorProperty GainNP;

    INumber OffsetN[1];
    INumberVectorProperty OffsetNP;

    INumber BaudrateDivisorN[1];
    INumberVectorProperty BaudrateDivisorNP;

    INumber LibftditimerAN[1];
    INumberVectorProperty LibftditimerANP;

    INumber LibftdilatencyAN[1];
    INumberVectorProperty LibftdilatencyANP;

    INumber LibftditimerBN[1];
    INumberVectorProperty LibftditimerBNP;

    INumber LibftdilatencyBN[1];
    INumberVectorProperty LibftdilatencyBNP;
	
	ISwitch ContinuousADToggle[1];
	ISwitchVectorProperty ContinuousADToggleP;

    float ExposureRequest;
    float TemperatureRequest;
    int   timerID;

};

#endif // CAM84CCD_H
