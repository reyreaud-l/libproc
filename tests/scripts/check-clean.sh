#!/bin/sh

for file in $(ls *-test); do
  pkill "$file" 
  if [ "$?" -eq 0 ]; then
    echo "Found some process while cleaning up $file"
    exit 1
  fi
done
exit 0
