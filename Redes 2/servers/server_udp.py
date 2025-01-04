import sys, os; sys.path.append(os.path.join(os.path.dirname(__file__), '..'))

from utils.constants import MAX_PACK_SIZE, NUM_PACKAGES
from utils.logger import logger
import argparse
import socket

DUMMY_DATA = "A" * MAX_PACK_SIZE

def main(args):
    server_logger = logger("udp_server")

    # Bindig the UDP socket
    server_ip = socket.gethostbyname(socket.gethostname())
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_socket.bind((server_ip, int(args.port)))
    server_logger.write(f"Initiating server - IP: {server_ip} - PORT: {args.port}")

    try:
        # Receive one message from the client and start the send loop
        while True:
            client_message, client_address = server_socket.recvfrom(MAX_PACK_SIZE)
            server_logger.write(f"Client spotted - IP: {client_address}")

            for i in range(NUM_PACKAGES):
                server_socket.sendto(DUMMY_DATA.encode('utf-8'), client_address)
                server_logger.write(f"Sending package {i+1} to {client_address[0]}:{client_address[1]}")

            server_logger.write("All test packages sent")

    except KeyboardInterrupt:
        # Shuting down the server =D
        server_logger.write(f"Closing server - IP: {server_ip} - PORT: {args.port}")
        server_socket.close()
        server_logger.close()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="UDP Server Test1", formatter_class=argparse.ArgumentDefaultsHelpFormatter)
    parser.add_argument("--port", "-p", type=str, required=True)

    main(parser.parse_args())