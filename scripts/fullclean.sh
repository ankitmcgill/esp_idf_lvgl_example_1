# Clean Build
# 8/27/25

#!/bin/bash

# Get The Path Where This Shell Script Is
SCRIPT_DIR="$(dirname "$(readlink -f "$0")")"

# Source Color Definitions
source $SCRIPT_DIR/colors.sh

printf "${LIGHT_YELLOW}*** Build Full Clean ***${ENDCOLOR}\n"
idf.py fullclean