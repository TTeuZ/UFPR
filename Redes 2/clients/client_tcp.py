import sys, os; sys.path.append(os.path.join(os.path.dirname(__file__), '..'))

from utils.constants import MAX_PACK_SIZE, NUM_PACKAGES
from utils.logger import logger
import argparse
import socket
import struct
import time

def main(args):
    client_logger = logger("tcp_client")

    # Starting socket and connecting to the server
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((args.host, int(args.port)))
    client_logger.write(f"Connected to server at {args.host}:{args.port}")

    total_time, package_count, bytes_received = 0, 0, 0
    time_per_packages = []

    # Receiving packages and collecting metrics
    start_time = time.time()
    while True:
        package_start_time = time.time()

        # Getting package size
        header = client_socket.recv(4)
        if not header:
            break
        message_length = struct.unpack('!I', header)[0]

        # Guarantee that the correct size is read before conting one package
        data = b""
        while len(data) < message_length:
            package = client_socket.recv(message_length - len(data))
            if not package:
                break
            data += package

        package_end_time = time.time()

        bytes_received = bytes_received + len(data)
        elapsed_time = package_end_time - package_start_time
        time_per_packages.append(elapsed_time)
        package_count += 1

        client_logger.write(f"Package {package_count} received from {args.host}:{args.port}")

    total_time = time.time() - start_time

    # Logging results
    client_logger.write(F"Bytes received: {bytes_received} - actual sent: {NUM_PACKAGES * MAX_PACK_SIZE}")
    client_logger.write(f"Received {package_count} packages")
    client_logger.write(f"Total time: {total_time:.4f} seconds")
    client_logger.write(f"Average time per package: {sum(time_per_packages) / package_count:.6f} seconds")

    client_logger.write(f"Closing connection - HOST: {args.host} - PORT: {args.port}")
    client_logger.close()
    client_socket.close()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="TCP Client Test1", formatter_class=argparse.ArgumentDefaultsHelpFormatter)
    parser.add_argument("--host", "-ho", type=str, required=True)
    parser.add_argument("--port", "-p", type=str, required=True)

    main(parser.parse_args())