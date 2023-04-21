#!/bin/bash

for i in *.c; do
	cc "$i" -o "${i%.*}";
done