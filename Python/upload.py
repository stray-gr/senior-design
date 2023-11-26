"""
NOTES: 
- Before running this script, first type ctrl+E in Wokwi's REPL. 
  This will have the REPL enter paste mode, which makes it easier 
  to send lots of text. 
- After runnig the script, type ctrl+D in Wokwi's REPL. This will 
  let the python expressions be evaluated
"""

import glob
import serial
import os

# Global Consts
TELNET_URL = 'rfc2217://localhost:4000'
BAUD_RATE  = 115200
MODULES    = ['import machine']
EXCLUDED_FILES = {'example_hidden.py'}
BOARD_DIR  = 'board/'

# Find file paths
os.chdir(BOARD_DIR)
file_paths = []
for item in glob.glob('./**', recursive=True):
    if os.path.isfile(item) and os.path.basename(item) not in EXCLUDED_FILES:
        print(f'Found {item}')
        file_paths.append(item)

# Create serial connection
ser = serial.serial_for_url(TELNET_URL, baudrate=BAUD_RATE)

# Iterate over modules that need to be imported
for m in MODULES:
    ser.write(f'{m}\n'.encode())

# Iterate over source code files that need to be uploaded
# NOTE that file contents are sent as raw, multi-line byte strings
for fpath in file_paths:
    ser.write(b'x = r\"""') 
    with open(fpath, 'r') as f:
        ser.write(f.read().encode())
    ser.write(b'\"""\n')
    ser.write(f'f = open("{os.path.basename(fpath)}", "w")\n'.encode())
    ser.write(b'f.write(x)\n')
    ser.write(b'f.close()\n')

# Terminate the sent expressions with a machine reset
ser.write(b'machine.reset()')
