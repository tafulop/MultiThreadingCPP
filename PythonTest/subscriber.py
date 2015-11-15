import sys
import zmq
import string
import re

# Socket to talk to server

port = "5556"
context = zmq.Context()
m1 = context.socket(zmq.SUB)
m2 = context.socket(zmq.SUB)
m3 = context.socket(zmq.SUB)
m4 = context.socket(zmq.SUB)
m5 = context.socket(zmq.SUB)

print("Connecting...")
m1.connect ("tcp://localhost:%s" % port)
m2.connect ("tcp://localhost:%s" % port)
m3.connect ("tcp://localhost:%s" % port)
m4.connect ("tcp://localhost:%s" % port)
m5.connect ("tcp://localhost:%s" % port)

m1.setsockopt_string(zmq.SUBSCRIBE, "M1")
m2.setsockopt_string(zmq.SUBSCRIBE, "M2")
m3.setsockopt_string(zmq.SUBSCRIBE, "M3")
m4.setsockopt_string(zmq.SUBSCRIBE, "M4")
m5.setsockopt_string(zmq.SUBSCRIBE, "M5")

print("Connected.")
# Process 5 updates
while(1):
    string = m1.recv()
    topic, messagedata = string.split()
    msgdata = str(messagedata)
    match = re.match(b'(-?\d+.?\d*)', messagedata)
    print ("M1: ",float(match.group(1)))

    string = m2.recv()
    topic, messagedata = string.split()
    msgdata = str(messagedata)
    match = re.match(b'(-?\d+.?\d*)', messagedata)
    print ("M2: ", float(match.group(1)))


    string = m3.recv()
    topic, messagedata = string.split()
    msgdata = str(messagedata)
    match = re.match(b'(-?\d+.?\d*)', messagedata)
    print ("M3: ", float(match.group(1)))


    string = m4.recv()
    topic, messagedata = string.split()
    msgdata = str(messagedata)
    match = re.match(b'(-?\d+.?\d*)', messagedata)
    print ("M4: ",float(match.group(1)))


    string = m5.recv()
    topic, messagedata = string.split()
    msgdata = str(messagedata)
    match = re.match(b'(-?\d+.?\d*)', messagedata)
    print ("M5: ",float(match.group(1)))


    print ("-----------------------------")