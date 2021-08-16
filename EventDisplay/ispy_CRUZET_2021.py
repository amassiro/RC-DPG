import os

# Stuff for singularity on lxplus
outPath = os.getenv('ANALYSIS_OUTDIR')

if not outPath:
  outPath = ''
else:
  outPath += '/'

import FWCore.ParameterSet.Config as cms

process = cms.Process("ISPY")

process.load("Configuration.StandardSequences.MagneticField_cff")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load("Configuration.StandardSequences.GeometryDB_cff")

#from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_data', '')

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = '113X_dataRun3_Prompt_v3' 
#process.GlobalTag.globaltag = '112X_dataRun3_Prompt_v6' 


import FWCore.Utilities.FileUtils as FileUtils

process.source = cms.Source(
    'PoolSource',
    #fileNames = cms.untracked.vstring(
    #'root://cmsxrootd.fnal.gov//store/data/Run2018D/DoubleMuon/AOD/PromptReco-v2/000/324/998/00000/AF519538-7FE5-4A4B-BD66-6FE4900CB5C6.root'
    #'root://cmsxrootd.fnal.gov//store/data/Run2018B/Charmonium/AOD/17Sep2018-v1/120000/3ADC2E5A-4F1B-4546-8CB6-58DDBBC921D3.root'
  #)
    #fileNames = cms.untracked.vstring('file:/tmp/amassiro/03ec45f7-d8ff-42ac-a85e-e0e9db92a36f.root'),
    #fileNames = cms.untracked.vstring('file:/tmp/amassiro/10f95c97-4f96-4e33-93c7-2363d7a75b9e.root'),
    #fileNames = cms.untracked.vstring('file:/tmp/amassiro/048645d2-0b33-4882-b99f-56dce7d6f19f.root'),
    fileNames = cms.untracked.vstring('file:/tmp/amassiro/3ef1ea68-1f7b-48a6-b59d-cb7dfc8f9d26.root'),
    )

from FWCore.MessageLogger.MessageLogger_cfi import *

process.add_(
        cms.Service("ISpyService",
                        outputFileName = cms.untracked.string('igOutput.ig'),
                        outputESFilename = cms.untracked.string('ES.ig'),
                        outputFilePath = cms.untracked.string(outPath),
                        outputIg = cms.untracked.bool(True),
                        outputMaxEvents = cms.untracked.int32(-1),
                        )
        )

process.options = cms.untracked.PSet(
        SkipEvent = cms.untracked.vstring('ProductNotFound')
            )

process.maxEvents = cms.untracked.PSet(
        input = cms.untracked.int32(-1)
        )

process.load("ISpy.Analyzers.ISpyEvent_cfi")
process.load('ISpy.Analyzers.ISpyCSCRecHit2D_cfi')
process.load('ISpy.Analyzers.ISpyCSCSegment_cfi')
process.load('ISpy.Analyzers.ISpyDTRecHit_cfi')
process.load('ISpy.Analyzers.ISpyDTRecSegment4D_cfi')
process.load('ISpy.Analyzers.ISpyEBRecHit_cfi')
process.load('ISpy.Analyzers.ISpyEERecHit_cfi')
process.load('ISpy.Analyzers.ISpyESRecHit_cfi')
process.load('ISpy.Analyzers.ISpyHBRecHit_cfi')
process.load('ISpy.Analyzers.ISpyHERecHit_cfi')
process.load('ISpy.Analyzers.ISpyHFRecHit_cfi')
process.load('ISpy.Analyzers.ISpyHORecHit_cfi')
process.load('ISpy.Analyzers.ISpyMET_cfi')
process.load('ISpy.Analyzers.ISpyPFMET_cfi')
process.load('ISpy.Analyzers.ISpyMuon_cfi')
process.load('ISpy.Analyzers.ISpyJet_cfi')
process.load('ISpy.Analyzers.ISpyPFJet_cfi')
process.load('ISpy.Analyzers.ISpyPhoton_cfi')
process.load('ISpy.Analyzers.ISpyRPCRecHit_cfi')
process.load('ISpy.Analyzers.ISpySuperCluster_cfi')

process.load('ISpy.Analyzers.ISpyTrackExtrapolation_cfi')
process.load('ISpy.Analyzers.ISpyTriggerEvent_cfi')
process.load('ISpy.Analyzers.ISpyVertex_cfi')

