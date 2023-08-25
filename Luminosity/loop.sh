

#!/bin/bash
#
# run 3 fills
#    up to Aug 2023
#
# for i in {7920..9075}
# for i in {8273..9075}
# for i in {8178..9075}
# for i in {8894..9075}
for i in {9059..9075}
do
   echo "Fill $i"
   /cvmfs/cms-bril.cern.ch/brilconda3/bin/python3 prepareTree.py $i
   /cvmfs/cms-bril.cern.ch/brilconda3/bin/python3 prepareTreeROOT.py $i  
done