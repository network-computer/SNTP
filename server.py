import socket
import logging

def udp_server(host, port):
    skt = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    skt.bind((host, port))
    while True:
        data = skt.recv(1024 * 4)
        print(data)

print('Starting server...')
udp_server('127.0.0.1', 123)
