import Adafruit_DHT
import RPi.GPIO as GPIO
import time
from DHT11 import DHT11

# initialize GPIO
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
GPIO.cleanup()

# Sensor should be set to Adafruit_DHT.DHT11,
# Adafruit_DHT.DHT22, or Adafruit_DHT.AM2302.
#sensor = Adafruit_DHT.DHT22
sensor = Adafruit_DHT.DHT11

# Example using a Raspberry Pi with DHT sensor
# connected to GPIO23.
pin = 16

# Try to grab a sensor reading.  Use the read_retry method which will retry up
# to 15 times to get a sensor reading (waiting 2 seconds between each retry).

for i in range(0, 60):
	
	instance = DHT11(pin = pin)

	# humidity, temperature = Adafruit_DHT.read(sensor, pin)
	result = instance.read()
	temperature = None
	humidity = None

	if result.is_valid():
    		print("Temperature: %d C" % result.temperature)
    		print("Humidity: %d %%" % result.humidity)
		humidity = result.humidity
		temperature = result.temperature

		print("{4} -- S: {3} P: {2} H: {0} T: {1}".format(humidity, temperature, pin, sensor, i))
	else:
    		print("Error: %d" % result.error_code)



	# Note that sometimes you won't get a reading and
	# the results will be null (because Linux can't
	# guarantee the timing of calls to read the sensor).
	# If this happens try again!
	if humidity is not None and temperature is not None:
		print('\tTemp={0:0.1f}*C  Humidity={1:0.1f}%'.format(temperature, humidity))
	else:
		print('\tFailed to get reading. Try again!')
	time.sleep(1)

#GPIO.cleanup() 

