Creation of ttree for luminosity studies
====

From BRIL group

    ssh lxplus
    /cvmfs/cms-bril.cern.ch/brilconda3/bin/python3 -m pip install --user --upgrade brilws
    /cvmfs/cms-bril.cern.ch/brilconda3/bin/python3


    /cvmfs/cms-bril.cern.ch/brilconda3/bin/python3 prepareTree.py
    /cvmfs/cms-bril.cern.ch/brilconda3/bin/python3 prepareTreeROOT.py
    

    /cvmfs/cms-bril.cern.ch/brilconda3/bin/python3 prepareTree.py 8817
    /cvmfs/cms-bril.cern.ch/brilconda3/bin/python3 prepareTreeROOT.py 8817
    
    /cvmfs/cms-bril.cern.ch/brilconda3/bin/python3 prepareTree.py 8786
    /cvmfs/cms-bril.cern.ch/brilconda3/bin/python3 prepareTreeROOT.py 8786
    
    /cvmfs/cms-bril.cern.ch/brilconda3/bin/python3 prepareTree.py 8746
    /cvmfs/cms-bril.cern.ch/brilconda3/bin/python3 prepareTreeROOT.py 8746
    
    
    r99t draw.cxx
    

OMS:

    https://cmsoms.cern.ch/cms/fills/bunch_info?cms_fill=8817
    

Draw Changes

    
    sh loop.sh
    
    r99t drawChanges.cxx
    
    ls Luminosity/ | tr "_" " " |  tr "." " " | awk '{print $2","}' | tr "\n" " "
    
    
    