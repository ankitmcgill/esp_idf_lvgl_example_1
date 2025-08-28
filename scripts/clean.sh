# Clean Build
# 8/27/25

#!/bin/bash

RED="\e[31m"
GREEN="\e[32m"
ENDCOLOR="\e[0m"

echo -e "${GREEN}*** Build Clean${ENDCOLOR}"
idf.py clean

