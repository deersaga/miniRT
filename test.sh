#!/bin/bash

test_invalid() {
	echo "$1"
	$1 && echo "Expected Error but got success" || echo "OK"
}

## Invalid Test Case
### No argument
test_invalid "./miniRT"
### Invalid Filename
test_invalid "./miniRT nosuchfile"

## Valid Test Case

### 1. Ambient & Camera & Sphere

test_valid() {
	echo "$1"
	$1 && echo "OK" || echo "Expected Success but got Error"
}

cat <<EOF >.tmp.rt
sp 0.0,0.0,20.6 12.6 10,0,255
C  -50.0,0,20 0,0,1 70
sp 0.0,0.0,20.6 12.6 10,0,255
EOF

## Valid
test_valid "./miniRT .tmp.rt"

rm .tmp.rt
