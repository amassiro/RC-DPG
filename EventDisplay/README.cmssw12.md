Where:

    /afs/cern.ch/user/a/amassiro/work/RC/CMSSW_12_1_0_pre3/src/ISpy/Analyzers
    
Compiled and working here.

Need first to reco the RAW events:

     cmsRun step2_RAW2DIGI_L1Reco_RECO.py
     
Then prepare the ispy file:

    cmsRun python/ispy_Splashes_2021.py
    
    