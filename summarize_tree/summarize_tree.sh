#!/bin/bash

echo "There were $(find "$1" -type d -print| wc -l) directories."
echo "There were $(find "$1" -type f  -print| wc -l) regular files."

