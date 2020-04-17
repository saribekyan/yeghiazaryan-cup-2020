#!/bin/bash

problemId=$1
file=$2
ext=${file##*.}
if [ $ext = "cpp" ]; then
    g++ file -o "./test-prog.out"
    executable="./test-prog.out"
elif [ $ext = "py" ]; then
    executable="python $file"
elif [ $ext = "out" ]; then
    executable=$file
fi

TESTS=problems/$problemId/tests/[0-9][0-9][0-9]
echo "Checking: $executable"
for f in $TESTS
do
    echo "Testing $f"
    $executable < $f > curr.a
    if cmp -s curr.a "$f"; then
        echo "Test $f failed, see curr.a for output."
        exit 1
    fi
done

rm ./curr.a
rm ./test-prog.out
