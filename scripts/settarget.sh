# Set Target
# 10/1/25

#!/bin/bash

# Get The Path Where This Shell Script Is
SCRIPT_DIR="$(dirname "$(readlink -f "$0")")"

# Source Color Definitions
source $SCRIPT_DIR/colors.sh

printf "${LIGHT_YELLOW}*** Set Target esp32s3 ***${ENDCOLOR}\n"
idf.py set-target esp32s3