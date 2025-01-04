import sys, os; sys.path.append(os.path.join(os.path.dirname(__file__), '..'))

from utils.constants import MAX_PACK_SIZE, NUM_PACKAGES
from utils.logger import logger
import argparse
import socket
import time

def main(args):
    client_logger = logger("udp_client")

    # Starting the socket and timeout, in case of lost packages
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    client_socket.settimeout(5)
    server = (args.host, int(args.port))

    # Ask for the packages from the server
    client_logger.write(f"Starting test with {args.host}:{args.port}")
    client_socket.sendto(b"START", server)

    total_time, package_count, bytes_received = 0, 0, 0
    time_per_packages = []
    timeoutHappend = False

    try:
        # Receiving packages and collecting metrics
        start_time = time.time()
        while True:
            package_start_time = time.time()

            data, server_address = client_socket.recvfrom(MAX_PACK_SIZE)

            package_end_time = time.time()

            bytes_received = bytes_received + len(data)
            elapsed_time = package_end_time - package_start_time
            time_per_packages.append(elapsed_time)
            package_count += 1

            client_logger.write(f"Package {package_count} received from {server_address[0]}:{server_address[1]}")

            if package_count >= NUM_PACKAGES:
                break

    except OSError:
        client_logger.write(f"Timeout - {NUM_PACKAGES - package_count} packages lost")
        timeoutHappend = True

    # Timeout is 5 seconds, so, if one happend, it's necessary to remove 5 seconds from the total time
    total_time = time.time() - start_time
    if timeoutHappend:
        total_time = total_time - 5

    # Logging results
    client_logger.write(F"Bytes received: {bytes_received} - actual sent: {NUM_PACKAGES * MAX_PACK_SIZE}")
    client_logger.write(f"Received {package_count} packages")
    client_logger.write(f"Total time: {total_time:.4f} seconds")
    client_logger.write(f"Average time per package: {sum(time_per_packages) / package_count:.6f} seconds")

    client_logger.write(f"Closing test - HOST: {args.host} - PORT: {args.port}")
    client_logger.close()
    client_socket.close()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="TCP Client Test1", formatter_class=argparse.ArgumentDefaultsHelpFormatter)
    parser.add_argument("--host", "-ho", type=str, required=True)
    parser.add_argument("--port", "-p", type=str, required=True)

    main(parser.parse_args())