Event display
====

For CRUZET 2025

    /eos/cms/store/group/visualization/run389523/run389523_ls0008_streamEvDOutput2_dqmcluster.root
    
    https://fireworks.cern.ch/cmsShowWeb/revetor.pl


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

    cmsrel CMSSW_11_3_4/
    cd CMSSW_11_3_4/src
    cmsenv
    git clone https://github.com/cms-outreach/ispy-analyzers.git ISpy/Analyzers 
    git clone https://github.com/cms-outreach/ispy-services.git ISpy/Services
    
some fixes:

    rm ./ISpy/Analyzers/interface/ISpyCaloTau.h ./ISpy/Analyzers/src/ISpyCaloTau.cc
    
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







Find the events
====


    /eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/
    
    
    cd /afs/cern.ch/user/a/amassiro/work/RC/CMSSW_12_1_0_pre3/src
    cmsenv
    r99t ~/.root_fwlite.C  file.root
    
    
    
    #include "DataFormats/FWLite/interface/Event.h"
    #include "PhysicsTools/FWLite/interface/Scanner.h"

    fwlite::Event muonEvents(_file0)    
    fwlite::Scanner<std::vector<reco::Muon> > muons(&muonEvents, "muons");

    muons.scan("pt:eta:phi:track.numberOfValidHits","isTrackerMuon");

    
    
    r99t ~/.root_fwlite.C testing.c 

    
    
    r99t ~/.root_fwlite.C 
    
    std::vector<std::string> tutti = {"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/*.root"}
    
    
    
    
    #include "DataFormats/FWLite/interface/ChainEvent.h"
    #include "PhysicsTools/FWLite/interface/Scanner.h"


    
    std::vector<std::string> tutti = {
    "/tmp/amassiro/058d3e2f-db7d-4079-b093-18010acf00e8.root",
    "/tmp/amassiro/0cf74522-2861-4079-957d-c90fe7009137.root",
    "/tmp/amassiro/12331718-131a-4b82-af78-06ac3510c308.root",
    "/tmp/amassiro/1a12153e-ee3e-44ef-832d-49819f42d65f.root",
    "/tmp/amassiro/1b031e7d-d1c2-4ca3-8291-6c227ba981d0.root",
    "/tmp/amassiro/1f7c4813-9229-4f7f-96f2-80c191f45abc.root",
    "/tmp/amassiro/254ff4ee-eee7-4757-8ab1-4dd64d89f47a.root",
    "/tmp/amassiro/2b16d124-0330-4509-9d11-91a52a8b9fe0.root",
    "/tmp/amassiro/495e47a4-e08f-48b5-a5bc-7b90e0acc002.root",
    "/tmp/amassiro/49e2dc4c-f834-4add-b415-7fab6e7d414f.root",
    "/tmp/amassiro/4e410d11-e238-46fb-9f24-914e0c4230fc.root"
    }

    fwlite::ChainEvent muonEvents(tutti)    

    fwlite::Scanner<std::vector<reco::Muon> > muons(&muonEvents, "muons");

    muons.scan("pt:eta:phi:track.numberOfValidHits","isTrackerMuon");

    muons.scan("pt:eta:phi:track.numberOfValidHits","isGlobalMuon");
    

    
       std::vector<std::string> tutti = {
    "/tmp/amassiro/254ff4ee-eee7-4757-8ab1-4dd64d89f47a.root",
    }
  
    
     std::vector<std::string> tutti = {
    "/tmp/amassiro/1f7c4813-9229-4f7f-96f2-80c191f45abc.root",
    "/tmp/amassiro/254ff4ee-eee7-4757-8ab1-4dd64d89f47a.root",
    "/tmp/amassiro/2b16d124-0330-4509-9d11-91a52a8b9fe0.root",
    "/tmp/amassiro/495e47a4-e08f-48b5-a5bc-7b90e0acc002.root",
    "/tmp/amassiro/49e2dc4c-f834-4add-b415-7fab6e7d414f.root",
    "/tmp/amassiro/4e410d11-e238-46fb-9f24-914e0c4230fc.root"
    }

     std::vector<std::string> tutti = {
    "/tmp/amassiro/495e47a4-e08f-48b5-a5bc-7b90e0acc002.root",
    "/tmp/amassiro/49e2dc4c-f834-4add-b415-7fab6e7d414f.root",
    "/tmp/amassiro/4e410d11-e238-46fb-9f24-914e0c4230fc.root"
    }
   
    
    


    
    ls -alrth /eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/*.root | awk '{print "\"" $9 "\","}'

    
    
std::vector<std::string> tutti = {    
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/03ba5a27-f20e-4762-9605-7bcdfc815458.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/cb8a57d4-19b8-422c-aade-452f01b56356.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/254ff4ee-eee7-4757-8ab1-4dd64d89f47a.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/65e03e99-c262-4712-9ddd-600f8b613372.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/058d3e2f-db7d-4079-b093-18010acf00e8.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/63930dc5-848a-4c4a-a273-ece14de6ecfb.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/5b4513da-dd9f-40bc-a92b-5f40c173f92c.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/3350685c-f75a-4120-8be9-e297c3c5fa34.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/8634aa57-1c17-408c-9b37-77d1b5c04b04.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/e6bfd002-1be8-4d22-b3c1-0ecaee5f48c2.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/cce20614-beac-45c5-89aa-69627b93d32e.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/1a12153e-ee3e-44ef-832d-49819f42d65f.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/c23a58eb-92b9-4837-a388-94c782bae3be.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/343bd252-be7e-4687-a7cb-4bda8ff129f7.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/ca70223f-b9bf-4d6d-b7f8-3e0233d19693.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/35e59634-ce79-405e-8216-f08e0b51e162.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/49e2dc4c-f834-4add-b415-7fab6e7d414f.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/ebb1c5dd-ba6e-481f-8bdf-38b2fd65323e.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/c1b39a45-f443-42b4-8812-bb0536a02b0a.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/5cca15ad-0c6d-4d3e-bb48-be54b7334dc8.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/66ec175d-276e-41a1-a8ef-cdd0ec47106a.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/9bc65325-617d-4ea7-b4ed-187452541ead.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/96cb253e-bc3e-43f6-8242-1b644c2eab3e.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/f52c163e-4573-4c38-bf99-53bb7f438fc7.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/b676f624-1fd0-4288-9cd5-00658649f031.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/03dc5211-4339-4636-be35-253f51a318a0.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/2b16d124-0330-4509-9d11-91a52a8b9fe0.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/3aab3616-777c-4564-aa42-58e4f4323acf.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/cdfc0742-bd3b-4415-8dd8-1ff45c024ace.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/644d0716-9bca-4292-b72d-9c3edccd1c68.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/62f3f316-6491-4836-878f-725b5dda00f6.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/31b6f400-e876-4e61-b41e-5f96ad79b3b7.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/e69b7e0d-23ea-47ad-8322-6ec8e0ae7aab.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/76de35a5-846b-4853-8e9f-d2c465fad4e8.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/4e410d11-e238-46fb-9f24-914e0c4230fc.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/c0bbbb3b-fa28-4984-8b66-c4da59caeab1.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/32ecce69-fda5-497e-8e46-b8ab7f29e634.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/8f14c3c5-3075-4446-8fe6-04f8e42b51fb.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/c68440db-8811-4b4c-b928-2d44b1f8fd28.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/dc87a12a-3f20-4420-a0c5-29de4e4cd6d2.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/1f7c4813-9229-4f7f-96f2-80c191f45abc.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/8ad03ca3-2db7-4e50-a434-cba32de0a26c.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/959f8f3f-0f23-42e4-a83a-99086984e43a.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/0cf74522-2861-4079-957d-c90fe7009137.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/cb652bc7-886b-477b-8810-6901a8fa9d27.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/35ee08f5-00de-4c60-93ec-6e038e11dee8.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/b77254be-fd77-4e33-96c4-fb98bfdf0f1b.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/5645609e-391f-48ed-a55e-c784bf3dbbd4.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/96317c82-ca81-4792-be46-02e266ef5e35.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/1b031e7d-d1c2-4ca3-8291-6c227ba981d0.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/495e47a4-e08f-48b5-a5bc-7b90e0acc002.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/12331718-131a-4b82-af78-06ac3510c308.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/70b1bbb4-5ea0-4ed3-bb55-851ebff86708.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/55a6129c-1067-4262-b269-b1151e924e6d.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/9a3391e6-e46a-4c40-81b3-247608c8e4fa.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/a344b2ae-0ba8-4fc3-9f16-7f24d2a5917e.root",
"/eos/cms/store/express/Commissioning2021/ExpressPhysics/FEVT/Express-v1/000/346/373/00000/a0dd2641-ccdb-477b-996c-34a06d32527d.root",
}
  
    


