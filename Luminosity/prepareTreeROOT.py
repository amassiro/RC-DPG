
#
# fill_8736.csv
#

import ROOT


def main(fill: int = 8736):
    
    filenameCVS = 'fill_' + fill + '.csv'
    filenameROOT = 'fill_' + fill + '.root'
    
    df = ROOT.RDF.MakeCsvDataFrame(filenameCVS)
    # https://root-forum.cern.ch/t/attributeerror-type-object-rdf-has-no-attribute-fromcsv/54899

    df.Snapshot("newtree", filenameROOT)




import sys
print (sys.argv)

main(fill = sys.argv[1])

#main(fill=8786)

