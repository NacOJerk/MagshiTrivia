import json
import socket
import math

LOGIN_REQUEST_ID = b'00000001'
SIGNUP_REQUEST_ID = b'00000010'
ERROR_RESPONSE_ID = b'00000011'
SIGNUP_RESPONSE_ID = b'00000100'
LOGIN_RESPONSE_ID = b'00000101'


s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("127.0.0.1", 12345))

dic = {"email": "shahar3333@gmail.com", "password": "123456", "username": "shahar"}
send(s, SIGNUP_REQUEST_ID, dic)
print(recv(s))

dic = {"username": "shahar", "password": "123456"}
send(s, LOGIN_REQUEST_ID, dic)
print(recv(s))

def send(sock, id, dict):
	send_from = 0
	string_dic = json.dumps(dict)
	message = id + str(len(string_dic)) + string_dic;
	while send_from < len(message):
		send_from += sock.send(message[send_from:])

def byte_to_int(byte)
	num = 0;
	st = ""
	while len(byte) is not 0:
		st += byte[-1]
		byte[:-1]
	for i in range(len(st)):
		if st[i] is '1':
			num += math.pow(2, i)
	return num
		
def recv(sock):
	id = sock.recv(1)
	if id is ERROR_RESPONSE_ID:
		print("error returned")
	length = sock.recv(4)
	length = byte_to_int(length)
	message = ""
	while len(message) < length:
		message += sock.recv(length)
	return message
	
