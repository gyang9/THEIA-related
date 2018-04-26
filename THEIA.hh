#include <TH2F.h>
#include <TGraph.h>
#include <TSpline.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TMatrixDSym.h>
#include <TMatrixDSymEigen.h>
#include <TVectorD.h>

using namespace std;

class THEIA {
public:
  
  THEIA();
  ~THEIA();


  void SetMinPE(double pe){}
  double GetMinPE(){return 1;}


  void Init();
  void Delete();


  private:

};

class THAddition {
public:
  THAddition();
  ~THAddition();

  void Init();
  void Delete();


  private:
};

