#!/bin/bash

echo -e "\033c"

../SLEQASM/sleqasm.js macrotests/$1.sleq 3 && \
../SLEQASM/subleq.js macrotests/$1.v20raw -q  > /tmp/tmp.tmp

# read all lines from /tmp/tmp.tmp
while read line; do
    v1=$(echo $line | awk '{print $1}')
    v2=$(echo $line | awk '{print $3}')
    res=$(echo $line | awk '{print $4}')
    res=$(echo $res | tr -d '\r\n')
    if [ -z "$v1" ] || [ -z "$v2" ]; then continue; fi
#    if [ $v1 -lt 0 ] && [ $v2 -lt 0 ]; then continue; fi
#    if [ $v1 -gt 0 ] && [ $v2 -gt 0 ]; then continue; fi
    
    if [ $v1 -ge $v2 ]; then expected="True"; else expected="False"; fi

    if [ "$res" == "$expected" ]; then
        echo -e "\033[32mComparing $v1 and  $v2 OK\033[0m"
    else
        echo -e "\033[31mComparing $v1 and $v2 Fail\033[0m"
    fi

done < /tmp/tmp.tmp

source ./clean.sh
