#!/bin/bash

echo "This is an apparmor example."

touch sample.txt
echo "File created"

sleep 1

rm sample.txt
echo "File deleted"

