#!/bin/bash

# Compares the output of the test program to the test answer bitewise

# This is for quick local testing, it will not ignore whitespace characters etc.

problem=$1      # e.g. sum
file=$2         # solution file (can be cpp, py or out)
onlytest=$3     # run only this test     (e.g. problems/sum/tests/001)

ext=${file##*.}
if [ $ext = "cpp" ]; then
    solution="./$problem-sol.out"
    g++ $file -o "$solution"

    if [ $? -eq 0 ]; then
        echo "Successfully compiled the solution"
    else
        echo "Could not compile the solution $file"
        exit 1;
    fi
elif [ $ext = "py" ]; then
    solution="python $file"
elif [ $ext = "out" ]; then
    solution=$file
elif [ $ext = $sol ]; then # maybe there is no extension on the solution file
    solution=$sol
else
    echo "Can't figure out extension of $sol"
    exit 1
fi

TESTS=problems/$problem/tests/[0-9][0-9][0-9]
if [ -z $onlytest ]; then # do all tests
    TESTS=problems/$problem/tests/[0-9][0-9][0-9]
else
    TESTS=problems/$problem/tests/$onlytest
fi

echo "Starting testing $sol"
echo "Executable: $solution"
echo ""

for f in $TESTS
do
    echo "Testing $f"
    $solution < $f > curr.a
    cmp -s curr.a "$f.a"
    if [ $? -eq 0 ]; then
        echo "ok"
    else
        echo "Test $f failed, see curr.a for output."
        exit 1
    fi
done

rm ./curr.a 2> /dev/null
rm "./$problem-sol.out" 2> /dev/null
