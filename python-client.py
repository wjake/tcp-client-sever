import socket

def tcp_client():
    host = '127.0.0.1'  # Server address
    port = 65432  # Server port

    # Create TCP socket
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((host, port)) # Connect to the server
        
        # Send data
        message = 'Message' # Message to send
        s.sendall(message.encode())
        
        # Receive confirmation response from the server
        data = s.recv(1024)
        print('Received from server:', data.decode())
