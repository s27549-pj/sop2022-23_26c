#!/bin/bash

if [[ "$0" =~ (.sh)$ ]]; then
	echo "Plik .sh"
else
	rename "s/$0/.sh/" *.![.sh]$
fi
