#!/bin/bash

if [[ $(ls -p | grep -cv /) -gt 5 ]]; then
	echo "W bieżącym katalogu jest więcej niż 5 plików"
fi