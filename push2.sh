#!/bin/sh

if [ $1 && $1 = -p ]; then
    git pull
fi
    git status;
    echo "Choose a file to add (* for all)";
    read var1;
    git add "$var1";
    git status;
    echo "Reason to push";
    read var2;
    git commit -m "$var2";
    if git push; then
	echo "Nicely done; successful push";
    fi


