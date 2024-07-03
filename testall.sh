#!/bin/bash

source ./clean.sh
cd macrotests/testcasegen
source build.sh
cd ../..


if [ $# -eq 1 ]; then
  test_name=$1
else
  test_name=""
fi

echo -e "\033c"

ls macrotests | grep .sleq | sed 's/.sleq//' | while read line; do 
    if [ ! -z "$test_name" ] && [[ "$line" != $test_name* ]]; then
        continue
    fi
    
    echo -n "$line "

    script=$(sed -n '/;# SCRIPT/,/;# END/p' macrotests/$line.sleq | sed 's/^;//')
    expected=$(eval "$script")
    if [ "$expected" = "" ]; then
        echo -e "\033[0;33mNot tested\033[0m"
        continue
    fi

    result=$(  \
        ../SLEQASM/sleqasm.js macrotests/$line.sleq 0 && \
        ../SLEQASM/subleq.js macrotests/$line.v20raw -q | \
        tr -d '\n' | \
        tr -d '\r' \
    )

    if [ "$expected" = "$result" ]; then
        echo -e "\033[0;32mOK\033[0m"
    else
        echo -e "\033[0;31mFAIL\033[0m"
        if [ ! -z "$test_name" ]; then
            echo -e "\tExpected \'$expected\'"
            echo -e "\tBut got  \'$result\'"
        fi

    fi
done

source ./clean.sh
