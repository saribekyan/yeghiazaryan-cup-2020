#!/bin/bash

problemId=$1
executable=`ls problems/$problemId/a.out 2> /dev/null`
if [ -z $executable ]; then # file does not exist
    pysol=`ls problems/$problemId/sol.py 2> /dev/null`
    if [ -z $pysol ]; then # python file also does not exist
        echo "No solution found for problem $problem"
        exit 1
    fi
    executable="python $pysol"
fi
echo $executable

FILES=problems/$problemId/tests/[0-9][0-9][0-9]
for f in $FILES
do
    echo "Running $f"
    $executable < $f > $f.a
done
