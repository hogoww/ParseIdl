#! /bin/bash 

DN="temp" 
#Directory Name
TF="test.idl" 
#test File

make

if [ "$?" == 0 ]
then
    ./main $TF
    if [ "$?" == 0 ]
    then
	cd "./$DN"
	make
    else
	exit 2
    fi
else
    exit 1
fi

#Add emacs script to indent
