import json
import socket
import math

LOGIN_REQUEST_ID = (1).to_bytes(1, byteorder='big')
SIGNUP_REQUEST_ID = (2).to_bytes(1, byteorder='big')
ERROR_RESPONSE_ID = (3).to_bytes(1, byteorder='big')
SIGNUP_RESPONSE_ID = (4).to_bytes(1, byteorder='big')
LOGIN_RESPONSE_ID = (5).to_bytes(1, byteorder='big')

def send(sock, id, dict):
	send_from = 0
	string_dic = json.dumps(dict)
	message = id + len(string_dic).to_bytes(4, byteorder='big') + string_dic.encode("ASCII");
	while send_from < len(message):
		send_from += sock.send(message[send_from:])
		
def recv(sock):
	id = sock.recv(1)
	if id is ERROR_RESPONSE_ID:
		print("error returned")
	length = int.from_bytes(sock.recv(4), byteorder='big')
	message = ""
	while len(message) < length:
		message += (sock.recv(length)).decode("ASCII")
	return message
	
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("172.29.109.130", 12345))

dic = {"username": "shahar", "password": "123456"}
send(s, LOGIN_REQUEST_ID, dic)
print(recv(s))

dic = {"email": "shahar3333@gmail.com", "password": "123456", "username": "shahar"}
send(s, SIGNUP_REQUEST_ID, dic)
print(recv(s))

dic = {"username": "shahar", "password": "123456"}
send(s, LOGIN_REQUEST_ID, dic)
print(recv(s))
s.close()
	
