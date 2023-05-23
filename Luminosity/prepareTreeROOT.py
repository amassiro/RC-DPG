
#
# fill_8736.csv
#

import ROOT

#filenameCVS = "fill_8736.csv"
filenameCVS = "fill_8786.csv"


#ROOT.EnableImplicitMT()
# df = ROOT.RDF.FromCSV(filenameCVS)
df = ROOT.RDF.MakeCsvDataFrame(filenameCVS)
# https://root-forum.cern.ch/t/attributeerror-type-object-rdf-has-no-attribute-fromcsv/54899

#df2 = df.Filter("x > 0").Define("y", "x*x")
#control_h = df2.Histo1D("y")
#df.Snapshot("newtree", "newfile.root", ("fill", "run", "ls", "datetime", "time", "avgpu", "bcid"))
df.Snapshot("newtree", "newfile.root")

