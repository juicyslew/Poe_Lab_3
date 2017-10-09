#!/usr/local/bin/python

from serial import Serial, SerialException
import pickle as pk
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from math import cos, sin, pi

cxn = Serial('/dev/ttyACM0', baudrate=9600)
threshold = 400
count = 0;
IR_Data = [];
IR_Data2 = [];
fname = 'LastSessionData.pkl'
while(True):
    try:
        cxn.write([1])
        while cxn.inWaiting() < 1:
            pass
        result = str(cxn.readline());

        result = result.split("|");
        result = [int(i) for i in result]
        IR_Data.append(result[0])
        IR_Data.append(result[1])
        tape = [i < threshold for i in result]
        #if any(tape):
        #    print(result)
        if count % 100 == 0:
            with open(fname, 'wb') as f:
                pk.dump([IR_Data, IR_Data2], f);
        count += 1
    except ValueError:
        print("Bad arduino value.")
