# Compile options

VERBOSE=n
OPT=g
USE_NANO=y
SEMIHOST=n
USE_FPU=y

# Libraries

USE_LPCOPEN=y
USE_SAPI=y

USE_FATFS=y

USE_FREERTOS=n
FREERTOS_HEAP_TYPE=1

# Let FSSDC/FSUSB print their own status messages by DEBUGSTR()
DEFINES+=DEBUG_ENABLE

LOAD_INRAM=n