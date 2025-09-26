#Build
# 8/27/25

#!/bin/bash

# Get The Path Where This Shell Script Is
SCRIPT_DIR="$(dirname "$(readlink -f "$0")")"

# Source Color Definitions
source ./colors.sh

printf "${GREEN}*** Build ***${ENDCOLOR}\n"
idf.py build