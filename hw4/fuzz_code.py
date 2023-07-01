import socket
server = '51.144.113.30'
port = 13045
print_output = lambda sock: print (sock.recv(1024).decode("utf-8").strip())
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
    connect = sock.connect((server, port))
    print("connected")
    sock.send("AUTH: archer/VGPF24IDKK45SBP3\x00".encode())
    print("sent AUTH")
    print_output(sock)
    print("hello")
    sock.send(str.encode(input()))
    print_output(sock)
    sock.close()