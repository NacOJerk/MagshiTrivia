import json
import socket
import math

LOGIN_REQUEST_ID = (1).to_bytes(1, byteorder='big')
SIGNUP_REQUEST_ID = (2).to_bytes(1, byteorder='big')
GET_PLAYERS_REQUEST = (3).to_bytes(1, byteorder='big')
JOIN_ROOM_REQUEST = (4).to_bytes(1, byteorder='big')
CREATE_ROOM_REQUEST = (5).to_bytes(1, byteorder='big')
SIGNOUT_REQUEST = (6).to_bytes(1, byteorder='big')
GET_ROOMS_REQUEST = (7).to_bytes(1, byteorder='big')
GET_HISCORES_REQUEST = (8).to_bytes(1, byteorder='big')
ERROR_RESPONSE_ID = (9).to_bytes(1, byteorder='big')

def send(sock, id, dict = {}):
	send_from = 0
	string_dic = ""
	if dict is not {}:
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
	
def signup(sock):
	username = input("Enter username: ")
	password = input("Enter password: ")
	email = input("Enter email: ")
	birth = input("Enter birthdate (dd/MM/yyyy): ")
	phone = input("Enter phone number: ")
	address = input("Enter address: ")
	
	dic = {"username": username, 
		   "password": password, 
		   "email": email, 
		   "birthdate": birth, 
		   "phone": phone, 
		   "address": address}
	send(sock, SIGNUP_REQUEST_ID, dic)
	return json.loads(recv(sock))

def login(sock):
	username = input("Enter username: ")
	password = input("Enter password: ")
	dic = {"username": username, 
		   "password": password}
	send(sock, LOGIN_REQUEST_ID, dic)
	return json.loads(recv(sock))
	
def get_rooms(sock)
	send(sock, GET_ROOMS_REQUEST)
	return json.loads(recv(sock))

def print_rooms(sock):
	rooms = get_rooms(sock)
	i = 1
	for dic in rooms:
		print(str(i) + " " + dic["admin"] + "'s room")
		i += 1
	room = int(input("Enter room id: "))
	return rooms[room-1]
	
def join_room(sock):
	room = print_rooms(sock)
	dict = {"id": room["id"]}
	send(sock, JOIN_ROOM_REQUEST, dict)
	return json.loads(recv(sock))

def get_players_in_room(sock):
	room = print_rooms(sock)
	dict = {"id": room["id"]}
	send(sock, GET_PLAYERS_REQUEST, dict)
	return json.loads(recv(sock))
	
def create_room(sock):
	username = input("What's your username? ")
	maxUsers = int(input("How many max users? "))
	questionCount = int(input("How many questions? "))
	answerTimeout = int(input("How many seconds per question?" ))
	dic = {"username": username, "maxUsers": maxUsers, "questionCount": questionCount, "answerTimeout":answerTimeout}
	send(sock, CREATE_ROOM_REQUEST, dic)
	return json.loads(recv(sock))
	
def get_highscores(sock):
	send(sock, GET_HISCORES_REQUEST)
	return json.loads(recv(sock))

def signout(sock):
	send(sock, SIGNOUT_REQUEST_REQUEST)
	return json.loads(recv(sock))