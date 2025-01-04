from utils.constants import LOGS_BASEPATH
from datetime import datetime
import uuid

class logger():
    def __init__(self, base_name):
        self.base_name = base_name

        random_id = str(uuid.uuid4()).replace('-', '')[:5]
        log_file_name = f"{LOGS_BASEPATH}{base_name}_{random_id}.txt"

        # Opening the log file
        self.log_pointer = open(log_file_name, "w")

        self.log_pointer.write("=============================================================================\n")
        self.log_pointer.write(f"Starting program: {self.base_name}".ljust(58) +  f"{self._get_timestamp()}\n")
        self.log_pointer.write("=============================================================================\n\n")


    def _get_timestamp(self):
        timestamp = datetime.now()
        return timestamp.strftime("%d-%m-%Y %H:%M:%S")
    
    
    def write(self, log):
        self.log_pointer.write(f"[{self._get_timestamp()}]: {log}\n")
        print(f"[{self._get_timestamp()}]: {log}")


    # Close the file and print the log footer
    def close(self):
        if self.log_pointer: 
            self.log_pointer.write("\n=============================================================================\n")
            self.log_pointer.write(f"Closing program: {self.base_name}".ljust(58) +  f"{self._get_timestamp()}\n")
            self.log_pointer.write("=============================================================================\n")

            self.log_pointer.close()
