#!/bin/bash
# =========================================================================== #
# cub3D map testing script                                                    #
# Created on: 2025-07-29                                                      #
# =========================================================================== #

PROGRAM=./cub3D
MAP_DIRS=("assets/maps/invalid/color" "assets/maps/invalid/content"
    "assets/maps/invalid/tex" "assets/maps/valid/color"
    "assets/maps/valid/content" "assets/maps/valid/tex")

# -----------------------------------------------------------------------------
# UTILS: ANSI COLOR SEQUENCES

# Reset to default
NC='\033[0m'

# Regular text colors
RED="\033[0;31m"

# Bold text colors
RED_B="\033[1;31m"
GRN_B="\033[1;32m"
YEL_B="\033[1;33m"
CYA_B="\033[1;36m"

# -----------------------------------------------------------------------------

for DIR in "${MAP_DIRS[@]}"; do
    printf "${CYA_B}TESTING MAPS IN ${YEL_B}%s${NC}\n" "$DIR"

    for MAP in "$DIR"/*; do
        [ -f "$MAP" ] || continue
        printf "%s ${CYA_B}%s${NC} " "$PROGRAM"  "$MAP"
        ERR_MSG=$($PROGRAM "$MAP" 2>&1 >/dev/null)
        STATUS=$?
        if [ $STATUS -eq 0 ]; then
            printf "${GRN_B}VALIDATED${NC}\n"
        else
            printf "${RED_B}MARKED AS INVALID${NC}\n"
            [ -n "$ERR_MSG" ] && printf "${RED}%s${NC}\n" "$ERR_MSG" | sed 's/^/    /'
        fi
    done
    echo
done
