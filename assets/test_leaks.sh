#!/bin/bash
# =========================================================================== #
# cub3D: script to check for memory leaks                                     #
# Created on: 2025-07-31                                                      #
# =========================================================================== #

PROGRAM=./cub3D
MAP_DIRS=("assets/maps/invalid/color" "assets/maps/invalid/content"
    "assets/maps/invalid/tex")

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
        printf "%s ${CYA_B}%s${NC} " "$PROGRAM" "$MAP"
        VALGRIND_LOG=$(mktemp)
        ERR_MSG=$(valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=3 \
            "$PROGRAM" "$MAP" 2> "$VALGRIND_LOG" >/dev/null)
        STATUS=$?

        if [ $STATUS -eq 0 ]; then
            printf "${GRN_B}NO LEAKS${NC}\n"
        elif [ $STATUS -eq 3 ]; then
            printf "${RED_B}CRAPPY CODE - BOO!${NC} 💔\n"
            sed 's/^/    /' "$VALGRIND_LOG"
            rm "$VALGRIND_LOG"
            exit 1
        fi
        rm -f "$VALGRIND_LOG"
    done
    echo
done

printf "🥳 ${GRN_B}All maps checked: no leaks!${NC} 🥳\n"
