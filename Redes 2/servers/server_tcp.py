import sys, os; sys.path.append(os.path.join(os.path.dirname(__file__), '..'))

from utils.constants import MAX_PACK_SIZE, NUM_PACKAGES
from utils.logger import logger
import argparse
import socket
import struct

DUMMY_DATA = "A" * MAX_PACK_SIZE

def main(args):
    server_logger = logger("tcp_server")

    # Bindig the TPC socket
    server_ip = socket.gethostbyname(socket.gethostname())
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((server_ip, int(args.port)))
    server_logger.write(f"Initiating server - IP: {server_ip} - PORT: {args.port}")
    
    # Starting to listen clients (iterative mode)
    server_socket.listen(1)
    server_logger.write(f"Server is listening on {server_ip}:{args.port}...")

    try:
        while True:
            # Receiving client connection
            conn_socket, client_address = server_socket.accept()
            server_logger.write(f"Connection received from {client_address}")

            # Mouting TCP package
            message = DUMMY_DATA.encode('utf-8')
            message_length = struct.pack('!I', len(message))
            final_message = message_length + message

            # Starting the send loop
            for i in range(NUM_PACKAGES):
                conn_socket.sendall(final_message)
                server_logger.write(f"Sending package {i+1} to {client_address[0]}:{client_address[1]}")

            conn_socket.close()
            server_logger.write(f"Connection with {client_address} closed.")


    except KeyboardInterrupt:
        # Shuting down the server =D
        server_logger.write(f"Closing server - IP: {server_ip} - PORT: {args.port}")
        server_socket.close()
        server_logger.close()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="TCP Server Test1", formatter_class=argparse.ArgumentDefaultsHelpFormatter)
    parser.add_argument("--port", "-p", type=str, required=True)

    main(parser.parse_args())