//////////////////////////////////////////////////////////
////G.Yang Apr.25 2018

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH2D.h>
#include <iostream>
#include <fstream>
#include <TMath.h>
#include "TSystem.h"

#include "THEIALoop.hh"

//#ifdef THEIA_cxx

void THEIA::LoadFile(TTree* tree)
{
   Init(tree);
}

THEIA::THEIA(TTree* tree)
{
    Init(tree);
}

THEIA::~THEIA()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t THEIA::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t THEIA::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void THEIA::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   std::cout<<"in Init(), point 1"<<std::endl;
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);


   std::cout<<"in Init(), point 2"<<std::endl;
   fChain->SetBranchAddress("nring", &nring, &b_nring);

   std::cout<<"in Init(), point 2.1"<<std::endl;
   fChain->SetBranchAddress("nrun", &nrun, &b_nrun);
   fChain->SetBranchAddress("nev", &nev, &b_nev);
   fChain->SetBranchAddress("nsub", &nsub, &b_nsub);
   fChain->SetBranchAddress("cate", &cate, &b_cate);
   fChain->SetBranchAddress("potot", &potot, &b_potot);
   fChain->SetBranchAddress("nhit", &nhit, &b_nhit);
   fChain->SetBranchAddress("pomax", &pomax, &b_pomax);
   fChain->SetBranchAddress("potota", &potota, &b_potota);
   fChain->SetBranchAddress("nhita", &nhita, &b_nhita);
   fChain->SetBranchAddress("nhitac", &nhitac, &b_nhitac);
   fChain->SetBranchAddress("pomaxa", &pomaxa, &b_pomaxa);
   fChain->SetBranchAddress("wall", &wall, &b_wall);
   fChain->SetBranchAddress("evis", &evis, &b_evis);
   fChain->SetBranchAddress("rtsum", &rtsum, &b_rtsum);
   fChain->SetBranchAddress("rtmax", &rtmax, &b_rtmax);
   fChain->SetBranchAddress("wlen", &wlen, &b_wlen);
   fChain->SetBranchAddress("ip", ip, &b_ip);
   fChain->SetBranchAddress("pos", pos, &b_pos);
   fChain->SetBranchAddress("dir", dir, &b_dir);
   fChain->SetBranchAddress("dirtot", dirtot, &b_dirtot);
   fChain->SetBranchAddress("ang", ang, &b_ang);
   fChain->SetBranchAddress("rtot", rtot, &b_rtot);
   fChain->SetBranchAddress("amom", amom, &b_amom);
   fChain->SetBranchAddress("rtote", rtote, &b_rtote);
   fChain->SetBranchAddress("amome", amome, &b_amome);
   fChain->SetBranchAddress("rtotm", rtotm, &b_rtotm);
   fChain->SetBranchAddress("amomm", amomm, &b_amomm);
   fChain->SetBranchAddress("nsube", &nsube, &b_nsube);
   fChain->SetBranchAddress("ndcy", &ndcy, &b_ndcy);
   fChain->SetBranchAddress("ngate", &ngate, &b_ngate);
   fChain->SetBranchAddress("nbye", &nbye, &b_nbye);
   fChain->SetBranchAddress("probms", probms, &b_probms);
   fChain->SetBranchAddress("prmslg", prmslg, &b_prmslg);
   fChain->SetBranchAddress("date", date, &b_date);
   fChain->SetBranchAddress("time", time, &b_time);
   fChain->SetBranchAddress("elpsday", &elpsday, &b_elpsday);
   fChain->SetBranchAddress("numpo", numpo, &b_numpo);
   fChain->SetBranchAddress("apos", apos, &b_apos);
   fChain->SetBranchAddress("adir", adir, &b_adir);
   fChain->SetBranchAddress("aang", &aang, &b_aang);
   fChain->SetBranchAddress("agood", &agood, &b_agood);
   fChain->SetBranchAddress("wgain", &wgain, &b_wgain);
   fChain->SetBranchAddress("nbad", &nbad, &b_nbad);
   fChain->SetBranchAddress("nbada", &nbada, &b_nbada);
   fChain->SetBranchAddress("msdir", msdir, &b_msdir);
   fChain->SetBranchAddress("amomp", amomp, &b_amomp);
   fChain->SetBranchAddress("ange", ange, &b_ange);
   fChain->SetBranchAddress("angm", angm, &b_angm);
   fChain->SetBranchAddress("angp", angp, &b_angp);
   fChain->SetBranchAddress("ntot", ntot, &b_ntot);
   fChain->SetBranchAddress("probth", probth, &b_probth);
   fChain->SetBranchAddress("probpt", probpt, &b_probpt);
   fChain->SetBranchAddress("pi0like", pi0like, &b_pi0like);
   fChain->SetBranchAddress("pi0_e", pi0_e, &b_pi0_e);
   fChain->SetBranchAddress("pi0_dir", pi0_dir, &b_pi0_dir);
   fChain->SetBranchAddress("pi0mass", pi0mass, &b_pi0mass);
   fChain->SetBranchAddress("evisold", &evisold, &b_evisold);
   fChain->SetBranchAddress("evisoldxe", &evisoldxe, &b_evisoldxe);
   fChain->SetBranchAddress("evisnew", &evisnew, &b_evisnew);
   fChain->SetBranchAddress("nmue", &nmue, &b_nmue);
   fChain->SetBranchAddress("etype", etype, &b_etype);
   fChain->SetBranchAddress("etime", etime, &b_etime);
   fChain->SetBranchAddress("epos", epos, &b_epos);
   fChain->SetBranchAddress("edir", edir, &b_edir);
   fChain->SetBranchAddress("egood", egood, &b_egood);
   fChain->SetBranchAddress("ehit", ehit, &b_ehit);
   fChain->SetBranchAddress("mueprob", mueprob, &b_mueprob);
   fChain->SetBranchAddress("nmue_sel", &nmue_sel, &b_nmue_sel);
   fChain->SetBranchAddress("Rnring", &Rnring, &b_Rnring);
   fChain->SetBranchAddress("Rdir", Rdir, &b_Rdir);
   fChain->SetBranchAddress("Rang", Rang, &b_Rang);
   fChain->SetBranchAddress("Riring", &Riring, &b_Riring);
   fChain->SetBranchAddress("Rtwout", Rtwout, &b_Rtwout);
   fChain->SetBranchAddress("Rtwith", Rtwith, &b_Rtwith);
   fChain->SetBranchAddress("Alwout", &Alwout, &b_Alwout);
   fChain->SetBranchAddress("Alwith", &Alwith, &b_Alwith);
   fChain->SetBranchAddress("Qsmi", &Qsmi, &b_Qsmi);
   fChain->SetBranchAddress("Qsmo", &Qsmo, &b_Qsmo);
   fChain->SetBranchAddress("Qexi", &Qexi, &b_Qexi);
   fChain->SetBranchAddress("Qexo", &Qexo, &b_Qexo);
   fChain->SetBranchAddress("Pe5d", &Pe5d, &b_Pe5d);
   fChain->SetBranchAddress("En5d", &En5d, &b_En5d);
   fChain->SetBranchAddress("Eh5d", &Eh5d, &b_Eh5d);
   fChain->SetBranchAddress("Pe5do", &Pe5do, &b_Pe5do);
   fChain->SetBranchAddress("En5do", &En5do, &b_En5do);
   fChain->SetBranchAddress("Eh5do", &Eh5do, &b_Eh5do);
   fChain->SetBranchAddress("Rtadd", &Rtadd, &b_Rtadd);
   fChain->SetBranchAddress("Pdgeta", &Pdgeta, &b_Pdgeta);
   fChain->SetBranchAddress("Pd5d", &Pd5d, &b_Pd5d);
   fChain->SetBranchAddress("Pdthre", &Pdthre, &b_Pdthre);
   fChain->SetBranchAddress("Pd5do", &Pd5do, &b_Pd5do);
   fChain->SetBranchAddress("Delpd", &Delpd, &b_Delpd);
   fChain->SetBranchAddress("Ropena", Ropena, &b_Ropena);
   fChain->SetBranchAddress("Maxth", &Maxth, &b_Maxth);
   fChain->SetBranchAddress("Pkang", &Pkang, &b_Pkang);
   fChain->SetBranchAddress("Qrfct", &Qrfct, &b_Qrfct);
   fChain->SetBranchAddress("Pdfct", &Pdfct, &b_Pdfct);
   fChain->SetBranchAddress("Pkfct", &Pkfct, &b_Pkfct);
   fChain->SetBranchAddress("Agfct", &Agfct, &b_Agfct);
   fChain->SetBranchAddress("Dlfct", &Dlfct, &b_Dlfct);
   fChain->SetBranchAddress("Iflag", &Iflag, &b_Iflag);
   fChain->SetBranchAddress("Pmfct", &Pmfct, &b_Pmfct);
   fChain->SetBranchAddress("Imfct", &Imfct, &b_Imfct);
   fChain->SetBranchAddress("Rilike", &Rilike, &b_Rilike);
   fChain->SetBranchAddress("ri_ver", &ri_ver, &b_ri_ver);
   fChain->SetBranchAddress("ri_pid", &ri_pid, &b_ri_pid);
   fChain->SetBranchAddress("ri_nring", &ri_nring, &b_ri_nring);
   fChain->SetBranchAddress("ri_flag", ri_flag, &b_ri_flag);
   fChain->SetBranchAddress("ri_dlfct", ri_dlfct, &b_ri_dlfct);
   fChain->SetBranchAddress("ri_pdfct", ri_pdfct, &b_ri_pdfct);
   fChain->SetBranchAddress("ri_pkfct", ri_pkfct, &b_ri_pkfct);
   fChain->SetBranchAddress("ri_vafct", ri_vafct, &b_ri_vafct);
   fChain->SetBranchAddress("ri_total", ri_total, &b_ri_total);
   fChain->SetBranchAddress("ri_dir", ri_dir, &b_ri_dir);
   fChain->SetBranchAddress("ri_imfct", ri_imfct, &b_ri_imfct);
   fChain->SetBranchAddress("ri_pmfct", ri_pmfct, &b_ri_pmfct);
   fChain->SetBranchAddress("npar", &npar, &b_npar);
   fChain->SetBranchAddress("wallv", &wallv, &b_wallv);
   fChain->SetBranchAddress("ipv", ipv, &b_ipv);
   fChain->SetBranchAddress("posv", posv, &b_posv);
   fChain->SetBranchAddress("dirv", dirv, &b_dirv);
   fChain->SetBranchAddress("pmomv", pmomv, &b_pmomv);
   fChain->SetBranchAddress("light_flag", light_flag, &b_light_flag);
   fChain->SetBranchAddress("npar2", &npar2, &b_npar2);
   fChain->SetBranchAddress("wallv2", wallv2, &b_wallv2);
   fChain->SetBranchAddress("ipv2", ipv2, &b_ipv2);
   fChain->SetBranchAddress("iorg", iorg, &b_iorg);
   fChain->SetBranchAddress("posv2", posv2, &b_posv2);
   fChain->SetBranchAddress("dirv2", dirv2, &b_dirv2);
   fChain->SetBranchAddress("pmomv2", pmomv2, &b_pmomv2);
   fChain->SetBranchAddress("numnu", &numnu, &b_numnu);
   fChain->SetBranchAddress("mode", &mode, &b_mode);
   fChain->SetBranchAddress("ipnu", ipnu, &b_ipnu);
   fChain->SetBranchAddress("pnu", pnu, &b_pnu);
   fChain->SetBranchAddress("dirnu", dirnu, &b_dirnu);
   fChain->SetBranchAddress("flxg", flxg, &b_flxg);
   fChain->SetBranchAddress("flxh01", flxh01, &b_flxh01);
   fChain->SetBranchAddress("kflux", kflux, &b_kflux);
   fChain->SetBranchAddress("bs71", bs71, &b_bs71);
   fChain->SetBranchAddress("bs74", bs74, &b_bs74);
   fChain->SetBranchAddress("flxf", flxf, &b_flxf);
   fChain->SetBranchAddress("flxh1d", flxh1d, &b_flxh1d);
   fChain->SetBranchAddress("flxb03", flxb03, &b_flxb03);
   fChain->SetBranchAddress("flxf03", flxf03, &b_flxf03);
   fChain->SetBranchAddress("flxh06", flxh06, &b_flxh06);
   fChain->SetBranchAddress("flxh11", flxh11, &b_flxh11);
   fChain->SetBranchAddress("scan", scan, &b_scan);
   fChain->SetBranchAddress("nuceff_version", &nuceff_version, &b_nuceff_version);
   fChain->SetBranchAddress("charge_exchange", &charge_exchange, &b_charge_exchange);
   fChain->SetBranchAddress("absorbed", &absorbed, &b_absorbed);
   fChain->SetBranchAddress("multipi_gen", &multipi_gen, &b_multipi_gen);
   fChain->SetBranchAddress("scattering", &scattering, &b_scattering);
   fChain->SetBranchAddress("piless_dcy", &piless_dcy, &b_piless_dcy);
   fChain->SetBranchAddress("nscndprt", &nscndprt, &b_nscndprt);
   fChain->SetBranchAddress("itrkscnd", itrkscnd, &b_itrkscnd);
   fChain->SetBranchAddress("istakscnd", istakscnd, &b_istakscnd);
   fChain->SetBranchAddress("vtxscnd", vtxscnd, &b_vtxscnd);
   fChain->SetBranchAddress("pscnd", pscnd, &b_pscnd);
   fChain->SetBranchAddress("iprtscnd", iprtscnd, &b_iprtscnd);
   fChain->SetBranchAddress("tscnd", tscnd, &b_tscnd);
   fChain->SetBranchAddress("iprntprt", iprntprt, &b_iprntprt);
   fChain->SetBranchAddress("lmecscnd", lmecscnd, &b_lmecscnd);
   fChain->SetBranchAddress("iprnttrk", iprnttrk, &b_iprnttrk);
   fChain->SetBranchAddress("iorgprt", iorgprt, &b_iorgprt);
   fChain->SetBranchAddress("pprnt", pprnt, &b_pprnt);
   fChain->SetBranchAddress("iflgscnd", iflgscnd, &b_iflgscnd);
   fChain->SetBranchAddress("pprntinit", pprntinit, &b_pprntinit);
   fChain->SetBranchAddress("vtxprnt", vtxprnt, &b_vtxprnt);
   fChain->SetBranchAddress("iprntidx", iprntidx, &b_iprntidx);
   fChain->SetBranchAddress("nchilds", nchilds, &b_nchilds);
   fChain->SetBranchAddress("ichildidx", ichildidx, &b_ichildidx);
   fChain->SetBranchAddress("Npvcscnd", &Npvcscnd, &b_Npvcscnd);
   fChain->SetBranchAddress("Nchildsvc", Nchildsvc, &b_Nchildsvc);
   fChain->SetBranchAddress("Ichildidxvc", Ichildidxvc, &b_Ichildidxvc);
   fChain->SetBranchAddress("Neutmode", &Neutmode, &b_Neutmode);
   fChain->SetBranchAddress("Npne", &Npne, &b_Npne);
   fChain->SetBranchAddress("Ipne", Ipne, &b_Ipne);
   fChain->SetBranchAddress("Abspne", Abspne, &b_Abspne);
   fChain->SetBranchAddress("Pvecne", Pvecne, &b_Pvecne);
   fChain->SetBranchAddress("Npvc", &Npvc, &b_Npvc);
   fChain->SetBranchAddress("Ipvc", Ipvc, &b_Ipvc);
   fChain->SetBranchAddress("Ichvc", Ichvc, &b_Ichvc);
   fChain->SetBranchAddress("Iorgvc", Iorgvc, &b_Iorgvc);
   fChain->SetBranchAddress("Iflvc", Iflvc, &b_Iflvc);
   fChain->SetBranchAddress("Abspvc", Abspvc, &b_Abspvc);
   fChain->SetBranchAddress("Pvc", Pvc, &b_Pvc);
   fChain->SetBranchAddress("Crsx", &Crsx, &b_Crsx);
   fChain->SetBranchAddress("Crsy", &Crsy, &b_Crsy);
   fChain->SetBranchAddress("Crsz", &Crsz, &b_Crsz);
   fChain->SetBranchAddress("Crsphi", &Crsphi, &b_Crsphi);
   fChain->SetBranchAddress("Numbndn", &Numbndn, &b_Numbndn);
   fChain->SetBranchAddress("Numbndp", &Numbndp, &b_Numbndp);
   fChain->SetBranchAddress("Numfrep", &Numfrep, &b_Numfrep);
   fChain->SetBranchAddress("Numatom", &Numatom, &b_Numatom);
   fChain->SetBranchAddress("Ibound", &Ibound, &b_Ibound);
   fChain->SetBranchAddress("Neutinpmt", &Neutinpmt, &b_Neutinpmt);
   fChain->SetBranchAddress("Nvert", &Nvert, &b_Nvert);
   fChain->SetBranchAddress("Posvert", Posvert, &b_Posvert);
   fChain->SetBranchAddress("Iflgvert", Iflgvert, &b_Iflgvert);
   fChain->SetBranchAddress("Nvcvert", &Nvcvert, &b_Nvcvert);
   fChain->SetBranchAddress("Dirvert", Dirvert, &b_Dirvert);
   fChain->SetBranchAddress("Abspvert", Abspvert, &b_Abspvert);
   fChain->SetBranchAddress("Abstpvert", Abstpvert, &b_Abstpvert);
   fChain->SetBranchAddress("Ipvert", Ipvert, &b_Ipvert);
   fChain->SetBranchAddress("Iverti", Iverti, &b_Iverti);
   fChain->SetBranchAddress("Ivertf", Ivertf, &b_Ivertf);
   fChain->SetBranchAddress("Fsiprob", &Fsiprob, &b_Fsiprob);
   fChain->SetBranchAddress("Fsivarwt", Fsivarwt, &b_Fsivarwt);
   fChain->SetBranchAddress("Nvertsk", &Nvertsk, &b_Nvertsk);
   fChain->SetBranchAddress("Posvertsk", Posvertsk, &b_Posvertsk);
   fChain->SetBranchAddress("Iflgvertsk", Iflgvertsk, &b_Iflgvertsk);
   fChain->SetBranchAddress("Nvcvertsk", &Nvcvertsk, &b_Nvcvertsk);
   fChain->SetBranchAddress("Dirvertsk", Dirvertsk, &b_Dirvertsk);
   fChain->SetBranchAddress("Abspvertsk", Abspvertsk, &b_Abspvertsk);
   fChain->SetBranchAddress("Abstpvertsk", Abstpvertsk, &b_Abstpvertsk);
   fChain->SetBranchAddress("Ipvertsk", Ipvertsk, &b_Ipvertsk);
   fChain->SetBranchAddress("Ivertisk", Ivertisk, &b_Ivertisk);
   fChain->SetBranchAddress("Ivertfsk", Ivertfsk, &b_Ivertfsk);
   fChain->SetBranchAddress("Fsiprobsk", &Fsiprobsk, &b_Fsiprobsk);
   fChain->SetBranchAddress("trgoff", &trgoff, &b_trgoff);
   fChain->SetBranchAddress("fqntwnd", &fqntwnd, &b_fqntwnd);
   fChain->SetBranchAddress("fqtwnd_iclstr", fqtwnd_iclstr, &b_fqtwnd_iclstr);
   fChain->SetBranchAddress("fqtwnd_npeak", fqtwnd_npeak, &b_fqtwnd_npeak);
   fChain->SetBranchAddress("fqtwnd_prftt0", fqtwnd_prftt0, &b_fqtwnd_prftt0);
   fChain->SetBranchAddress("fqtwnd_prftpos", fqtwnd_prftpos, &b_fqtwnd_prftpos);
   fChain->SetBranchAddress("fqtwnd", fqtwnd, &b_fqtwnd);
   fChain->SetBranchAddress("fqtwnd_peakt0", fqtwnd_peakt0, &b_fqtwnd_peakt0);
   fChain->SetBranchAddress("fqtwnd_peakiness", fqtwnd_peakiness, &b_fqtwnd_peakiness);
   fChain->SetBranchAddress("fqnse", &fqnse, &b_fqnse);
   fChain->SetBranchAddress("fqitwnd", fqitwnd, &b_fqitwnd);
   fChain->SetBranchAddress("fqipeak", fqipeak, &b_fqipeak);
   fChain->SetBranchAddress("fqnhitpmt", fqnhitpmt, &b_fqnhitpmt);
   fChain->SetBranchAddress("fqtotq", fqtotq, &b_fqtotq);
   fChain->SetBranchAddress("fq0rtotmu", fq0rtotmu, &b_fq0rtotmu);
   fChain->SetBranchAddress("fq0rnll", fq0rnll, &b_fq0rnll);
   fChain->SetBranchAddress("fqn50", fqn50, &b_fqn50);
   fChain->SetBranchAddress("fqq50", fqq50, &b_fqq50);
   fChain->SetBranchAddress("fq1rpcflg", fq1rpcflg, &b_fq1rpcflg);
   fChain->SetBranchAddress("fq1rmom", fq1rmom, &b_fq1rmom);
   fChain->SetBranchAddress("fq1rt0", fq1rt0, &b_fq1rt0);
   fChain->SetBranchAddress("fq1rtotmu", fq1rtotmu, &b_fq1rtotmu);
   fChain->SetBranchAddress("fq1rnll", fq1rnll, &b_fq1rnll);
   fChain->SetBranchAddress("fq1rpos", fq1rpos, &b_fq1rpos);
   fChain->SetBranchAddress("fq1rdir", fq1rdir, &b_fq1rdir);
   fChain->SetBranchAddress("fq1rdconv", fq1rdconv, &b_fq1rdconv);
   fChain->SetBranchAddress("fq1reloss", fq1reloss, &b_fq1reloss);
   fChain->SetBranchAddress("fqpi0pcflg", fqpi0pcflg, &b_fqpi0pcflg);
   fChain->SetBranchAddress("fqpi0mom1", fqpi0mom1, &b_fqpi0mom1);
   fChain->SetBranchAddress("fqpi0mom2", fqpi0mom2, &b_fqpi0mom2);
   fChain->SetBranchAddress("fqpi0momtot", fqpi0momtot, &b_fqpi0momtot);
   fChain->SetBranchAddress("fqpi0dconv1", fqpi0dconv1, &b_fqpi0dconv1);
   fChain->SetBranchAddress("fqpi0dconv2", fqpi0dconv2, &b_fqpi0dconv2);
   fChain->SetBranchAddress("fqpi0t0", fqpi0t0, &b_fqpi0t0);
   fChain->SetBranchAddress("fqpi0totmu", fqpi0totmu, &b_fqpi0totmu);
   fChain->SetBranchAddress("fqpi0nll", fqpi0nll, &b_fqpi0nll);
   fChain->SetBranchAddress("fqpi0mass", fqpi0mass, &b_fqpi0mass);
   fChain->SetBranchAddress("fqpi0photangle", fqpi0photangle, &b_fqpi0photangle);
   fChain->SetBranchAddress("fqpi0pos", fqpi0pos, &b_fqpi0pos);
   fChain->SetBranchAddress("fqpi0dir1", fqpi0dir1, &b_fqpi0dir1);
   fChain->SetBranchAddress("fqpi0dir2", fqpi0dir2, &b_fqpi0dir2);
   fChain->SetBranchAddress("fqpi0dirtot", fqpi0dirtot, &b_fqpi0dirtot);
   fChain->SetBranchAddress("fqnmrfit", &fqnmrfit, &b_fqnmrfit);
   fChain->SetBranchAddress("fqmrifit", fqmrifit, &b_fqmrifit);
   fChain->SetBranchAddress("fqmrnring", fqmrnring, &b_fqmrnring);
   fChain->SetBranchAddress("fqmrpcflg", fqmrpcflg, &b_fqmrpcflg);
   fChain->SetBranchAddress("fqmrnll", fqmrnll, &b_fqmrnll);
   fChain->SetBranchAddress("fqmrtotmu", fqmrtotmu, &b_fqmrtotmu);
   fChain->SetBranchAddress("fqmrpid", fqmrpid, &b_fqmrpid);
   fChain->SetBranchAddress("fqmrmom", fqmrmom, &b_fqmrmom);
   fChain->SetBranchAddress("fqmrdconv", fqmrdconv, &b_fqmrdconv);
   fChain->SetBranchAddress("fqmreloss", fqmreloss, &b_fqmreloss);
   fChain->SetBranchAddress("fqmrt0", fqmrt0, &b_fqmrt0);
   fChain->SetBranchAddress("fqmrpos", fqmrpos, &b_fqmrpos);
   fChain->SetBranchAddress("fqmrdir", fqmrdir, &b_fqmrdir);
   fChain->SetBranchAddress("fqmsnfit", &fqmsnfit, &b_fqmsnfit);
   fChain->SetBranchAddress("fqmspcflg", fqmspcflg, &b_fqmspcflg);
   fChain->SetBranchAddress("fqmsnseg", fqmsnseg, &b_fqmsnseg);
   fChain->SetBranchAddress("fqmspid", fqmspid, &b_fqmspid);
   fChain->SetBranchAddress("fqmsifit", fqmsifit, &b_fqmsifit);
   fChain->SetBranchAddress("fqmsimer", fqmsimer, &b_fqmsimer);
   fChain->SetBranchAddress("fqmstotmu", fqmstotmu, &b_fqmstotmu);
   fChain->SetBranchAddress("fqmsnll", fqmsnll, &b_fqmsnll);
   fChain->SetBranchAddress("fqmsmom", fqmsmom, &b_fqmsmom);
   fChain->SetBranchAddress("fqmseloss", fqmseloss, &b_fqmseloss);
   fChain->SetBranchAddress("fqmst0", fqmst0, &b_fqmst0);
   fChain->SetBranchAddress("fqmspos", fqmspos, &b_fqmspos);
   fChain->SetBranchAddress("fqmsdir", fqmsdir, &b_fqmsdir);
   fChain->SetBranchAddress("prid_ang", &prid_ang, &b_prid_ang);
   fChain->SetBranchAddress("prid_len", &prid_len, &b_prid_len);
   fChain->SetBranchAddress("prid_pmom", &prid_pmom, &b_prid_pmom);
   fChain->SetBranchAddress("prid_mang", &prid_mang, &b_prid_mang);
   fChain->SetBranchAddress("prid_plike", &prid_plike, &b_prid_plike);
   fChain->SetBranchAddress("prid_mlike", &prid_mlike, &b_prid_mlike);
   fChain->SetBranchAddress("prid_nused", &prid_nused, &b_prid_nused);
   fChain->SetBranchAddress("dirtotepi", dirtotepi, &b_dirtotepi);
   fChain->SetBranchAddress("dirtotenpi", dirtotenpi, &b_dirtotenpi);
   fChain->SetBranchAddress("dirtotmue", dirtotmue, &b_dirtotmue);
   fChain->SetBranchAddress("dirsum", dirsum, &b_dirsum);
   fChain->SetBranchAddress("etot", &etot, &b_etot);
   fChain->SetBranchAddress("etotepi", &etotepi, &b_etotepi);
   fChain->SetBranchAddress("etotenpi", &etotenpi, &b_etotenpi);
   fChain->SetBranchAddress("etotmue", &etotmue, &b_etotmue);
   fChain->SetBranchAddress("oscweight", oscweight, &b_oscweight);
   fChain->SetBranchAddress("oscwgt", &oscwgt, &b_oscwgt);
   fChain->SetBranchAddress("live", &live, &b_live);
   fChain->SetBranchAddress("sacth", &sacth, &b_sacth);
   fChain->SetBranchAddress("sactg", &sactg, &b_sactg);
   fChain->SetBranchAddress("sacth1d", &sacth1d, &b_sacth1d);
   fChain->SetBranchAddress("ccqelike", &ccqelike, &b_ccqelike);
   fChain->SetBranchAddress("mulike", &mulike, &b_mulike);
   fChain->SetBranchAddress("mproton", &mproton, &b_mproton);
   fChain->SetBranchAddress("outdir", outdir, &b_outdir);
   fChain->SetBranchAddress("nused2", &nused2, &b_nused2);
   fChain->SetBranchAddress("vsum", &vsum, &b_vsum);
   fChain->SetBranchAddress("qsep", &qsep, &b_qsep);
   fChain->SetBranchAddress("qpeak", &qpeak, &b_qpeak);
   fChain->SetBranchAddress("qhigh", &qhigh, &b_qhigh);
   fChain->SetBranchAddress("qlow", &qlow, &b_qlow);
   fChain->SetBranchAddress("nzeros2", &nzeros2, &b_nzeros2);
   fChain->SetBranchAddress("moyenne2", &moyenne2, &b_moyenne2);
   fChain->SetBranchAddress("lproton", &lproton, &b_lproton);
   fChain->SetBranchAddress("qwin", &qwin, &b_qwin);
   fChain->SetBranchAddress("ent_pos", ent_pos, &b_ent_pos);
   fChain->SetBranchAddress("ent_dir", ent_dir, &b_ent_dir);
   fChain->SetBranchAddress("length", &length, &b_length);
   fChain->SetBranchAddress("tr_mom1", &tr_mom1, &b_tr_mom1);
   fChain->SetBranchAddress("A_ent_mom", &A_ent_mom, &b_A_ent_mom);
   fChain->SetBranchAddress("A_ent_pos", A_ent_pos, &b_A_ent_pos);
   fChain->SetBranchAddress("A_ent_dir", A_ent_dir, &b_A_ent_dir);
   fChain->SetBranchAddress("A_ext_mom", &A_ext_mom, &b_A_ext_mom);
   fChain->SetBranchAddress("A_ext_pos", A_ext_pos, &b_A_ext_pos);
   fChain->SetBranchAddress("A_ext_dir", A_ext_dir, &b_A_ext_dir);
   fChain->SetBranchAddress("Fit_pos", Fit_pos, &b_Fit_pos);
   fChain->SetBranchAddress("Fit_dir", Fit_dir, &b_Fit_dir);
   fChain->SetBranchAddress("Fit_len", &Fit_len, &b_Fit_len);
   fChain->SetBranchAddress("Fit_mom", &Fit_mom, &b_Fit_mom);
   fChain->SetBranchAddress("Fit_pid", &Fit_pid, &b_Fit_pid);
   fChain->SetBranchAddress("Um_ehit8m", &Um_ehit8m, &b_Um_ehit8m);
   fChain->SetBranchAddress("Um_ohit8m", &Um_ohit8m, &b_Um_ohit8m);
   fChain->SetBranchAddress("Um_qent", &Um_qent, &b_Um_qent);
   fChain->SetBranchAddress("Sh_chi1p", &Sh_chi1p, &b_Sh_chi1p);
   fChain->SetBranchAddress("Sh_delta", &Sh_delta, &b_Sh_delta);
   fChain->SetBranchAddress("Sh_mean", &Sh_mean, &b_Sh_mean);
   fChain->SetBranchAddress("Sh_meanq", &Sh_meanq, &b_Sh_meanq);
   fChain->SetBranchAddress("Sh_id", &Sh_id, &b_Sh_id);
   fChain->SetBranchAddress("Tr_stop", Tr_stop, &b_Tr_stop);
   fChain->SetBranchAddress("Tr_mom", &Tr_mom, &b_Tr_mom);
   fChain->SetBranchAddress("Tr_len", &Tr_len, &b_Tr_len);
   fChain->SetBranchAddress("Tr_len1", &Tr_len1, &b_Tr_len1);
   fChain->SetBranchAddress("Pid_flg", &Pid_flg, &b_Pid_flg);
   fChain->SetBranchAddress("Crs1", &Crs1, &b_Crs1);
   fChain->SetBranchAddress("Crs2", &Crs2, &b_Crs2);
   fChain->SetBranchAddress("iclass", &iclass, &b_iclass);
   fChain->SetBranchAddress("mu_class", &mu_class, &b_mu_class);
   fChain->SetBranchAddress("mu_dec", &mu_dec, &b_mu_dec);
   fChain->SetBranchAddress("mu_dir", mu_dir, &b_mu_dir);
   fChain->SetBranchAddress("mu_pos", mu_pos, &b_mu_pos);
   fChain->SetBranchAddress("mu_good", &mu_good, &b_mu_good);
   fChain->SetBranchAddress("history", &history, &b_history);
   fChain->SetBranchAddress("Pdst", &Pdst, &b_Pdst);
   fChain->SetBranchAddress("idoff", &idoff, &b_idoff);
   fChain->SetBranchAddress("anthit", &anthit, &b_anthit);
   fChain->SetBranchAddress("idseq", &idseq, &b_idseq);
   fChain->SetBranchAddress("tstfrac", &tstfrac, &b_tstfrac);
   fChain->SetBranchAddress("judge", &judge, &b_judge);
   fChain->SetBranchAddress("Upcrs1", &Upcrs1, &b_Upcrs1);
   fChain->SetBranchAddress("Upcrs2", &Upcrs2, &b_Upcrs2);
   fChain->SetBranchAddress("lst", &lst, &b_lst);
   fChain->SetBranchAddress("jd", &jd, &b_jd);
   fChain->SetBranchAddress("fjd", &fjd, &b_fjd);
   fChain->SetBranchAddress("alt", &alt, &b_alt);
   fChain->SetBranchAddress("azi", &azi, &b_azi);
   fChain->SetBranchAddress("ra", &ra, &b_ra);
   fChain->SetBranchAddress("dec", &dec, &b_dec);
   fChain->SetBranchAddress("glat", &glat, &b_glat);
   fChain->SetBranchAddress("glong", &glong, &b_glong);
   std::cout<<"in Int(), point 3"<<std::endl;
   Notify();

}

