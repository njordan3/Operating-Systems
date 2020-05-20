#!/bin/sh
file="systemParams.txt"
if [ -f "$file" ]; then
    rm $file
fi
echo "==========================" >> $file
echo "Date: " >> $file
date >> $file
echo "==========================" >> $file
echo "Host: " >> $file
hostname >> $file
echo "==========================" >> $file
echo "The users are: " >> $file
who >> $file
echo "==========================" >> $file
echo "I am: " >> $file
whoami >> $file
echo "==========================" >> $file
