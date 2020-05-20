#!/bin/bash
file=memory.txt
free --mega >> $file	#gets memory info in megabytes and stores it in file
echo " " >> $file	#separates the data with a space
