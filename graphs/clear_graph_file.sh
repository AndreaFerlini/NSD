#!/bin/bash

FILENAME=$1

sed '/%/d' $FILENAME > "temp.clear";
sed '/^$/d' "temp.clear" > $FILENAME;

length=$(wc -c <$FILENAME)
if [ "$length" -ne 0 ] && [ -z "$(tail -c -1 <$FILENAME)" ]; then
  # The file ends with a newline or null
  dd if=/dev/null of=$FILENAME obs="$((length-1))" seek=1
fi

rm "temp.clear"

