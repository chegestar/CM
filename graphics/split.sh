#!/bin/bash
for i in `seq 0 $3`; 
do
    gimp -i -b "(split_image \"$1\" \"$2_$i.png\" $i)" -b '(gimp-quit 0)'
done