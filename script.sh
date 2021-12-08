#! /bin/bash

`make clean > /dev/null 2>&1 && make parser > /dev/null 2>&1`

TEST_FOLDER=./examples

total_tests=0
total_correct_tests=0

for entry in "$TEST_FOLDER"/*.tl; do
    printf "%-40s" "$entry"

    err_file=`echo $entry | sed 's/\(.*\)\.tl/\1.err/g'`
    err=`cat $err_file 2>/dev/null`

    `./test < $entry > /dev/null 2>&1`
    return_val=$?

    if [[ -f "$err_file" && $return_val -ne $err ]]; then
        printf "\x1B[31m"
        printf "\u2718"
        printf "   ERROR CODE -->  < %s >  " $return_val
        printf "expected -->  < %s >" $err
        printf "\x1B[0m\n"
    elif [[ $return_val -eq 0 || $return_val -eq $err ]]; then
        printf "\x1B[32m"
        printf "\u2714"
        printf "\x1B[0m\n"
        ((total_correct_tests+=1))
    else
        printf "\x1B[31m"
        printf "File $err_file does not exists"
        printf "\x1B[0m\n"
        ((total_correct_tests+=1))
    fi

    ((total_tests+=1))
done

printf "Number of tests: $total_tests\n"
printf "Number of passed tests: $total_correct_tests\n"
printf ""

`make clean > /dev/null 2>&1`
