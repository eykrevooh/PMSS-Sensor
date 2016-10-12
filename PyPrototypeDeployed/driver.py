import time
import dweepy
import sys
import datetime
import Adafruit_DHT
import RPi.GPIO as GPIO
from DHT11 import DHT11
import math
import os

# initialize GPIO
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
GPIO.cleanup()

# Debug Levels
NO_DEBUG  = 0
INFO      = 10
WARN      = 20
ALL       = 1000

SENSOR_ID = "bat"
DEBUG_LEVEL = ALL

# The native library for the DH11 uses board numbers
USE11 = True
DHT11PIN = 16

# The Adafruit Library for the DHT22 uses GPIO numbers
USE22 = True
DHT22PIN = 4

# This is the dictionary we send to Freeboard.
PACKAGE = {}

# Number of times we'll retry a dead sensor.
READRETRY = 5

def readFromDHT22 (pin):
  debug(INFO, "Attempting to read DHT22 on pin {0}".format(pin))
  HUMI, TEMP = None, None
  count = 0
  while ((HUMI == None) or (TEMP == None)) and (count < READRETRY):
      HUMI, TEMP = Adafruit_DHT.read(Adafruit_DHT.DHT22, pin)
      debug(INFO, "In Function DHT22 H: {0}, T: {1}".format(HUMI, TEMP))
      time.sleep(1)
      count += 1
      
  if HUMI == None:
    HUMI = 0
  if TEMP == None:
    TEMP = 0
    
  return (HUMI, TEMP)

def readFromDHT11 (pin):
  instance = DHT11(pin = pin)
  TEMP = None
  HUMI = None
  count = 0 
  while ((HUMI == None) or (TEMP == None)) and (count < READRETRY):
      result = instance.read()
      debug(INFO, "In Function DHT11 H: {0}, T: {1}".format(result.humidity, result.temperature))
      if result.is_valid():
          TEMP = result.temperature
          HUMI  = result.humidity
      time.sleep(1)
      count += 1
  
  if HUMI == None:
    HUMI = 0
  if TEMP == None:
    TEMP = 0

  return (HUMI, TEMP)

def sendLogFiles ():
  try:
    os.system("scp DHT11.log jadudm@cs.berea.edu:/home/jadudm/www/pmss/{0}-DHT11.log".format(SENSOR_ID))
    os.system("scp DHT22.log jadudm@cs.berea.edu:/home/jadudm/www/pmss/{0}-DHT22.log".format(SENSOR_ID))
    os.system("scp errors.log jadudm@cs.berea.edu:/home/jadudm/www/pmss/{0}-errors.log".format(SENSOR_ID))
  except Exception as e:
    debug (WARN, "Could not send log files.")
    f = open('errors.log', 'a')
    f.write("{0},{1},{2},{3},{4}\n".format(datetime.datetime.now(), "ERROR", 0, 0, e))
    f.close()


def avg (ls):
	sum = 0
	for i in ls:
		sum += i
	return math.floor(sum / len(ls))

def debug (lvl, string):
  if DEBUG_LEVEL >= lvl:
    print(string)

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
  #### Variables ####
  ##
  TEMP11  = None
  HUMI11  = None
  TEMP22  = None
  HUMI22  = None

  #### BEGIN MAIN LOOP ####
  state = INIT
  while(True):
    if state == INIT:
      try:
        #################
        debug(INFO, "READING FROM SENSOR")

        TEMPERATURES11 = []
        TEMPERATURES22 = []
        HUMIDITIES11 = []
        HUMIDITIES22 = []

        counter = 0 

        while counter < 5:
          if USE11:
            HUMI11, TEMP11 = readFromDHT11(DHT11PIN)
            TEMPERATURES11.append(TEMP11)
            HUMIDITIES11.append(HUMI11)
            debug(INFO, "S: {3} P: {2} H: {0} T: {1}".format(HUMI11, TEMP11, DHT11PIN, "DHT11"))

          if USE22:
            HUMI22, TEMP22 = readFromDHT22(DHT22PIN)
            TEMPERATURES22.append(TEMP22)
            HUMIDITIES22.append(HUMI22)
            debug(INFO, "S: {3} P: {2} H: {0} T: {1}".format(HUMI22, TEMP22, DHT22PIN, "DHT22"))

          counter += 1

        #Insert Sensor Reading Code Here
        #Record Humidity Reading as HUM
        #Record Temp Reading as TEMP
        #################
        if USE11: 
          debug (INFO, "T11: {0}".format(TEMPERATURES11))
          debug (INFO, "H11: {0}".format(HUMIDITIES11))
          TEMP11 = avg(TEMPERATURES11)
          HUMI11 = avg(HUMIDITIES11)
          PACKAGE["temp_11"] = TEMP11
          PACKAGE["humi_11"] = HUMI11
          
        if USE22:
          debug (INFO, "T22: {0}".format(TEMPERATURES22))
          debug (INFO, "H22: {0}".format(HUMIDITIES22))
          TEMP22 = avg(TEMPERATURES22)
          HUMI22 = avg(HUMIDITIES22)
          PACKAGE["temp_22"] = TEMP22
          PACKAGE["humi_22"] = HUMI22
          
        state = CONNECT_WIFI
      except Exception as e:
        ERROR = e
        
    elif state == CONNECT_WIFI:
      try:
        ################
        #Connect to WIFI
        #INSERT Wifi Connection Code Here
        ################
        connect = True #TEMP; This is for testing until Wifi code added
        
        if connect == True:
          debug(INFO, "CONNECTED TO WEB")
          state = WRITING_WEB
        else:
          debug(INFO, "FAILED TO CONNECT TO WEB")
          state = WRITING_LOCAL 
      except Exception as e:
        ERROR = e
    elif state == WRITING_WEB:
      try:
        debug(INFO, "WRITING TO WEB")
        ###############
        #Write to Dweepy
        # define each of the keys for sending the temperature and humidity data 
        ###############
        dev_name = "org_pmss_berea_{0}".format(SENSOR_ID)
        debug(INFO, dweepy.dweet_for(dev_name, PACKAGE))
        
        state = WRITING_LOCAL #This is for debugging and later will switch to INIT
      except Exception as e:
        ERROR = e
    elif state == WRITING_LOCAL:
      try:
        print "WRITING LOCALLY"
        ##############
        #Write to Local Storage        
        ##############
        if USE11:
          f = open('DHT11.log', 'a')
          f.write("{0},{1},{2},{3},{4}\n".format(datetime.datetime.now(), "DHT11", TEMP11, HUMI11, "OK"))
          f.close()
        if USE22:
          f = open('DHT22.log', 'a')
          f.write("{0},{1},{2},{3},{4}\n".format(datetime.datetime.now(), "DHT22", TEMP22, HUMI22, "OK"))
          f.close()
        
        sendLogFiles()
        state = SLEEP
        
      except Exception as e:
        debug(WARN, "Unexpected error:", sys.exc_info()[0])
        ERROR = e
    elif state == SLEEP:
      debug(INFO, "SLEEP")
      time.sleep(8)
      state = INIT
    if ERROR:
      ################
      #Write error locally
      debug(WARN, ERROR)
      f = open('errors.log', 'a')
      f.write("{0},{1},{2},{3},{4}\n".format(datetime.datetime.now(), "ERROR", 0, 0, e))
      f.close()

      #INSERT Error Recording Code Here
      ################
      debug (WARN, "ERROR OCCURED")
      ERROR = False
      state = SLEEP
          
  return 0

main()
