import ftplib
import os
import time
import math
from subprocess import call
"""
sudo apt-get install imagemagick

"""

###GLOBAL VARIABLES
proccessTime = 40 #Uploads webcam.jpg at xx.[processTime]  seconds


import sys
import signal


#Uploads a file to the webserver
def uploadFile(ftp, file):
	ext = os.path.splitext(file)[1]
	if ext in (".txt",".htm",".html"):
		ftp.storlines("STOR " + file, open(file))
	else:
		ftp.storbinary("STOR " + file, open(file, "rb"), 1024)

#Overwrites the Ctrl-C function
#Uploads the offline picture, and quits the FTP connection
def signal_handler(signal, frame):
	global ftp
	call(["cp","offline.jpeg","webcam.jpeg"])
	uploadFile(ftp, "webcam.jpeg")
	print "\nUploaded offline image..."
	print "Quitting FTP Connection..."
	ftp.quit()
	sys.exit(0)
signal.signal(signal.SIGINT, signal_handler)
		
		
ftp = ftplib.FTP("www.nrpickle.net")
ftp.login("u51571509-wheatley","WheatleyCam")

if __name__ == '__main__':
	count = 0
	image = 1
	avg = .5
	countOvertime = float(0)  #TODO Remove debug
	if len(sys.argv) >= 2:
		countIter = float(sys.argv[1])  #TODO Remove debug; This is number of times to iterate through the test.
	else:
		countIter = 99999999999
		print "Running script without command line args. Using default value. This script should run for " + str(countIter/60/60/24/365) + " years."
		time.sleep(3)

		
	while count < countIter:  #TODO Remove debug
		currentTime = time.time();
		
		call(["streamer","-o","webcam.jpeg"])
		
		while int(math.floor((currentTime*100)%100)) != proccessTime:
			time.sleep(.005)
			currentTime = time.time()
		beginTime = time.time();
		
		print "Begin sequence " + str(count)
		
		
		print "Begin Sequence on " + str(int(math.floor((beginTime*100)%100))),
		print "at " +  str(time.time()%1000)
		print ""
		
		#call(["cp",str(image)+".jpg","webcam.jpg"])
		#if image < 4:
		#	image += 1
		#else:
		#	image = 1
		
		uploadFile(ftp, "webcam.jpeg")
		print "Uploaded File"
		
		#avg += time.time() - beginTime
		#avg /= 2
		print "End sequence. Took " + str(int(((time.time() - beginTime))*1000)) + " ms. \n"
		
		if(int(((time.time() - beginTime))*1000) >= 600):  #TODO Remove debug
			countOvertime += 1
		
		count += 1
		#time.sleep(.05)
	
	#TODO Remove debug
	print "Test complete."
	print "Overtime instances: " + str(countOvertime)
	print "Thats a percentage of: " + str((countOvertime / countIter) * 100) + "%"