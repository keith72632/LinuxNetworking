import socket
from time import sleep
from datetime import datetime
import sys

HOST = '192.168.0.183'
PORT = 9090

while True:
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0) as s:
        try:
            s.connect((HOST, PORT))
            print(f'Connect to {HOST} on port {PORT}')

            msg = 'client'
            s.send(msg.encode())

            data = s.recv(1024)
            data = data.decode()

            print(f'Data: {data} received')
            sleep(1)

        except KeyboardInterrupt:
            print('keyboard interrupt')
            s.close()
            sys.exit()
