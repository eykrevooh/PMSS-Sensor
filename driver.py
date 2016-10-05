import time

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
    #### BEGIN MAIN LOOP ####
    state = INIT
    while(True):
        if state == INIT:
            try:
                #################
                #Read from Sensor
                #Insert Sensor Reading Code Here
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
                ###############
                #Write to the Web
                #INSERT Web Writing Here
                ###############
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
