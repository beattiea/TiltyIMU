'''
magn calibration functions 01

copyright (c) Davide Gironi, 2012

Released under GPLv3.
Please refer to LICENSE file for licensing information.
'''

import sys
import string
import serial
from struct import unpack, pack
from optparse import OptionParser
import time

from sys import stdout
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

#serial port
SERIALPORT = "COM33"
SERIALBAUD = 57600

#serial command to get data
SERGETCOMMAND = '\x22'

#number of read to take for the avarage value
READAVARAGETOT = 500

#total number of points to collect
TOTPOINTS = 1000

#output file name
OUTFILENAME = "magnpoints.txt"

#output file name calibrated
OUTFILENAMECAL = "magnpoints.cal.txt"

#test calibration values
#to obtain those values we need a tool that do elliplse fitting computation,
#something like ellipsoid_fit.m or magneto12.exe
ce = [-99.7, -154.0, -22.7]
m1 = [0.952017, 0.00195895, 0.0139661]
m2 = [0.00195895, 0.882824, 0.00760243]
m3 = [0.0139661, 0.00760243, 0.995365]


#flush input if present
def ser_flush():
	while ser.inWaiting():
		ser.read()
			
#read from serial until the character specified and number of char has reached
def ser_readuntil(untilchar, numchars):
	buf = ""
	bufnum = 0
	done = 0
	while not done:
		#read from serial
		n = ser.read()
		buf = buf + n
		bufnum = bufnum + 1
		#check if this could be the last char
		if n == untilchar:
			#check if the number of char readed is correct
			if bufnum == numchars:
				done = 1
			else:
				done = 1
				buf = ""
				bufnum = 0
	return buf

#read data from chip
def readdata(avaragesamples):
	dataret = [0, 0, 0]
	if avaragesamples > 0:
		datatot = [0, 0, 0]
		dataread = [0, 0, 0]
		#repat read avaragesamples times and avarage values
		for x in range(avaragesamples):
			#send the get values command
			ser.write(SERGETCOMMAND)
			#read values
			line = ser_readuntil('\n', 7)
			i = 1
			datanum = 0
			while i < len(line):
				#combine back the read values
				num = unpack('<h', line[(i-1)] + line[(i-1)+1])
				dataread[datanum] = int(num[0])
				datanum = datanum + 1
				i = i + 2
				if i == len(line):
					break
			datatot[0] = datatot[0] + dataread[0]
			datatot[1] = datatot[1] + dataread[1]
			datatot[2] = datatot[2] + dataread[2]
		dataret[0] = float(datatot[0]) / avaragesamples
		dataret[1] = float(datatot[1]) / avaragesamples
		dataret[2] = float(datatot[2]) / avaragesamples
	else:
		#send the get values command
		ser.write(SERGETCOMMAND)
		#read values
		line = ser_readuntil('\n', 7)
		i = 1
		datanum = 0
		while i < len(line):
			#combine back the read values
			num = unpack('<h', line[(i-1)] + line[(i-1)+1])
			dataret[datanum] = int(num[0])
			datanum = datanum + 1
			i = i + 2
			if i == len(line):
				break
	return dataret


#collect points
def collectpoints():
	ser_flush()

	countpoints = 0
	dataold = [0, 0, 0]
	points = []
	raw_input("move magn in every position to collect correct data, press any key to continue ")
	while countpoints < TOTPOINTS:
		#read data
		data = readdata(0)
		#record only new values, and valid values (not 0)
		if (data[0] == dataold[0] and data[1] == dataold[1] and data[2] == dataold[2]) or (data[0] == 0 and data[1] == 0 and data[2] == 0):
			continue			
		dataold = data
		#collect points
		points.append(data)
		countpoints = countpoints + 1
		stdout.write("\r  read %4d of %4d, get %4d, %4d, %4d" % (countpoints, TOTPOINTS, data[0], data[1], data[2]))
		stdout.flush()
	stdout.write("\n")
	stdout.flush()		
	return points

#plot the collected points
def plotpoints(x, y, z):
	fig = plt.figure()
	
	#set diameter for the estimated sphere
	dia = 0
	for i in x:
		if abs(i) > dia:
			dia = abs(i)
	for i in y:
		if abs(i) > dia:
			dia = abs(i)
	for i in z:
		if abs(i) > dia:
			dia = abs(i)
	
	#generate figure
	ax = fig.add_subplot(111, projection='3d', aspect='equal')
	
	#plot estimated spehre
	u = np.linspace(0, 2 * np.pi, 100)
	v = np.linspace(0, np.pi, 100)
	ex = dia * np.outer(np.cos(u), np.sin(v))
	ey = dia * np.outer(np.sin(u), np.sin(v))
	ez = dia * np.outer(np.ones(np.size(u)), np.cos(v))
	
	#plot points
	ax.plot_wireframe(ex, ey, ez, rstride=4, cstride=4, color='grey', alpha=0.5)
	ax.scatter(x, y, z)
	ax.set_xlabel('X')
	ax.set_ylabel('Y')
	ax.set_zlabel('Z')
	plt.show()
	
