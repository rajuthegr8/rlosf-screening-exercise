#!/bin/bash
g++ part1.cpp -o evaluate

filename='input.txt'
rm output.txt
touch output.txt

while read line; do
./evaluate $line >> output.txt 
echo "" >> output.txt
done < $filename