#!/bin/bash
function kolorowowy_tekst() {
	echo -e "\033[$2m$1\033[0m"
}