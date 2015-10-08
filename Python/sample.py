#!/usr/bin/env python 

import time
import mraa
import serial


def WaitFor(serial, msg, timeOut):
        nbMax = 0
        serial.timeout = timeOut
        currentMsg = ''
        while currentMsg.endswith(msg) != True :
            c = serial.read()
            if c != '' :
                currentMsg += c
            else :
                print 'timeout waiting for ' + msg
                return False
            nbMax = nbMax + 1
            if nbMax > 150:
				print 'Timeout expired'
				return False
        return True

def sendsigfox(data):
	print('Sending SigFox Message...')
	uart = mraa.Uart(0)
	# define sigfox and implicitely makes a sigfox.open()
	sigfox = serial.Serial(
		uart.getDevicePath(),
		baudrate=9600,
		parity=serial.PARITY_NONE,
		stopbits=serial.STOPBITS_ONE,
		bytesize=serial.EIGHTBITS
		)
	sigfox.write('AT\r')
	if (WaitFor(sigfox, 'OK', 3)):
		print('SigFox Modem OK')
	else:
		print('SigFox Modem Error')
		sigfox.close()
		return False
	print("sending data " + data + " to SigFox network:")
	print("Sigfox: AT$SF=" + data + "\r")
	sigfox.write("AT$SF=")
	sigfox.write(data)
	sigfox.write("\r")
	if (WaitFor(sigfox, 'OK', 15)):
		print('Message sent OK')
	else:
		print('Error Sending message')
		sigfox.close()
		return False
	sigfox.close()
	return True

	

sendsigfox("48 45 4c 4c 4f 20 57 4f 52 4c 44")