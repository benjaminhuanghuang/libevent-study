import socket

HOST = '127.0.0.1' #'10.10.15.194'   
PORT = 9995           
sdata = ['hello world','you are','baby','do....just..all']
rdata = ''

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print('connect to server..')

s.connect((HOST, PORT))
for data in sdata:
    print('send data '),data
    s.sendall(data)
    print('recv..')
    rdata = s.recv(len(data))
    print('Received', repr(rdata),'\n')

s.close()