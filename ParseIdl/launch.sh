#! /bin/bash 

DN="temp" 
#Directory Name
TF="test.idl" 
#test File

make
./main $TF
cd "./$DN"
make
