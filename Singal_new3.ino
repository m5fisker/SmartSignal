
#include <VirtualWire.h>
//Variables for LED
int sig[4][3] = {13,12,11,10,9,8,7,6,5,4,3,2};
int tim; //Instatneous Time
int sigg=1;//Variable for if loop
int timtemp; //Variable passed to the delay function

void setup() 
{
  vw_set_ptt_inverted(true); 
  vw_set_rx_pin(14);
  vw_setup(4000); 
  vw_rx_start();
  int i,j;
  for(i=0;i<4;i++)//Loop for junction
  for(j=0;j<3;j++)//Loop for signal
  pinMode(sig[i][j], OUTPUT);
}

void loop() 
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  int j1s1=analogRead(A0);//LDR sesor 1 value
  int j1s2=analogRead(A1);//LDR sesor 2 value
  int j1s3=analogRead(A2);//LDR sesor 3 value
  
  int j2s1=analogRead(A3);//LDR sesor 4 value
  int j2s2=analogRead(A4);//LDR sesor 5 value
  int j2s3=analogRead(A5);//LDR sesor 6 value
  
  int j3s1=analogRead(A6);//LDR sesor 7 value
  int j3s2=analogRead(A7);//LDR sesor 8 value
  int j3s3=analogRead(A8);//LDR sesor 9 value
  
  int j4s1=analogRead(A9);//LDR sesor 10 value
  int j4s2=analogRead(A10);//LDR sesor 11 value
  int j4s3=analogRead(A11);//LDR sesor 12 value

  //First junctuion
  if(sigg==1)
  {
    stateGo(0);
    statePause(1);
     if (vw_get_message(buf, &buflen)) // Non-blocking
     {
      if(buf[0]=='1')
      {
        timtemp=45000;
      }
    
       else 
       {
         if(j2s1<500&&j2s2>500&&j2s3>500)
          {
             tim=15000;
          }
         else if(j2s1<500&&j2s2<500&&j2s3>500)
          {
            tim=30000;
          }
          else if(j2s1<500&&j2s2<500&&j2s3<500)
          {
            tim=45000;
          }
          else
          {
            tim=10000;
          }
          timtemp=tim;
          sigg=2;
        }
     }
  }

  //Second Junction
    if(sigg==2)
    {
           stateGo(1);
           statePause(2);
            if (vw_get_message(buf, &buflen)) // Non-blocking
           {
            if(buf[0]=='1')
            {
              timtemp=45000;
            }
    
           else 
           {
             if(j3s1<500&&j3s2>500&&j3s3>500)
              {
                 tim=15000;
              }
             else if(j3s1<500&&j3s2<500&&j3s3>500)
              {
                tim=30000;
              }
              else if(j3s1<500&&j3s2<500&&j3s3<500)
              {
                tim=45000;
              }
              else
              {
                tim=10000;
              }
              timtemp=tim;
              sigg=3;
           }
       }
    }

  //Third Junction
 if(sigg==3)
{
     stateGo(2);
     statePause(3);
       if (vw_get_message(buf, &buflen)) // Non-blocking
     {
      if(buf[0]=='1')
      {
        timtemp=45000;
      }
    
         else 
         {
          if(j4s1<500&&j4s2>500&&j4s3>500)
          {
             tim=15000;
          }
         else if(j2s1<500&&j2s2<500&&j2s3>500)
        {
          tim=30000;
        }
          else if(j2s1<500&&j2s2<500&&j2s3<500)
          {
            tim=45000;
          }
          else
          {
            tim=10000;
          }
          timtemp=tim;
          sigg=4;
         }
     }
 }

  //Fourth Junction
    if(sigg==4)
    {
     stateGo(3);
    statePause(0);
      if (vw_get_message(buf, &buflen)) // Non-blocking
     {
      if(buf[0]=='1')
      {
        timtemp=45000;
      }
    
       else 
       {
          if(j1s1<500&&j1s2>500&&j1s3>500)
            {
               tim=15000;
            }
           else if(j2s1<500&&j2s2<500&&j2s3>500)
            {
              tim=30000;
            }
            else if(j2s1<500&&j2s2<500&&j2s3<500)
            {
              tim=45000;
            }
            else
            {
              tim=10000;
            }
            timtemp=tim;
            sigg=1;
        }
     }
  }
}

//Activation for the current Signal
  void stateGo(int k)
  {
     
     //all lights are turned off for a fraction of a second.
     int i,j;
      for(i=0;i<4;i++)
        for(j=0;j<3;j++)
          digitalWrite(sig[i][j],LOW);
          
      //all roads except the 'k'th road is red.
      for(i=0;i<4;i++)
        if(i!=k)
          digitalWrite(sig[i][0],HIGH);
      
      //kth road is green.
      digitalWrite(sig[k][2],HIGH);
      
      //wait according to the value
      delay(timtemp);
      
      //blink green as a "hurry up" warning for next 6 seconds
      for(i=0;i<6;i++)
      {
        digitalWrite(sig[k][2],LOW);
        delay(500);
        digitalWrite(sig[k][2],HIGH);
        delay(500);
    }
}

//defines signal statuses when the 'k' th signal is "ready to go"
//'k-1'th signal is returning from green.

//
void statePause(int k)
{
  int i,j;
  int p = k-1;
  if(p==-1)
    p=3;
    
  //turn off all lights for a fraction of a second.
  for(i=0;i<4;i++)
      for(j=0;j<3;j++)
        digitalWrite(sig[i][j],LOW);
        
  //all red lights except p (i.e k-1) are red.
  for(i=0;i<4;i++)
    if(i!=p)
          digitalWrite(sig[i][0], HIGH);
  
  //also  p and k roads have yellow
  digitalWrite(sig[p][1],HIGH);
  digitalWrite(sig[k][1],HIGH);
  }
}

 
