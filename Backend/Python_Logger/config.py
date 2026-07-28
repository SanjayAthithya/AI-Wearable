import os

# ------------------------------------
# Serial Settings
# ------------------------------------

BAUDRATE = 115200

COM_PORT = None

# ------------------------------------
# Base Directory
# ------------------------------------

BASE_DIR = os.path.dirname(os.path.abspath(__file__))

# ------------------------------------
# Dataset Folder
# ------------------------------------

DATASET_FOLDER = os.path.join(
    BASE_DIR,
    "..",
    "..",
    "Dataset",
    "Raw",
    "Test"
)

DATASET_FOLDER = os.path.abspath(DATASET_FOLDER)