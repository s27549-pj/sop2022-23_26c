#!/bin/bash

if [ -a "./config.cfg" ]; then
	bash config.cfg
elif [ "$1" ] ; then
	bash "$1"
else
	echo "BŁĄD"
fi