Bool_t THEIA::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void THEIA::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}

Int_t THEIA::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}


Double_t THEIA::GetToWall(double *pos, double *dir){
// Cylindrical detector like SK
    
    double towall = 0;

    double tmp=(pos[0]*dir[0]+pos[1]*dir[1])*(pos[0]*dir[0]+pos[1]*dir[1]) + (dir[0]*dir[0]+dir[1]*dir[1])*(1690*1690-pos[0]*pos[0]-pos[1]*pos[1]);
    
    if (tmp>0.) {// solution exists
      towall=(-(pos[0]*dir[0]+pos[1]*dir[1])+TMath::Sqrt(tmp))/(dir[0]*dir[0]+dir[1]*dir[1]);
      
      if ((pos[2]+towall*dir[2])>1810) {//penetrates top wall!
        towall=(1810-pos[2])/dir[2];
      }
      else if ((pos[2]+towall*dir[2])<-1810) {//penetrates bottom wall!
        towall=(-1810-pos[2])/dir[2];
      }
    }
}

void THEIA::InfoNeutron(Int_t NofEvent){

   for(Int_t i=0;i<10;i++) neutron2d[i] = new TH2D(Form("h2d_%d",i),Form("h2d_%d",i),100,0,100,10,0,10);

   Long64_t nbytes = 0, nb = 0;
   if(NofEvent > fChain->GetEntriesFast()) NofEvent = fChain->GetEntriesFast();

   for (Long64_t jentry=0; jentry<NofEvent;jentry++) {
      Long64_t ientry = this->LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if (jentry % 100000 == 0) {std::cout << jentry << " events processed" << std::endl;}

      double tdist[1000]={};
      int nCapture = 0;
      if(abs(mode) >= 1 && abs(mode) <= 2){
	nCapture = 0;
   	for(int i=0; i<nscndprt; i++){
   	  if( lmecscnd[i]==18 && /* Neutron capture */
       	  iprtscnd[i]==22 /* PDG code for gamma */
     	  )
    	  {
      	    for(int innerloop =0 ; innerloop<10; innerloop++) tdist[innerloop]=0.0;
            for(int j=0; j<3; j++)
            {
              tdist[nCapture]+=(posv[j] - vtxscnd[i][j])*(posv[j] - vtxscnd[i][j]);
	      //std::cout<<vtxscnd[i][j]<<" "<<posv[j]<<" "<<(posv[j] - vtxscnd[i][j])*(posv[j] - vtxscnd[i][j])<<std::endl;
            }
	    nCapture ++;
	    //std::cout<<"one neutron at "<<nCapture<<" with distance of "<<tdist[nCapture-1]<<" "<<std::endl;
    	  }
  	}
	for(int innerl =0 ; innerl <nCapture; innerl ++) neutron2d[0]->Fill(TMath::Sqrt( tdist[innerl]), nCapture );
      }

      else if(abs(mode) == 11 || abs(mode) == 13 || abs(mode) == 16){
        nCapture = 0;
        for(int i=0; i<nscndprt; i++){
          if( lmecscnd[i]==18 && /* Neutron capture */
          iprtscnd[i]==22 /* PDG code for gamma */
          )
          {
            for(int innerloop =0 ; innerloop<10; innerloop++) tdist[innerloop]=0.0;
            for(int j=0; j<3; j++)
            {
              tdist[nCapture]+=(posv[j] - vtxscnd[i][j])*(posv[j] - vtxscnd[i][j]);
              //std::cout<<vtxscnd[i][j]<<" "<<posv[j]<<" "<<(posv[j] - vtxscnd[i][j])*(posv[j] - vtxscnd[i][j])<<std::endl;
            }
            nCapture ++;
            //std::cout<<"one neutron at "<<nCapture<<" with distance of "<<tdist[nCapture-1]<<" "<<std::endl;
          }
        }
        for(int innerl =0 ; innerl <nCapture; innerl ++) neutron2d[1]->Fill(TMath::Sqrt( tdist[innerl]), nCapture );
      }

      else if(abs(mode) > 16 && abs(mode) < 30){
        nCapture = 0;
        for(int i=0; i<nscndprt; i++){
          if( lmecscnd[i]==18 && /* Neutron capture */
          iprtscnd[i]==22 /* PDG code for gamma */
          )
          {
            for(int innerloop =0 ; innerloop<10; innerloop++) tdist[innerloop]=0.0;
            for(int j=0; j<3; j++)
            {
              tdist[nCapture]+=(posv[j] - vtxscnd[i][j])*(posv[j] - vtxscnd[i][j]);
              //std::cout<<vtxscnd[i][j]<<" "<<posv[j]<<" "<<(posv[j] - vtxscnd[i][j])*(posv[j] - vtxscnd[i][j])<<std::endl;
            }
            nCapture ++;
            //std::cout<<"one neutron at "<<nCapture<<" with distance of "<<tdist[nCapture-1]<<" "<<std::endl;
          }
        }
        for(int innerl =0 ; innerl <nCapture; innerl ++) neutron2d[2]->Fill(TMath::Sqrt( tdist[innerl]), nCapture );
      }

      else if(abs(mode) > 30){
        nCapture = 0;
        for(int i=0; i<nscndprt; i++){
          if( lmecscnd[i]==18 && /* Neutron capture */
          iprtscnd[i]==22 /* PDG code for gamma */
          )
          {
            for(int innerloop =0 ; innerloop<10; innerloop++) tdist[innerloop]=0.0;
            for(int j=0; j<3; j++)
            {
              tdist[nCapture]+=(posv[j] - vtxscnd[i][j])*(posv[j] - vtxscnd[i][j]);
              //std::cout<<vtxscnd[i][j]<<" "<<posv[j]<<" "<<(posv[j] - vtxscnd[i][j])*(posv[j] - vtxscnd[i][j])<<std::endl;
            }
            nCapture ++;
            //std::cout<<"one neutron at "<<nCapture<<" with distance of "<<tdist[nCapture-1]<<" "<<std::endl;
          }
        }
        for(int innerl =0 ; innerl <nCapture; innerl ++) neutron2d[3]->Fill(TMath::Sqrt( tdist[innerl]), nCapture );
      }


    }

    std::cout <<  "returning" << std::endl; 
}


