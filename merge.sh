#!/bin/bash

find /eos/user/k/kuzmenko/msc-230/ -name "*.root" | sort -r | head -n 1 | sed -e "s/[^0-9]//g" | read data; data=$((data + 1))
echo $data
hadd "%05d.root" "$data" $(find $OUTPUT_DIR -name "*.root")

rm -r $OUTPUT_DIR/tmp/