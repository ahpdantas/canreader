#!/usr/bin/python
# -*- coding: iso-8859-1 -*-
import serial

port = 'com4'
baud_rate = 115200

ser = serial.Serial(port, baud_rate)
while True:
    byte = int.from_bytes(ser.read(), byteorder='little')
    print("{:02x}:".format(byte), end ='')
    if  byte == 0x04:
        print("\n")
