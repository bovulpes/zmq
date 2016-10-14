#!/bin/bash

W1=1
W2=16

#for W1 in 11
while (($W2-$W1+1))
do

  iw=$W1

  #kill %${iw}; echo "Kill worker " ${iw} 
  #./pc11/taskwork ${iw} & 
  ./srv/taskwork ${iw} &

  W1=$(($W1+1))

done
