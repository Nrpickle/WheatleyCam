import ftplib
import os

def uploadFile():
	file = "webcam.jpg"
	ftp = ftplib.FTP("www.nrpickle.net")
	ftp.login("u51571509-wheatley","WheatleyCam")
	ext = os.path.splitext(file)[1]
	if ext in (".txt",".htm",".html"):
		ftp.storlines("STOR " + file, open(file))
	else:
		ftp.storbinary("STOR " + file, open(file, "rb"), 1024)
	ftp.quit()

if __name__=='__main__':
	uploadFile()