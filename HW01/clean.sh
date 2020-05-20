#!/bin/bash

#this script removes .txt files if it finds them
file=(`find ./ -maxdepth 1 -name "*.txt"`)
if [ ${#file[@]} -gt 0 ]
then
    rm *.txt
fi

#this script removes root-process files if it finds them
file=(`find ./ -maxdepth 1 -name "root-processes*"`)
if [ ${#file[@]} -gt 0 ]
then
    rm root-processes*
fi

#this script removes my-process files if it finds them
file=(`find ./ -maxdepth 1 -name "my-processes*"`)
if [ ${#file[@]} -gt 0 ]
then
    rm my-processes*
fi
