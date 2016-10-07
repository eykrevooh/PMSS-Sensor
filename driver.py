import time
import dweepy

def senddata(dev_name, temp, hum):
    '''dev_name is the device name paramater <string>
    temp is the tempature value paramater <float>
    hum is the humidity value paramter <float>'''
def main():
    ##
    #### STATE DECLERATIONS ####
    INIT = 0
    CONNECT_WIFI = 1
    WRITING_LOCAL = 2
    WRITING_WEB = 3
    SLEEP = 4
    ERROR = False
    ##
    #### Varialbes ####
    ##
    TEMP = 0
    HUM  = 0
    #### BEGIN MAIN LOOP ####
    state = INIT
    while(True):
        if state == INIT:
            try:
                #################
                #Read From Sensor
                #Insert Sensor Reading Code Here
                #Record Humidity Reading as HUM
                #Record Temp Reading as TEMP
                #################
                print "READING FROM SENSOR"
                state = CONNECT_WIFI
            except:
                ERROR = True
        elif state == CONNECT_WIFI:
            try:
                ################
                #Connect to WIFI
                #INSERT Wifi Connection Code Here
                ################
                connect = True #TEMP; This is for testing until Wifi code added
                if connect == True:
                    print "CONNECTED TO WEB"
                    state = WRITING_WEB
                else:
                    print "FAILED TO CONNECT TO WEB"
                    state = WRITING_LOCAL 
            except:
                ERROR = True
        elif state == WRITING_WEB:
            try:
                  # define each of the keys for sending the temperature and humidity data 
                dev_name = "pine_mountain_sensor_1"
                tempkey = dev_name + "_temp"
                humkey = dev_name + "_hum"
                dweepy.dweet_for(tempkey, {'temp': TEMP})
                dweepy.dweet_for(humkey, {'hum': HUM})
                print "WRITING TO WEB"
                state = WRITING_LOCAL #This is for debugging and later will switch to INIT
            except:
                ERROR = True
        elif state == WRITING_LOCAL:
            try:
                ##############
                #Write to Local Storage
                #INSERT Local Storage Code Here
                ##############
                print "WRITING LOCALLY"
                state = SLEEP
            except:
                ERROR =True
        elif state == SLEEP:
            time.sleep(8)
            state = INIT
        if ERROR:
            ################
            #Write error locally
            #INSERT Error Recording Code Here
            ################
            print "ERROR OCCURED"
            ERROR = False
        
    return 0

main()
