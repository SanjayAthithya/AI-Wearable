import os
import csv
from datetime import datetime

from config import *


class CSVWriter:

    # ==============================================
    # Constructor
    # ==============================================

    def __init__(self):

        os.makedirs(DATASET_FOLDER, exist_ok=True)

        filename = (
            FILE_PREFIX
            + "_"
            + datetime.now().strftime("%Y%m%d_%H%M%S")
            + FILE_EXTENSION
        )

        self.filename = filename

        self.filepath = os.path.join(
            DATASET_FOLDER,
            filename
        )

        self.file = open(
            self.filepath,
            "w",
            newline=""
        )

        self.writer = csv.writer(self.file)

        self.rows = 0

    # ==============================================
    # Write Header
    # ==============================================

    def write_header(self, header):

        self.writer.writerow(header)

    # ==============================================
    # Write One CSV Row
    # ==============================================

    def write_row(self, row):

        self.writer.writerow(row)

        self.rows += 1

    # ==============================================
    # Flush File
    # ==============================================

    def flush(self):

        self.file.flush()

    # ==============================================
    # Close File
    # ==============================================

    def close(self):

        self.file.close()

    # ==============================================
    # Number of Samples
    # ==============================================

    def sample_count(self):

        return self.rows

    # ==============================================
    # Current File
    # ==============================================

    def current_file(self):

        return self.filename

    # ==============================================
    # Current File Path
    # ==============================================

    def current_path(self):

        return self.filepath