# -*- coding:utf-8 -*-

import socket
print "create socket .."
s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

print "done"
print "connect to 192.168.87.129"
s.connect(("192.168.87.129",7707))
while True:
	print "ye ,,"
	sr = raw_input("send msg for 'q' is quit:")
	if sr=='q':
		break
	else:
		# sr = sr.decode("utf-8")
		s.send(sr)
	reply = s.recv(4096)
	print reply

	# sSend = raw_input()
s.close()
print "done"
