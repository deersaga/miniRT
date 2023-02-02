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

## Valid
test_valid "./miniRT rt_files/ok_1.rt"

rm .tmp.rt
