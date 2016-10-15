#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> //This is the sleep library

//Declaring All States
#define INIT 0
#define CONNECT_WIFI 1
#define WRITING_LOCAL 2
#define WRITING_WEB 3
#define DISCONNECT_WIFI 4
#define SLEEP 5

//Delcare all Constant variables
#define NUM_READ 5

int main(){
  //Declare Dynamic Variables
  float TEMP_READINGS[NUM_READ];
  float HUM_READINGS[NUM_READ];
  int CONNECTED;
  //BEGIN MAIN LOOP
  int state = INIT;
  while(1){
    switch(state){

        case INIT:
          //////////
          //READ FROM SENSOR AND WRITE TO TEMP_READING AND HUM_READINGS ARRAY
          //////////

          //////////
          //FIND AVERAGE READING VALUE
          //////////
          printf("READ FROM SENSOR\n");
          state = CONNECT_WIFI;
          break;

        case CONNECT_WIFI:
          //////////
          //CONNECT TO THE WIFI
          //////////
          CONNECTED = 0; //This is for testing
          if(CONNECTED){
            state = WRITING_WEB;
          }
          else{
            state = WRITING_LOCAL;
          }
          printf("CONNECTING TO WIFI\n");
          break;

        case WRITING_LOCAL:
          ////////////
          //WRITE THE VALUE LOCALLY
          ////////////
          printf("WRITING LOCALLY\n"); 
          state = SLEEP;
          break;

         case WRITING_WEB:
          /////////////
          //WRITE THE VALUE TO THE WEB
          /////////////
          printf("WRITING TO WEB\n");
          state = DISCONNECT_WIFI;
          break;

         case DISCONNECT_WIFI:
          /////////////
          //DISCONNECT FROM THE WIFI
          /////////////
          printf("DISCONNECTING FROM WIFI\n");
          state = SLEEP;
          break;

         case SLEEP:
          //////////
          //SLEEP
          //////////
          printf("SLEEP\n");
          sleep(4);
          state = INIT;
          break;
        }
  }

  return 0;
}