process.ISpyCSCRecHit2D.iSpyCSCRecHit2DTag = cms.InputTag("csc2DRecHits")
process.ISpyCSCSegment.iSpyCSCSegmentTag = cms.InputTag("cscSegments")
process.ISpyDTRecHit.iSpyDTRecHitTag = cms.InputTag('dt1DRecHits')
process.ISpyDTRecSegment4D.iSpyDTRecSegment4DTag = cms.InputTag('dt4DSegments')

process.ISpyEBRecHit.iSpyEBRecHitTag = cms.InputTag('reducedEcalRecHitsEB')
process.ISpyEERecHit.iSpyEERecHitTag = cms.InputTag('reducedEcalRecHitsEE')
process.ISpyESRecHit.iSpyESRecHitTag = cms.InputTag('reducedEcalRecHitsES')

process.ISpyHBRecHit.iSpyHBRecHitTag = cms.InputTag("reducedHcalRecHits:hbhereco")
process.ISpyHERecHit.iSpyHERecHitTag = cms.InputTag("reducedHcalRecHits:hbhereco")
process.ISpyHFRecHit.iSpyHFRecHitTag = cms.InputTag("reducedHcalRecHits:hfreco")
process.ISpyHORecHit.iSpyHORecHitTag = cms.InputTag("reducedHcalRecHits:horeco")

process.ISpyMET.iSpyMETTag = cms.InputTag("htMetIC5")
process.ISpyMuon.iSpyMuonTag = cms.InputTag("muons")

process.ISpyPFJet.iSpyPFJetTag = cms.InputTag('ak4PFJets')
process.ISpyPFJet.etMin = cms.double(30.0)
process.ISpyPFJet.etaMax = cms.double(2.5)

process.ISpyPhoton.iSpyPhotonTag = cms.InputTag('photons')
process.ISpyRPCRecHit.iSpyRPCRecHitTag = cms.InputTag("rpcRecHits")
process.ISpyVertex.iSpyVertexTag = cms.InputTag('offlinePrimaryVertices')

process.ISpyTrackExtrapolation.iSpyTrackExtrapolationTag = cms.InputTag("trackExtrapolator")
process.ISpyTrackExtrapolation.trackPtMin = cms.double(0.0)




#
# CRUZET
#
process.load("ISpy.Analyzers.ISpyEventFeatures_cfi")
process.load("ISpy.Analyzers.ISpyEvent_cfi")
process.load("ISpy.Analyzers.ISpyBasicCluster_cfi")
process.load("ISpy.Analyzers.ISpyCSCSegment_cfi")
process.load("ISpy.Analyzers.ISpyCSCStripDigi_cfi")
process.load("ISpy.Analyzers.ISpyCSCWireDigi_cfi")
process.load("ISpy.Analyzers.ISpyCaloTower_cfi")
process.load('ISpy.Analyzers.ISpyDTDigi_cfi')
process.load('ISpy.Analyzers.ISpyDTRecHit_cfi')
process.load("ISpy.Analyzers.ISpyDTRecSegment4D_cfi")
process.load("ISpy.Analyzers.ISpyEBRecHit_cfi")
process.load("ISpy.Analyzers.ISpyEERecHit_cfi")
process.load("ISpy.Analyzers.ISpyESRecHit_cfi")
process.load("ISpy.Analyzers.ISpyHBRecHit_cfi")
process.load("ISpy.Analyzers.ISpyHERecHit_cfi")
process.load("ISpy.Analyzers.ISpyHFRecHit_cfi")
process.load("ISpy.Analyzers.ISpyHORecHit_cfi")
process.load("ISpy.Analyzers.ISpyJet_cfi")
process.load("ISpy.Analyzers.ISpyL1GlobalTriggerReadoutRecord_cfi")
process.load("ISpy.Analyzers.ISpyMET_cfi")
process.load("ISpy.Analyzers.ISpyMuon_cfi")
process.load("ISpy.Analyzers.ISpyPixelDigi_cfi")
process.load('ISpy.Analyzers.ISpyRPCRecHit_cfi')
process.load("ISpy.Analyzers.ISpySiPixelCluster_cfi")
process.load("ISpy.Analyzers.ISpySiPixelRecHit_cfi")
process.load("ISpy.Analyzers.ISpySiStripCluster_cfi")
process.load("ISpy.Analyzers.ISpySiStripDigi_cfi")
process.load("ISpy.Analyzers.ISpyTrack_cfi")
process.load("ISpy.Analyzers.ISpyTrackingRecHit_cfi")
process.load("ISpy.Analyzers.ISpyTriggerEvent_cfi")

