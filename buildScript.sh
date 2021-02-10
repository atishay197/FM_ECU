#!/bin/bash

if g++ Code/*.cpp -o Build/$outputName 
then
	echo "Problem in compilation" 
else
	echo "Compilation successful. Now running"
	cd Build
	./$outputName
	cd ..
fi
	

