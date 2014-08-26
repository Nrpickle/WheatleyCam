import math
import urllib2
import time
import sys

"""
Developed by Nick McComb for OSURC
April 2014
mccombn@onid.orst.edu

The first 10 lines of the retrieved file are reserved for comments and documentation
"""

def getData():
	req = urllib2.Request('http://groups.engr.oregonstate.edu/osurc/cam/data.txt')
	response = urllib2.urlopen(req)
	the_page = response.read()
	splitResult = the_page.split('\n')
	info = splitResult
	variablesIn = info[5]
	variablesIn = variablesIn.split(',')
	data = {}
	for i in variablesIn:
		temp = i.split(':')
		data[temp[1]] = info[int(temp[0])]
	return data
	
if __name__ == "__main__":
	data = getData()
	print "The name of the current project is: " + str(data['projectName'])	+ '\n'
	
	if(len(sys.argv) > 1): #Command line arg recieved
		if(sys.argv[1] == "vars"):  #Output the variables that can be used
			print "The current available variables (and their values) are:"
			print data
		else:
			print "That is an invalid command line argument. Please try again."
	
	print "Begin Test:"	
	while 1:
		data = getData() 
		for i in range(int(data['status'])):
			print '#',
		print '\n',
		time.sleep(.25)
