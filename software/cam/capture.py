from subprocess import call
import time

while(1): 
	beginTime = time.time()
	call(["streamer","-o","webcam.jpeg"])
	print "Took " + str(time.time() - beginTime)[0:4] + " seconds"
	time.sleep(1)