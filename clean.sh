#!/bin/bash

find . -type f \( -name "*.lst" -o -name "*.v20raw" \) -exec rm -f {} \;
rm -f macrotests/testcasegen/multest.inc
rm -f macrotests/testcasegen/divtest.inc
