#!/bin/bash
base1="root-processes-"
user1="root     "
count1="$((`ls -1 | grep $base1 | wc -l` + 1))"
ps -aux | more | grep $user1 > $base1$count1

base2="my-processes-"
user2=whoami
count2="$((`ls -1 | grep $base2 | wc -l` + 1))"
ps -aux | more | grep $user2 > $base2$count2
