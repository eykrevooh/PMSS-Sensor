import time

def main():
    INIT = 0
    CONNECT_WIFI = 1
    WRITTING_LOCAL = 2
    WRITTING_WEB = 3
    ERROR = False

    state = INIT
    while(True):
        if state == INIT:
            try:
                 #Read from Sensor
                 print "READING FROM SENSOR"
                 state = CONNECT_WIFI
            except:
                ERROR = True
        if state == CONNECT_WIFI:
            try:
                #Connect to WIFI
                connect = True # This variable is set wether its connected
                if connect == True:
                    print "CONNECTED TO WEB"
                    state = WRITTING_WEB
                else:
                    print "FAILED TO CONNECT TO WEB"
                    state = WRITTING_LOCAL
            except:
                ERROR = True
        if state == WRITTING_WEB:
            try:
                #write to the web
                print "WRITTING TO WEB"
                state = WRITTING_LOCAL #This is for debugging and later will switch to INIT
            except:
                ERROR = True
        if state == WRITTING_LOCAL:
            try:
                #write locally
                print "WRITTING LOCALLY"
                state = INIT
            except:
                ERROR =True
        if ERROR:
            #Write error locally
            print "ERROR OCCURED"
            ERROR = False
        time.sleep(8)
    return 0

main()
