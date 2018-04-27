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


