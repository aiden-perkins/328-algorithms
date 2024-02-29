for i in {0..10}; do
  echo $i
  { time ./cmake-build-debug/algorithms "$1" "$2" $i; }
done
