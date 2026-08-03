import os

# ==================================================
# Communication Mode
# ==================================================

# MODE = "SERIAL"
MODE = "WIFI"

# ==================================================
# Serial Settings
# ==================================================

COM_PORT = None          # Auto-detect if None
BAUDRATE = 115200
TIMEOUT = 1

# ==================================================
# Wi-Fi Settings
# ==================================================

HOST = "0.0.0.0"         # Listen on all interfaces
PORT = 5000
BUFFER_SIZE = 1024

# ==================================================
# Base Directory
# ==================================================

BASE_DIR = os.path.dirname(os.path.abspath(__file__))

# ==================================================
# Dataset Folder
# ==================================================

DATASET_FOLDER = os.path.join(
    BASE_DIR,
    "..",
    "..",
    "Dataset",
    "Raw",
    "Test"
)

DATASET_FOLDER = os.path.abspath(DATASET_FOLDER)

# ==================================================
# File Settings
# ==================================================

FILE_PREFIX = "wearable"
FILE_EXTENSION = ".csv"

# ==================================================
# Logger Settings
# ==================================================

STATUS_REFRESH_RATE = 1.0     # seconds
SHOW_LIVE_STATUS = True

# ==================================================
# Future AI Dataset Settings
# ==================================================

ENABLE_ACTIVITY_LABEL = False
DEFAULT_ACTIVITY = "UNKNOWN"

ENABLE_TIMESTAMP = True
ENABLE_DEBUG = False