process.ISpyCSCSegment.iSpyCSCSegmentTag = cms.InputTag("muonCSCSegments")
process.ISpyDTRecHit.iSpyDTRecHitTag = cms.InputTag("dt1DRecHits")
process.ISpyRPCRecHit.iSpyRPCRecHitTag = cms.InputTag("rpcRecHits")
process.ISpyMET.iSpyMETTag = cms.InputTag('genMetIC5GenJets')
process.ISpyMuon.iSpyMuonTag = cms.InputTag('muons')
process.ISpySiStripDigi.iSpySiStripDigiTag = cms.InputTag('siStripDigis:ZeroSuppressed')
#process.ISpyTrack.iSpyTrackTags = cms.VInputTag(cms.InputTag('cosmicMuons'))
#process.ISpyTrackingRecHit.iSpyTrackingRecHitTags = cms.VInputTag(cms.InputTag('cosmicMuons'))

process.ISpyTrack.iSpyTrackTags = cms.VInputTag(
                   cms.InputTag('cosmicMuons'),
                   cms.InputTag('regionalCosmicTracks')
                   )

process.ISpyTrackingRecHit.iSpyTrackingRecHitTags = cms.VInputTag(
                   cms.InputTag('cosmicMuons'),
                   cms.InputTag('regionalCosmicTracks')
                   )


#process.ISpyTrackExtrapolation.iSpyMuonTrackExtrapolationTag = cms.InputTag("muons")
                                        


process.iSpy = cms.Path(process.ISpyEvent*
                       #process.ISpyEventSetup*
                       process.ISpyEventFeatures*
                       process.ISpyBasicCluster*
                       process.ISpyCSCSegment*
                       process.ISpyCSCStripDigi*
                       process.ISpyCSCWireDigi*
                       process.ISpyCaloTower*
                       process.ISpyTrack*
                       process.ISpyTrackingRecHit*
                       process.ISpyDTRecSegment4D*
                       process.ISpyDTDigi*
                       process.ISpyDTRecHit*
                       process.ISpyRPCRecHit*
                       process.ISpyEBRecHit*
                       process.ISpyEERecHit*
                       process.ISpyESRecHit*
                       process.ISpyHBRecHit*
                       process.ISpyHERecHit*
                       process.ISpyHFRecHit*
                       process.ISpyHORecHit*
                       process.ISpyJet*
                       process.ISpyMET*
                       process.ISpyMuon*
                       process.ISpyPixelDigi*
                       process.ISpySiPixelCluster*
                       process.ISpySiPixelRecHit*
                       #process.ISpySiStripCluster*
                       process.ISpySiStripDigi*
                       process.ISpyL1GlobalTriggerReadoutRecord*
                       process.ISpyTrackExtrapolation* # MY
                       process.ISpyTriggerEvent
                       )



#process.iSpy = cms.Path(process.ISpyEvent*
                        #process.ISpyCSCRecHit2D*
                        #process.ISpyCSCSegment*
                        #process.ISpyDTRecHit*
                        #process.ISpyDTRecSegment4D*
                        #process.ISpyEBRecHit*
                        #process.ISpyEERecHit*
                        #process.ISpyESRecHit*
                        #process.ISpyHBRecHit*
                        #process.ISpyHERecHit*
                        #process.ISpyHFRecHit*
                        #process.ISpyHORecHit*
                        #process.ISpyMuon*
                        #process.ISpyPFJet*
                        #process.ISpyPFMET*
                        #process.ISpyPhoton*
                        #process.ISpyRPCRecHit*
                        #process.ISpyTrackExtrapolation*
                        #process.ISpyVertex)


#process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
#process.load('Configuration.StandardSequences.ReconstructionCosmics_cff')
#process.p3= cms.Path(process.RawToDigi)
#process.p4= cms.Path(process.reconstructionCosmics)
#process.schedule = cms.Schedule(process.p3,process.p4,process.iSpy)


process.schedule = cms.Schedule(process.iSpy)