int main(int argc, char* argv[])
{
   gSystem->Load("libTree");

   TChain tree("h1");
   tree.Add("input/mar16sk4.reduc.fQv5r0.root");

   std::cout<<"preparing.."<<std::endl;
   THEIA* sLoop = new THEIA(&tree);

   Long64_t nentries = tree.GetEntries();

   std::cout<<"ready to loop"<<std::endl;

   Int_t NofEvent = nentries;
   sLoop->InfoNeutron(NofEvent);
   std::cout <<  "ccqe done" << std::endl;

   std::cout<<"neutron info extracted "<<std::endl;
    
   TCanvas* c1 = new TCanvas();
   c1->Divide(2,2);
   c1->cd(1);
   sLoop->neutron2d[0]->GetXaxis()->SetTitle("neutron travel [cm]");
   sLoop->neutron2d[0]->GetYaxis()->SetTitle("neutron multiplicity");
   sLoop->neutron2d[0]->Draw("colz");
    
   c1->cd(2);
   sLoop->neutron2d[1]->GetXaxis()->SetTitle("neutron travel [cm]");
   sLoop->neutron2d[1]->GetYaxis()->SetTitle("neutron multiplicity");
   sLoop->neutron2d[1]->Draw("colz");
   c1->cd(3);
   sLoop->neutron2d[2]->GetXaxis()->SetTitle("neutron travel [cm]");
   sLoop->neutron2d[2]->GetYaxis()->SetTitle("neutron multiplicity");   
   sLoop->neutron2d[2]->Draw("colz");
   c1->cd(4);
   sLoop->neutron2d[3]->GetXaxis()->SetTitle("neutron travel [cm]");
   sLoop->neutron2d[3]->GetYaxis()->SetTitle("neutron multiplicity");
   sLoop->neutron2d[3]->Draw("colz");

   c1->SaveAs("neutron2d.C");
   
}


