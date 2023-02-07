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

### Invalid Parameter
test_invalid "./miniRT rt_files/invalid_01_outrange_color.rt"
test_invalid "./miniRT rt_files/invalid_02_outrange_A_ratio.rt"
test_invalid "./miniRT rt_files/invalid_03_outrange_L_ratio.rt"
test_invalid "./miniRT rt_files/invalid_04_cylinder.rt"
test_invalid "./miniRT rt_files/invalid_05_outrange_fov.rt"
test_invalid "./miniRT rt_files/invalid_06_multiple_A.rt"
test_invalid "./miniRT rt_files/invalid_07_multiple_C.rt"
test_invalid "./miniRT rt_files/invalid_08_multiple_L.rt"
test_invalid "./miniRT rt_files/invalid_09_negative_sp_diameter.rt"
test_invalid "./miniRT rt_files/invalid_10_negative_cy_diameter.rt"
test_invalid "./miniRT rt_files/invalid_11_negative_cy_height.rt"
test_invalid "./miniRT rt_files/invalid_12_unknown_identifier.rt"
test_invalid "./miniRT rt_files/invalid_13_whitespace_in_vec.rt"
test_invalid "./miniRT rt_files/invalid_14_invalid_properies_order.rt"

## Valid Test Case

### 1. Ambient & Camera & Sphere

test_valid() {
	print_yellow "$1"
	$1 && echo -e $OK || echo -e $RED"Expected Success but got Error"$RESET
}

## Valid
test_valid "./miniRT rt_files/ok_01_simple.rt"
test_valid "./miniRT rt_files/ok_02_two_sphere.rt"
test_valid "./miniRT rt_files/ok_03_plane.rt"
test_valid "./miniRT rt_files/ok_04_cylinder.rt"
test_valid "./miniRT rt_files/ok_05_multi_kind_objs.rt"
test_valid "./miniRT rt_files/ok_06_multiple_newline.rt"
test_valid "./miniRT rt_files/ok_07_multiple_spaces.rt"
test_valid "./miniRT rt_files/ok_08_simple_different_order.rt"
test_valid "./miniRT rt_files/ok_09_tdu1.rt"
test_valid "./miniRT rt_files/ok_10_tdu2.rt"
test_valid "./miniRT rt_files/ok_11_tdu3.rt"
