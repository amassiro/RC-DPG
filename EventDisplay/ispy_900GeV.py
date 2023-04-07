import FWCore.ParameterSet.Config as cms

from Configuration.Eras.Era_Run3_cff import Run3
process = cms.Process("process", Run3)

process.load("Configuration.StandardSequences.GeometryDB_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.GlobalTag.globaltag = '130X_dataRun3_Express_v1'




process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
     'file:/eos/cms/store/group/visualization/run365765/run365765_ls0087_streamEvDOutput2_dqmcluster.root'
    )
    ,eventsToProcess = cms.untracked.VEventRange('365765:212565968')
)
 
from FWCore.MessageLogger.MessageLogger_cfi import *

process.add_(
    cms.Service("ISpyService",
    outputFileName = cms.untracked.string('run3-900GeV.ig'),
    outputMaxEvents = cms.untracked.int32(25)
    )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(25)
)

process.load('ISpy.Analyzers.ISpyEvent_cfi')

process.load('ISpy.Analyzers.ISpyCSCRecHit2D_cfi')
process.load("ISpy.Analyzers.ISpyCSCSegment_cfi")
process.load("ISpy.Analyzers.ISpyCSCStripDigi_cfi")
process.load("ISpy.Analyzers.ISpyCSCWireDigi_cfi")
process.load("ISpy.Analyzers.ISpyCSCCorrelatedLCTDigi_cfi")
process.load('ISpy.Analyzers.ISpyDTDigi_cfi')
process.load('ISpy.Analyzers.ISpyDTRecHit_cfi')
process.load("ISpy.Analyzers.ISpyDTRecSegment4D_cfi")
process.load('ISpy.Analyzers.ISpyRPCRecHit_cfi')

process.load('ISpy.Analyzers.ISpyEBRecHit_cfi')
process.load('ISpy.Analyzers.ISpyEERecHit_cfi')
process.load('ISpy.Analyzers.ISpyESRecHit_cfi')
process.load('ISpy.Analyzers.ISpyHBRecHit_cfi')
process.load('ISpy.Analyzers.ISpyHERecHit_cfi')
process.load('ISpy.Analyzers.ISpyHFRecHit_cfi')
process.load('ISpy.Analyzers.ISpyHORecHit_cfi')

process.load('ISpy.Analyzers.ISpyMuon_cfi')
process.load('ISpy.Analyzers.ISpyVertex_cfi')

#process.load("ISpy.Analyzers.ISpyPixelDigi_cfi")
#process.load("ISpy.Analyzers.ISpySiPixelCluster_cfi")
#process.load("ISpy.Analyzers.ISpySiPixelRecHit_cfi")
#process.load("ISpy.Analyzers.ISpySiStripCluster_cfi")
#process.load("ISpy.Analyzers.ISpySiStripDigi_cfi")
process.load("ISpy.Analyzers.ISpyTrack_cfi")
process.load("ISpy.Analyzers.ISpyTrackingRecHit_cfi")


process.load("ISpy.Analyzers.ISpyGEMSegment_cfi")
process.load("ISpy.Analyzers.ISpyGEMRecHit_cfi")


process.ISpyCSCRecHit2D.iSpyCSCRecHit2DTag = cms.InputTag("csc2DRecHits")
process.ISpyCSCSegment.iSpyCSCSegmentTag = cms.InputTag("cscSegments")

process.ISpyEBRecHit.iSpyEBRecHitTag = cms.InputTag('ecalRecHit:EcalRecHitsEB')
process.ISpyEERecHit.iSpyEERecHitTag = cms.InputTag('ecalRecHit:EcalRecHitsEE')
process.ISpyHBRecHit.iSpyHBRecHitTag = cms.InputTag("hbhereco")
process.ISpyHERecHit.iSpyHERecHitTag = cms.InputTag("hbhereco")
process.ISpyHFRecHit.iSpyHFRecHitTag = cms.InputTag("hfreco")
process.ISpyHORecHit.iSpyHORecHitTag = cms.InputTag("horeco")

process.out = cms.OutputModule(
        "PoolOutputModule",
            fileName = cms.untracked.string("run3-900GeV.root")
        )

process.iSpy = cms.Path(process.ISpyEvent*
                        process.ISpyCSCSegment*
                        process.ISpyCSCCorrelatedLCTDigi*
                        process.ISpyCSCRecHit2D*
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
                        process.ISpyMuon*
                        process.ISpyVertex)
                        #process.ISpyGEMSegment*
                        #process.ISpyGEMRecHit)
                        #process.ISpyPixelDigi*
                        #process.ISpySiPixelCluster*
                        #process.ISpySiPixelRecHit*
                        #process.ISpySiStripCluster*
                        #process.ISpySiStripDigi)

                        
process.schedule = cms.Schedule(process.iSpy)
process.outpath = cms.EndPath(process.out)


