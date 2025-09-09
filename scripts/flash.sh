# Flash
# 9/5/25

#!/bin/bash

RED="\e[31m"
GREEN="\e[32m"
ENDCOLOR="\e[0m"

echo -e "${GREEN}*** Flash${ENDCOLOR}"
idf.py flash

