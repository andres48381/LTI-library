#include <stdio.h>      /* printf */
#include <time.h>       /* time_t, struct tm, difftime, time, mktime */
#include <iostream>

#include <Modelo.h>

using namespace std;

int main() {

  Modelo myModel("myModel",0,0,13,0,0,0); //only one pole, with "t=13" -> 13seg to reach 63% of final value

  time_t time0;
  time0 = time(NULL);
  float comandValue= 10; ///For example we want 10V of bus bar voltage
  float actualValue = 0; //initial voltage
  float acceptValue = 0.98; //98% final value

  //main control loop
  //while final value is under 98%
  while(actualValue< acceptValue*comandValue)
  {
    if(!myModel.ModeloStarted())
    {
      myModel.StartModelo(time(NULL)-time0,comandValue,0);
    } 

    myModel.Check_K(time(NULL)-time0,comandValue); //Refresh each second
    myModel.Update(time(NULL)-time0);
    actualValue = myModel.GetValue();
    //Refresh gauge voltageindicator. Example
    //setGaugeVoltage(actualValue); 
    cout <<"time: "<< (time(NULL)-time0) << " | reference: " << comandValue << "| actualValue: "<<actualValue<<endl;
  }

  cout <<"stopping model"<<endl;;
  //out control loop, if the model has to be stopped and restarted
  myModel.StopModelo();

  return 0;
}
