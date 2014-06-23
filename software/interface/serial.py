from subprocess import call
import time

def outputSerial(charToOutput):
	pass
#	call(["./

if __name__ == "__main__":
	print "Hello world!"
	while(1):
		call(["./serial",'b'])
		time.sleep(1)
		call(["./serial",'o'])
		time.sleep(1)

