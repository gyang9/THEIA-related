# THEIA-related 

Check out these code and then run:

$ g++ -std=c++11 -o main main.cc THEIALoop.cc root-config --cflags --glibs

$ ./main

Example of 100 events will be generated with flux reweights added as well as the signal/background tagger.

For the output, fluxWeight[0] is duneflux/atmflux without oscillation and fluxWeight[1] is the same but with oscillation;

signal tagger type: -1 -> not signal, 1-> 1 ring 0 decay, 2-> 1ring 1decay, 3-> 2 ring 0 decay

background type the same as singal.

The inputs include honda atm. flux, DUNE flux and SKIV ntuple.

I provided the first two. You need to input the SKIV ntuple. To directly run, make it ./input/combined.root 

Then those files should go to TMVA BDT.

You must install a ROOT 6 with TMVA!!

Then put the TMVA builder under current directory.

Then you can either

- $ root -l -q TMVAClassification.C arguments

or

- $ make

- $ ./TMVAClassification arguments

This gives you signal and background separation weights file and you can check the performance from the output files.

Then run through TMVAClassificationApplication_gy using either of the two methods above. This will add the TMVA variable to the tree.

Note that the TMVA BDT must be done for 1 ring 0 decay, 1 ring 1 decay and 2 ring 0 decay separately!

Next step is to generate histograms for each cases based on all pre-cuts and TMVA cuts. The TMVA cuts can be applied as a function of the energy bin.
Compile:

g++ -std=c++11 -o runsklooper runsklooper.C sklooper.C -lRooFit -lHtml -lMinuit -lRooFitCore `root-config --cflags --glibs`

Run:

for ESTEP in 0.25 0.1
do
  for TSTEP in 0.01
  do
    for VAR in 0.12
    do
        #./runsklooper 0.25 FHC 2 1 $VAR $ESTEP $TSTEP
    done
  done
done

First arguement 0.25 is the background fraction, 0.25 means 50% background assumed. Second arguement FHC is the horn current, third and fourth indicate the ring and decay numbers.
For 1 ring 0 decay: 3 1; 1 ring 1decay: 3 2; 2 ring 0 decay: 5 1; 2 ring 1 decay: 5 2; 3 ring 0 decay: 5 3; 3 ring 1 decay: 5 4.
Fifth arguement $VAR is the DUNE flux cut, use 0.12 means no cut on flux tail.
Sixth arguement $ESTEP is the step size of energy bin for TMVA cut applied.
Seventh arguement $TSTEP is the step size of TMVA variable to be applied.

Last thing is to make plot, use:

root -l makeratios_all_withOld.C 0.000000 FHC 5 2 1 0.120000 0.250000 0.010000

First arguement is background fraction, thrid and fourth are ring and decay indicators.
Fifth is "if you want a beautiful version of plots", 1 means you want it, also select 1 probably.
Sixth is flux cut, seventh and eighth are step size for energy bin and TMVA bin to apply TMVA cut.


