import socket

HOST = "192.168.137.1"
PORT = 5000

print("=" * 50)
print("      AI Wearable TCP Server")
print("=" * 50)

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server.bind((HOST, PORT))

server.listen(1)

print(f"Listening on Port {PORT}...")
print()

client, address = server.accept()

print("===================================")
print("ESP32 Connected")
print("IP :", address[0])
print("===================================")

while True:

    data = client.recv(1024)

    if not data:
        break

    print(data.decode().strip())