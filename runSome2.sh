#./runsklooper 0.25 2 1
#./runsklooper 0.01 2 1
#./runsklooper 0.0025 2 1

#./runsklooper 0.25 4 2
#./runsklooper 0.01 4 2
#./runsklooper 0.0025 4 2

#./runsklooper 0.25 5 3
#./runsklooper 0.01 5 3
#./runsklooper 0.0025 5 3

#./runsklooper 0.25 5 4
#./runsklooper 0.01 5 4
#./runsklooper 0.0025 5 4

g++ -std=c++11 -o runsklooper runsklooper.C sklooper.C -lRooFit -lHtml -lMinuit -lRooFitCore `root-config --cflags --glibs`


for ESTEP in 0.1
do
  for TSTEP in 0.01 
  do
    for VAR in 0.10
    do
        ./runsklooper 0.25 FHC 3 1 $VAR $ESTEP $TSTEP
        ./runsklooper 0.25 FHC 3 2 $VAR $ESTEP $TSTEP
        ./runsklooper 0.25 FHC 5 1 $VAR $ESTEP $TSTEP
        ./runsklooper 0.25 FHC 5 2 $VAR $ESTEP $TSTEP
        ./runsklooper 0.25 FHC 5 3 $VAR $ESTEP $TSTEP
        ./runsklooper 0.25 FHC 5 4 $VAR $ESTEP $TSTEP
        ./runsklooper 0.25 RHC 3 1 $VAR $ESTEP $TSTEP
        ./runsklooper 0.25 RHC 3 2 $VAR $ESTEP $TSTEP
        ./runsklooper 0.25 RHC 5 1 $VAR $ESTEP $TSTEP
        ./runsklooper 0.25 RHC 5 2 $VAR $ESTEP $TSTEP
        ./runsklooper 0.25 RHC 5 3 $VAR $ESTEP $TSTEP
        ./runsklooper 0.25 RHC 5 4 $VAR $ESTEP $TSTEP
     done
  done
done
