LIMIT=100000000
echo off

rm result

for ((a=100000; a <= LIMIT ; a=a+100000))
do
  echo "#define SIZE $a" > arraySize.h
  gcc -std=gnu99 cachedeteckt.c && ./a.out >> result
done

echo; echo
