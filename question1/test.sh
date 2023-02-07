#!/bin/bash

RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
RESET="\033[0m"
OK=$GREEN"OK"$RESET
NG=$RED"NG"$RESET

print_yellow() {
	echo -e $YELLOW"$1"$RESET
}
test_valid() {
	print_yellow "$1"
	$1 && echo -e $OK || echo -e $RED"Expected Success but got Error"$RESET
}

test_valid "./miniRT question1/sp_ok_10^9.rt"
test_valid "./miniRT question1/sp_all_blue_10^10.rt"
test_valid "./miniRT question1/sp_all_blue_10^12.rt"
test_valid "./miniRT question1/sp_strange_pattern_10^13.rt"
test_valid "./miniRT question1/sp_strange_pattern_10^15.rt"
test_valid "./miniRT question1/sp_almost_blue_10^16.rt"
test_valid "./miniRT question1/sp_disappear_10^17.rt"


