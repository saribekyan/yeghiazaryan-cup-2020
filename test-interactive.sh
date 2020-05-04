#!/bin/bash

problem=$1 # the name of the problem
sol=$2     # path to the solution
onlytest=$3
# we assume the interactor is interactor.cpp

interactor="./$problem-interactor.out"
g++ problems/$problem/interactor.cpp -o $interactor
if [ $? -eq 0 ]; then
    echo "Successfully compiled interactor"
else
    exit 1;
fi

ext=${sol##*.}
if [ $ext = "out" ]; then
    solution=$sol
elif [ $ext = "cpp" ]; then
    echo "Compiling $sol"
    solution="./$problem-sol.out"
    g++ $sol -o $solution
elif [ $ext = "py" ]; then
    solution="python $sol"
fi

if [ -z $onlytest ]; then # do all tests
    TESTS=problems/$problem/tests/[0-9][0-9][0-9]
else
    TESTS=problems/$problem/tests/$onlytest
fi
echo "Starting testing $sol"

pp="/tmp/interactiveProblemPipe"
rm "$pp" 2> /dev/null

for f in $TESTS
do
    echo "Testing $f"
    mkfifo $pp
    # echo "cat $pp | $interactor $f interactor-out.txt $f.a | $solution > $pp"
    # exit 0
    cat $pp | $interactor $f interactor-out.txt $f.a | $solution > $pp
    status="${PIPESTATUS[1]} ${PIPESTATUS[2]}"
    if [ "$status" != "0 0" ]; then
        echo "There was some problem: $status"
        cat interactor-out.txt

        rm $pp 2> /dev/null
        exit 1
    fi
    rm $pp 2> /dev/null
done

echo "Done; all good"

rm interactor-out.txt 2> /dev/null
rm $interactor 2> /dev/null

