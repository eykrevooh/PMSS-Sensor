import dweepy

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