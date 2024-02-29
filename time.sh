> time.log
for i in {0..10}; do
  { time ./cmake-build-debug/algorithms "$1" "$2" $i; }
done
