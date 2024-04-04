#!/bin/zsh

# https://stackoverflow.com/questions/43158140/way-to-create-multiline-comments-in-bash
TIMEFMT=$'real\t%*E\nuser\t%*U\nsys\t%*S\ncpu\t%P\nmemory\t%M KB\n'

for i in {0..10}; do
echo $i
  echo Started at $(date +'%r')
  { time ./cmake-build-"$1"/algorithms "$2" "$3" $i; }
done
