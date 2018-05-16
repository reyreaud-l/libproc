#!/bin/sh


procs=$(ls *-test)
echo "Cleaning the following possible processes" $procs
for file in $procs; do
  pkill "$file" 
  if [ "$?" -eq 0 ]; then
    echo "Found some process while cleaning up $file"
    exit 1
  fi
done
exit 0
