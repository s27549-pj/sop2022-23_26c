#!/bin/bash
files=("$@")

for file in ${#files[@]}; do

	cat "${files[i]}"
	echo

	tac "${files[i]}"
	echo

done