#main function			
if __name__ == '__main__':
	print "Magnetometer Calibration functions 01"
	print ""
	
	parser = OptionParser()
	parser.add_option("-d", "--debug", dest="opt_debug", action="store_true", help="debug output")
	parser.add_option("-g", "--get", dest="opt_get", action="store_true", help="collect data from chip")
	parser.add_option("-p", "--plot", dest="opt_plot", action="store_true", help="plot raw values collected")
	parser.add_option("-t", "--testcalib", dest="opt_testcalib", action="store_true", help="compute estimation of collected data and do plot, need calibration points to be setup with other script")
	(options, args) = parser.parse_args()

	if options.opt_debug:
		print "Debug output"
		
		#set serial port
		ser=serial.Serial(port=SERIALPORT, baudrate=SERIALBAUD , bytesize=serial.EIGHTBITS, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, timeout=1)
		ser.close()
		ser.open()
		if ser.isOpen():
			print ("Port " + ser.portstr + " opened")
		
			while 1:
				data = readdata(0)
				print "  read %d %d %d " % (data[0], data[1], data[2])
				time.sleep(0.5)
			
			ser.close()
		else:
			print ("Can not oper port")
			
	elif options.opt_get:
		print "Collect data from chip"
		
		#set serial port
		ser=serial.Serial(port=SERIALPORT, baudrate=SERIALBAUD , bytesize=serial.EIGHTBITS, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, timeout=1)
		ser.close()
		ser.open()
		if ser.isOpen():
			print ("Port " + ser.portstr + " opened")
							
			while 1:
				#collect points
				points = collectpoints()
				
				#output points to file
				out_file = open(OUTFILENAME,"w")
				for i in range(0, TOTPOINTS):
					s = str(points[i][0])+"\t"+str(points[i][1])+"\t"+str(points[i][2])+"\n"
					out_file.write(s)
				out_file.close()
	
				#plot points
				raw_input("plot raw points, press any key to continue ")
				x = []
				y = []
				z = []
				for i in range(0, TOTPOINTS):
					x.append(points[i][0])
					y.append(points[i][1])
					z.append(points[i][2])
				plotpoints(x, y, z)
	
				print ""
				readkey = raw_input("press any key to repeat reading, or X to exit ")
				if readkey == "X" or readkey == "x":
					break
			
			ser.close()
		else:
			print ("Can not oper port")
	
	elif options.opt_testcalib:
		print "Test calibration data using input file %s for raw values" % OUTFILENAME
		
		x = []
		y = []
		z = []
		num_samples = 0
		
		#read points from file
		in_file = open(OUTFILENAME,"r")
		while 1:
			in_line = in_file.readline()
			if not in_line:
				break
			num_samples = num_samples+1
			[a,b,c] = string.split(in_line,'\t')
			x.append(float(a))
			y.append(float(b))
			z.append(float(c))
		in_file.close()
		
		#plot uncalibrated
		raw_input("plot raw points, press any key to continue ")
		plotpoints(x, y, z)
		
		#hard iron correction (offset)
		for i in range(0,num_samples):
			x[i] -= ce[0]
			y[i] -= ce[1]
			z[i] -= ce[2]
		#soft iron correction (rotation)
		for i in range(0,num_samples):
			tx = x[i]
			ty = y[i]
			tz = z[i]
			x[i] = m1[0] * tx + m1[1] * ty + m1[2] * tz;
			y[i] = m2[0] * tx + m2[1] * ty + m2[2] * tz;
			z[i] = m3[0] * tx + m3[1] * ty + m3[2] * tz;
		
		#plot calibrated
		raw_input("plot calibrated points, press any key to continue ")
		plotpoints(x, y, z)
		
		#write calibrated output file
		print "write calibrated point to file %s" % OUTFILENAMECAL
		out_file = open(OUTFILENAMECAL,"w")
		for i in range(0,num_samples):
			s = str(x[i])+"\t"+str(y[i])+"\t"+str(z[i])+"\n"
			out_file.write(s)
		out_file.close()
	
	elif options.opt_plot:
		print "Plot data, read data from input file %s" % OUTFILENAME
	
		x = []
		y = []
		z = []
		num_samples = 0
		
		#input points from file
		in_file = open(OUTFILENAME,"r")
		while 1:
			in_line = in_file.readline()
			if not in_line:
				break
			num_samples = num_samples+1
			[a,b,c] = string.split(in_line,'\t')
			x.append(float(a))
			y.append(float(b))
			z.append(float(c))
		in_file.close()

		#plot points
		raw_input("plot raw points, press any key to continue ")
		plotpoints(x, y, z)
	
	else:
		parser.print_help()
