Event display
====

For CRUZET 2021


Pick event
====

    https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookPickEvents

    edmPickEvents.py  "/Cosmics/Commissioning2021-PromptReco-v1/AOD" 319337:60:30203079

The format is run:lumi:event or

    edmPickEvents.py  "/Cosmics/Commissioning2021-PromptReco-v1/AOD" file.txt

with 1 event for each line in the file.txt

Example:

    cd /afs/cern.ch/user/a/amassiro/work/RC/CMSSW_11_3_4/src
    cmsenv
    edmPickEvents.py  "/Cosmics/Commissioning2021-PromptReco-v1/AOD" file.txt
    

Get a whole bunch of events 
====

    https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=file+dataset%3D%2FCosmics%2FCommissioning2021-PromptReco-v1%2FAOD+run%3D344063
    
    voms-proxy-init -voms cms -rfc

    xrdcp root://xrootd.unl.edu///store/data/Commissioning2021/Cosmics/AOD/PromptReco-v1/000/344/063/00000/03ec45f7-d8ff-42ac-a85e-e0e9db92a36f.root  
    
    
    cd /tmp/amassiro/
    xrdcp root://xrootd.unl.edu///store/data/Commissioning2021/Cosmics/AOD/PromptReco-v1/000/344/063/00000/03ec45f7-d8ff-42ac-a85e-e0e9db92a36f.root .
    
    
    
    
    
    
    /Cosmics/Commissioning2021-CosmicTP-PromptReco-v1/RAW-RECO
    https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=file+dataset%3D%2FCosmics%2FCommissioning2021-CosmicTP-PromptReco-v1%2FRAW-RECO+run%3D344063
    
    xrdcp root://xrootd.unl.edu///store/data/Commissioning2021/Cosmics/RAW-RECO/CosmicTP-PromptReco-v1/000/344/063/00000/10f95c97-4f96-4e33-93c7-2363d7a75b9e.root .
    
    
    
    just RAW
    https://cmsweb.cern.ch/das/request?instance=prod/global&input=file+dataset%3D%2FCosmics%2FCommissioning2021-v1%2FRAW+run%3D344063
    
    
    xrdcp root://xrootd.unl.edu///store/data/Commissioning2021/Cosmics/RAW/v1/000/344/063/00000/048645d2-0b33-4882-b99f-56dce7d6f19f.root  .
    
    
    ~~~
    SP = Super Pointing  TP = Tracker Pointing
    essentially it is a filter to select events through Tracker (TP) or even through the Pixel (SP) 
    ~~~

    https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=file+dataset%3D%2FCosmics%2FCommissioning2021-CosmicSP-PromptReco-v1%2FRAW-RECO+run%3D344063
    
    xrdcp root://xrootd.unl.edu///store/data/Commissioning2021/Cosmics/RAW-RECO/CosmicSP-PromptReco-v1/000/344/063/00000/3ef1ea68-1f7b-48a6-b59d-cb7dfc8f9d26.root  .  
    
    
    
    
    

    
    
Extract file for the iSpy interface
====


    https://github.com/cms-outreach/ispy-analyzers

    cd /afs/cern.ch/user/a/amassiro/work/RC/TEST
    cmsrel CMSSW_11_3_4
    cd CMSSW_11_3_4/src
    cmsenv
    git clone https://github.com/cms-outreach/ispy-analyzers.git ISpy/Analyzers  --branch cmssw11
    git clone https://github.com/cms-outreach/ispy-services.git ISpy/Services  --branch cmssw11
    
compile:

    scram b -j 10

    cd ISpy/Analyzers

    
    
    
    
    
    
    
    
    
    
    
    cmsrel CMSSW_10_2_9/
    cd CMSSW_10_2_9/src
    cmsenv
    git clone https://github.com/cms-outreach/ispy-analyzers.git ISpy/Analyzers 
    git clone https://github.com/cms-outreach/ispy-services.git ISpy/Services
    
    scram b -j 10

    cd ISpy/Analyzers

    
    
    
modify the file:

    python/ispy_10_X_X_cfg.py
    
    python/ispy_CRUZET_cfg.py
    
    python/ispy_Run3_cosmics.py

Add you file in the input
BE CAREFUL of the cuts defines in the file

    cmsRun python/ispy_10_X_X_cfg.py
    cmsRun python/ispy_CRUZET_cfg.py
    cmsRun python/ispy_Run3_cosmics.py
    cmsRun python/ispy_CRUZET_2021.py
    
The .ig files are the input for the next step.


iSpy
====

Download the .ig file on your computer
Go to 

    https://ispy-webgl-dev.web.cern.ch/
    
Open file > Open local file > open the .ig file
Select the event.
Play with the graphical interface
Once you are happy save the 3D scene with Shift+E in case you want to ask for an interactive page




