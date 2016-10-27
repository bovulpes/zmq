#!/bin/bash

W1=1
W2=2

while (($W2-$W1+1))
do

  iw=$W1

  ./taskwork ${iw} &

  W1=$(($W1+1))

done
