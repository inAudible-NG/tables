#!/bin/bash

# ./demo.sh <sha1 checksum>
# 00112233

pattern='hex:'

cd `dirname $0`

./rcrack . -h $1 | grep $pattern | awk -F $pattern '{print $2}'
