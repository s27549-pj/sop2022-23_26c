#!/bin/bash

if   [[ "$1" =~ ^[A-ZŁŻŚ]{1}[a-ząćęłóńś]+$ ]]; then
    echo imie
elif [[ "$1" =~ ^[0-9]{2}-[0-9]{3}$ ]]; then
    echo "kod pocztowy"
elif [[ "$1" =~ ^[A-Za-z0-9!#$%\&\'*+\-/=?^_\`{|}~]{0,64}@[A-Za-z0-9.-]{0,255}$ ]]; then
    echo email
else
	echo nic
fi