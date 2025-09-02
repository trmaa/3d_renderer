#!/bin/bash

screenshots=$(find ./bin/screenshots/ -name "*.png")

for screenshot in $screenshots; do
	firefox $screenshot
done
