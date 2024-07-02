#!/bin/bash

find . -type f \( -name "*.lst" -o -name "*.v20raw" \) -exec rm -f {} \;
rm macrotests/testcasegen/multest.inc
rm macrotests/testcasegen/divtest.inc
