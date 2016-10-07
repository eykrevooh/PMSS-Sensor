import dweepy
import time

def senddata(dev_name, temp, hum):
    '''
    dev_name is the device name paramater <string>
    temp is the tempature value paramater <float>
    hum is the humidity value paramter <float>
    '''
    # define each of the keys for sending the temperature and humidity data 
    tempkey = dev_name + "_temp"
    humkey = dev_name + "_hum"
    
    #Send the data to dweet.io
    dweepy.dweet_for(tempkey, {'temp': temp})
    dweepy.dweet_for(humkey, {'hum': hum})

temperature = 0
humidity = 0 
while(True):
    senddata('pine_mountain_sensor_1', temperature, humidity)
    senddata('pine_mountain_sensor_2', temperature, humidity)
    senddata('pine_mountain_sensor_3', temperature, humidity)
    senddata('pine_mountain_sensor_4', temperature, humidity)
    senddata('pine_mountain_sensor_5', temperature, humidity)
    time.sleep(1)
    temperature += 1
    humidity += 1
    
    if (temperature == 100 or humidity == 100):
        temperature = 0
        humidity = 0
