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

test_invalid() {
	print_yellow "$1"
	$1 && echo -e $RED"Expected Error but got success"$RESET || echo -e $OK
}

## Invalid Test Case
### No argument
test_invalid "./miniRT"
### Invalid Filename
test_invalid "./miniRT nosuchfile"
test_invalid "./miniRT nosuchfile.rt"
test_invalid "./miniRT memo"

## Valid Test Case

### 1. Ambient & Camera & Sphere

test_valid() {
	print_yellow "$1"
	$1 && echo -e $OK || echo -e $RED"Expected Success but got Error"$RESET
}

cat <<EOF >.tmp.rt
A 0.2 255,255,255
C  -50.0,0,20 0,0,1 70
sp 0.0,0.0,20.6 12.6 10,0,255
EOF

## Valid
test_valid "./miniRT .tmp.rt"

rm .tmp.rt
