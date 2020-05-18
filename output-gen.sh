#!/bin/bash

# Generates output given the solution

problem=$1  # the name of the problem (e.g. sum)
sol=$2      # path to the solution    (e.g. problems/sum/sol.py) - can be cpp, out or py;
            # if empty, the script will find some sol.py/sol.cpp and compile it.

if [ -z $sol ]; then # no solution is given, find it
    sol=`ls problems/$problem/sol.py 2> /dev/null`
    if [ -z $sol ]; then # python solution not found
        sol=`ls problems/$problem/sol.cpp 2> /dev/null`
    fi
    if [ -z $sol ]; then # no solution found
        echo "No solution found for problem $problem"
        exit 1
    fi
    echo "Found solution file $sol"
fi

ext=${sol##*.}
if [ $ext = "out" ]; then # the solution is .out file
    solution=$sol
elif [ $ext = "cpp" ]; then # cpp solution, need to compile
    echo "Compiling $sol"
    solution="./$problem-sol.out"
    g++ $sol -o $solution

    if [ $? -eq 0 ]; then
        echo "Successfully compiled the solution"
    else
        echo "Could not compile the solution $sol"
        exit 1;
    fi

elif [ $ext = "py" ]; then # py file
    solution="python $sol"
elif [ $ext = $sol ]; then # maybe there is no extension on the solution file
    solution=$sol
else
    echo "Can't figure out extension of $sol"
    exit 1
fi

TESTS=problems/$problem/tests/[0-9][0-9][0-9]

echo "Starting testing $sol"
echo "Executable: $solution"
echo ""

for f in $TESTS
do
    echo "Running $f"
    $solution < $f > $f.a
done

rm "$problem-sol.out" 2> /dev/null
