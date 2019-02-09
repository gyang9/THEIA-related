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

TSpline5** THEIA::LoadDuneFlux(TString duneFlux)
{
   TFile* f1 = new TFile(duneFlux);

   nue       = (TH1D*)f1->Get("nue_flux");     
   nuebar    = (TH1D*)f1->Get("nuebar_flux");
   numu      = (TH1D*)f1->Get("numu_flux");
   numubar   = (TH1D*)f1->Get("numubar_flux");
   nueOsc    = (TH1D*)f1->Get("nue_fluxosc");
   nuebarOsc = (TH1D*)f1->Get("nuebar_fluxosc");
   numuOsc   = (TH1D*)f1->Get("numu_fluxosc");
   numubarOsc= (TH1D*)f1->Get("numubar_fluxosc");

   TH1D* EvCCnue       = (TH1D*)f1->Get("nue_cceventrate");
   TH1D* EvCCnuebar    = (TH1D*)f1->Get("nuebar_cceventrate");
   TH1D* EvCCnumu      = (TH1D*)f1->Get("numu_cceventrate");
   TH1D* EvCCnumubar   = (TH1D*)f1->Get("numubar_cceventrate");
   TH1D* EvCCnutau     = (TH1D*)f1->Get("nue_cceventrate");
   TH1D* EvCCnutaubar  = (TH1D*)f1->Get("nuebar_cceventrate");
   TH1D* EvNCnue       = (TH1D*)f1->Get("nue_cceventrate");
   TH1D* EvNCnuebar    = (TH1D*)f1->Get("nuebar_cceventrate");
   TH1D* EvNCnumu      = (TH1D*)f1->Get("numu_cceventrate");
   TH1D* EvNCnumubar   = (TH1D*)f1->Get("numubar_cceventrate");
   TH1D* EvNCnutau     = (TH1D*)f1->Get("nue_cceventrate");
   TH1D* EvNCnutaubar  = (TH1D*)f1->Get("nuebar_cceventrate");

   std::cout<<"now recording event rates: "<<std::endl;
   std::cout<<"CC nue "<< EvCCnue->Integral()<<std::endl;
   std::cout<<"CC nuebar "<< EvCCnuebar->Integral()<<std::endl;
   std::cout<<"CC numu "<< EvCCnumu->Integral()<<std::endl;
   std::cout<<"CC numubar "<< EvCCnumubar->Integral()<<std::endl;
   std::cout<<"CC nutau "<< EvCCnutau->Integral()<<std::endl;
   std::cout<<"CC nutaubar "<< EvCCnutaubar->Integral()<<std::endl;

   std::cout<<"NC nue "<< EvNCnue->Integral()<<std::endl;
   std::cout<<"NC nuebar "<< EvNCnuebar->Integral()<<std::endl;
   std::cout<<"NC numu "<< EvNCnumu->Integral()<<std::endl;
   std::cout<<"NC numubar "<< EvNCnumubar->Integral()<<std::endl;
   std::cout<<"NC nutau "<< EvNCnutau->Integral()<<std::endl;
   std::cout<<"NC nutaubar "<< EvNCnutaubar->Integral()<<std::endl;

/*
   //normalize to 1
   nue         ->Scale(1./nue->Integral());
   nuebar      ->Scale(1./nuebar->Integral());
   numu        ->Scale(1./numu->Integral());
   numubar     ->Scale(1./numubar->Integral());
   nueOsc      ->Scale(1./nueOsc->Integral());
   nuebarOsc   ->Scale(1./nuebarOsc->Integral());
   numuOsc     ->Scale(1./numuOsc->Integral());
   numubarOsc  ->Scale(1./numubarOsc->Integral());
*/

   TH1D * hists[] = {nue, nuebar, numu, numubar, nueOsc, nuebarOsc, numuOsc, numubarOsc};

   // Divide by bin width first!
   for (int iHist = 0; iHist < 8; iHist++) {
     std::cout<<"the integral for "<<iHist<<" "<<hists[iHist]->Integral()<<std::endl;
     for (int iBin = 1; iBin <= hists[iHist]->GetNbinsX(); iBin++)
       hists[iHist]->SetBinContent(iBin, hists[iHist]->GetBinContent(iBin)/hists[iHist]->GetBinWidth(iBin));
       //std::cout<<"the integral for "<<iHist<<" "<<hists[iHist]->Integral()<<std::endl;
       //hists[iHist]->Scale(1./hists[iHist]->Integral()); // Why normalizing each component independently?!
   }

/*
   TSpline5* duneNue       = new TSpline5( nue);
   TSpline5* duneNuebar    = new TSpline5( nuebar);
   TSpline5* duneNumu      = new TSpline5( numu);
   TSpline5* duneNumubar   = new TSpline5( numubar);
   TSpline5* duneNueOsc    = new TSpline5( nueOsc);
   TSpline5* duneNuebarOsc = new TSpline5( nuebarOsc);
   TSpline5* duneNumuOsc   = new TSpline5( numuOsc);
   TSpline5* duneNumubarOsc= new TSpline5( numubarOsc);
*/

   TSpline5* duneNue       = new TSpline5( hists[0]);
   TSpline5* duneNuebar    = new TSpline5( hists[1]);
   TSpline5* duneNumu      = new TSpline5( hists[2]);
   TSpline5* duneNumubar   = new TSpline5( hists[3]);
   TSpline5* duneNueOsc    = new TSpline5( hists[4]);
   TSpline5* duneNuebarOsc = new TSpline5( hists[5]);
   TSpline5* duneNumuOsc   = new TSpline5( hists[6]);
   TSpline5* duneNumubarOsc= new TSpline5( hists[7]);

   //std::cout<<"dune flux integral tests: "<<duneNue->Integral()<<" "<<duneNuebar->Integral()<<" "<<duneNumu->Integral()<<" "<<duneNumubar->Integral()<<" "<<duneNueOsc->Integral()<<" "<<duneNuebarOsc->Integral()<<" "<<duneNumuOsc->Integral()<<" "<<duneNumubarOsc->Integral()<<std::endl;

   reTot2[0] = duneNue;
   reTot2[1] = duneNuebar;
   reTot2[2] = duneNumu;
   reTot2[3] = duneNumubar;
   reTot2[4] = duneNueOsc;
   reTot2[5] = duneNuebarOsc;
   reTot2[6] = duneNumuOsc;
   reTot2[7] = duneNumubarOsc;

   return reTot2;

}


TSpline5** THEIA::LoadAtmFlux(TString atmFlux)
{
/*
   int counter = 0;
   std::ifstream in;
   in.open(atmFlux);
   std::cout<<"fluxes from Honda: energy, nue, nuebar, numu, numubar  ***|*** "<<std::endl;
   while (1){
        if (!in.good()) break;
        in>>xx[counter]>>nueIn[counter]>>nuebarIn[counter]>>numuIn[counter]>>numubarIn[counter];
        std::cout<<xx[counter]<<" "<<nueIn[counter]<<" "<<nuebarIn[counter]<<" "<<numuIn[counter]<<" "<<numubarIn[counter]<<std::endl;
        totNumber[0] = totNumber[0] + nueIn[counter];
        totNumber[1] = totNumber[1] + nuebarIn[counter];
        totNumber[2] = totNumber[2] + numuIn[counter];
        totNumber[3] = totNumber[3] + numubarIn[counter];
   counter++;
   }

   std::cout<<"summation of atm fluxes "<<totNumber[0]<<" "<<totNumber[1]<<" "<<totNumber[2]<<" "<<totNumber[3]<<std::endl;

   for(Int_t i=0;i<counter;i++){
	nueIn[counter]    = nueIn[counter]/totNumber[0];
        nuebarIn[counter] = nuebarIn[counter]/totNumber[1];
        numuIn[counter]   = numuIn[counter]/totNumber[2];
        numubarIn[counter]= numubarIn[counter]/totNumber[3];
   }

   TSpline5* atmNue    = new TSpline5("atmNue", xx, nueIn, counter);
   TSpline5* atmNuebar = new TSpline5("atmNuebar", xx, nuebarIn, counter);
   TSpline5* atmNumu   = new TSpline5("atmNumu", xx, numuIn, counter);
   TSpline5* atmNumubar= new TSpline5("atmNumubar", xx, numubarIn, counter);
*/

   // Use TGraphs to read file directly, much easier
   TGraph * gAtmNumu     = new TGraph(atmFlux, "%lg %lg" , "");
   TGraph * gAtmNumubar  = new TGraph(atmFlux, "%lg %*lg %lg", "");
   TGraph * gAtmNue    = new TGraph(atmFlux, "%lg %*lg %*lg %lg", "");
   TGraph * gAtmNuebar = new TGraph(atmFlux, "%lg %*lg %*lg %*lg %lg", "");
/*
   //double inteNue=0; double inteNuebar=0; double intNumu=0; double inteNumubar=0;
   double inteNue = gAtmNue->Integral();
   //for (int iGra=0;iGra<gAtmNue->GetN();iGra++) inteNue += gAtmNue->GetY()[iGra]; 
   for (int iGra=0;iGra<gAtmNue->GetN();iGra++) gAtmNue->GetY()[iGra] /= inteNue;
   double inteNuebar = gAtmNuebar->Integral();
   //for (int iGra=0;iGra<gAtmNuebar->GetN();iGra++) inteNuebar += gAtmNuebar->GetY()[iGra];
   for (int iGra=0;iGra<gAtmNuebar->GetN();iGra++) gAtmNuebar->GetY()[iGra] /= inteNuebar;
   double inteNumu = gAtmNumu->Integral();
   //for (int iGra=0;iGra<gAtmNumu->GetN();iGra++) inteNumu += gAtmNumu->GetY()[iGra];
   for (int iGra=0;iGra<gAtmNumu->GetN();iGra++) gAtmNumu->GetY()[iGra] /= inteNumu;
   double inteNumubar = gAtmNumubar->Integral();
   //for (int iGra=0;iGra<gAtmNumubar->GetN();iGra++) inteNumubar += gAtmNumubar->GetY()[iGra];
   for (int iGra=0;iGra<gAtmNumubar->GetN();iGra++) gAtmNumubar->GetY()[iGra] /= inteNumubar;
*/
   TSpline5* atmNue    = new TSpline5("atmNue", gAtmNue);
   TSpline5* atmNuebar = new TSpline5("atmNuebar", gAtmNuebar);
   TSpline5* atmNumu   = new TSpline5("atmNumu", gAtmNumu);
   TSpline5* atmNumubar= new TSpline5("atmNumubar", gAtmNumubar);

   //std::cout<<"atm flux integral tests: "<<atmNue->Integral()<<" "<<atmNuebar->Integral()<<" "<<atmNumu->Integral()<<" "<<atmNumubar->Integral()<<std::endl;

   reTot[0] = atmNue;
   reTot[1] = atmNuebar;
   reTot[2] = atmNumu;
   reTot[3] = atmNumubar;

   return reTot;
}

void THEIA::prepareOutput(TString outName){

   //output file with flux weights added
   ff = TFile::Open(outName,"RECREATE");
   tt = fChain->CloneTree(0);
   tt->Branch("fluxWeight",&fluxWeight,"fluxWeight[2]/D");
   tt->Branch("sigCategory",&sigCategory,"sigCategory/I");
   tt->Branch("bkgCategory",&bkgCategory,"bkgCategory/I");
   tt->Branch("fqwall",&fqwall,"fqwall/D");
   tt->Branch("towall",&towall,"towall/D");
   tt->Branch("angleepi",&angleepi,"angleepi/D");
   tt->Branch("anglepie",&anglepie,"anglepie/D");
   tt->Branch("angleee",&angleee,"angleee/D");
   tt->Branch("anglepp",&anglepp,"anglepp/D");
   tt->Branch("angleeee",&angleeee,"angleeee[3]/D");
   tt->Branch("angleppp",&angleppp,"angleppp[3]/D");
   tt->Branch("angleepp",&angleepp,"angleepp[3]/D");
   tt->Branch("anglepep",&anglepep,"anglepep[3]/D");
   tt->Branch("angleppe",&angleppe,"angleppe[3]/D");
   tt->Branch("angleeep",&angleeep,"angleeep[3]/D");
   tt->Branch("angleepe",&angleepe,"angleepe[3]/D");
   tt->Branch("anglepee",&anglepee,"anglepee[3]/D");
   tt->Branch("momee",&momee,"momee[2]/D");
   tt->Branch("momepi",&momepi,"momepi[2]/D");
   tt->Branch("mompie",&mompie,"mompie[2]/D");
   tt->Branch("mompp",&mompp,"mompp[2]/D");
   tt->Branch("momeee",&momeee,"momeee[3]/D");
   tt->Branch("momppp",&momppp,"momppp[3]/D");
   tt->Branch("momeep",&momeep,"momeep[3]/D");
   tt->Branch("momepe",&momepe,"momepe[3]/D");
   tt->Branch("mompee",&mompee,"mompee[3]/D");
   tt->Branch("momepp",&momepp,"momepp[3]/D");
   tt->Branch("mompep",&mompep,"mompep[3]/D");
   tt->Branch("momppe",&momppe,"momppe[3]/D");

   tt->Branch("fq1rE",&fq1rE,"fq1rE/D");
   tt->Branch("fq2rPE",&fq2rPE,"fq2rPE/D");
   tt->Branch("fq2rEE",&fq2rEE,"fq2rEE/D");
   tt->Branch("fq2rPP",&fq2rPP,"fq2rPP/D");
   tt->Branch("fq2rEP",&fq2rEP,"fq2rEP/D");
   tt->Branch("fq3rEEP",&fq3rEEP,"fq3rEEP/D");
   tt->Branch("fq3rEPE",&fq3rEPE,"fq3rEPE/D");
   tt->Branch("fq3rPEE",&fq3rPEE,"fq3rPEE/D");
   tt->Branch("fq3rPPP",&fq3rPPP,"fq3rPPP/D");
   tt->Branch("fq3rEEE",&fq3rEEE,"fq3rEEE/D");
   tt->Branch("fq3rEPP",&fq3rEPP,"fq3rEPP/D");
   tt->Branch("fq3rPEP",&fq3rPEP,"fq3rPEP/D");
   tt->Branch("fq3rPPE",&fq3rPPE,"fq3rPPE/D");
   tt->Branch("erec1r",&erec1r,"erec1r/D");
   tt->Branch("erecmr",&erecmr,"erecmr/D");
   tt->Branch("eTOpre",&eTOpre,"eTOpre/D");

   tt->Branch("tdist",&tdist,"tdist/D");
   tt->Branch("nCaptureEff",&nCaptureEff,"nCaptureEff/D");
   tt->Branch("nCapture",&nCapture,"nCapture/I");
}


TTree* THEIA:: LoopAndWrite(Int_t NofEvent){

   Long64_t nbytes = 0, nb = 0;
   if(NofEvent > fChain->GetEntriesFast()) NofEvent = fChain->GetEntriesFast();

   for (Long64_t jentry=0; jentry<NofEvent;jentry++) {
      Long64_t ientry = this->LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if (jentry % 100000 == 0) {std::cout << jentry << " events processed" << std::endl;}

      //std::cout<<"neutrino ip and energy : "<<ipnu[0]<<" "<<pnu[0]<<std::endl;

      if(ipnu[0] == 12){
        fluxWeight[0] = (reTot2[0]->Eval(pnu[0])*1.47e21*3.5)/ (500.00*365.*24.*3600.*4.*TMath::Pi()*reTot[0]->Eval(pnu[0]));
        fluxWeight[1] = (reTot2[4]->Eval(pnu[0])*1.47e21*3.5)/ (500.00*365.*24.*3600.*4.*TMath::Pi()*reTot[0]->Eval(pnu[0]));
      }
      if(ipnu[0] == -12){
        fluxWeight[0] = (reTot2[1]->Eval(pnu[0])*1.47e21*3.5)/ (500.00*365.*24.*3600.*4.*TMath::Pi()*reTot[1]->Eval(pnu[0]));
        fluxWeight[1] = (reTot2[5]->Eval(pnu[0])*1.47e21*3.5)/ (500.00*365.*24.*3600.*4.*TMath::Pi()*reTot[1]->Eval(pnu[0]));
      }
      if(ipnu[0] == 14){
        fluxWeight[0] = (reTot2[2]->Eval(pnu[0])*1.47e21*3.5)/ (500.00*365.*24.*3600.*4.*TMath::Pi()*reTot[2]->Eval(pnu[0]));
        fluxWeight[1] = (reTot2[6]->Eval(pnu[0])*1.47e21*3.5)/ (500.00*365.*24.*3600.*4.*TMath::Pi()*reTot[2]->Eval(pnu[0]));
      }
      if(ipnu[0] == -14){
        fluxWeight[0] = (reTot2[3]->Eval(pnu[0])*1.47e21*3.5)/ (500.00*365.*24.*3600.*4.*TMath::Pi()*reTot[3]->Eval(pnu[0]));
        fluxWeight[1] = (reTot2[7]->Eval(pnu[0])*1.47e21*3.5)/ (500.00*365.*24.*3600.*4.*TMath::Pi()*reTot[3]->Eval(pnu[0]));
      }

      if(TMath::Abs(mode) > 30) { fluxWeight[1] = fluxWeight[0]; }
        //if(fluxWeight[0]>0.1) {fluxWeight[0] = 10e-22;}
        //if(fluxWeight[1]>0.1) {fluxWeight[1] = 10e-22;}

        tt->Fill();
   }

   tt->Write();
   ff->Write();

   return tt;

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


//neutron efficiency spline generated here
void THEIA:: LoadNeutronEfficiency(TString neutronEffFile){

   TGraph * gNeutronSpline     = new TGraph(neutronEffFile, "%lg %lg" , "");
   TSpline5* neutronSpline    = new TSpline5("neutronSpline", gNeutronSpline);
}


// 88 variables aimed at 
void THEIA:: LoopAndWrite(Int_t NofEvent, Bool_t SigBkgTagger){

   Long64_t nbytes = 0, nb = 0;
   if(NofEvent > fChain->GetEntriesFast()) NofEvent = fChain->GetEntriesFast();

   for (Long64_t jentry=0; jentry<NofEvent;jentry++) {
      Long64_t ientry = this->LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if (jentry % 100000 == 0) {std::cout << jentry << " events processed" << std::endl;}

      if(ipnu[0] == 12){
        fluxWeight[0] = (reTot2[0]->Eval(pnu[0])*1.47e21*3.5)/ (500.*365.*24.*3600.*4.*TMath::Pi()*reTot[0]->Eval(pnu[0]));
        fluxWeight[1] = (reTot2[4]->Eval(pnu[0])*1.47e21*3.5)/ (500.*365.*24.*3600.*4.*TMath::Pi()*reTot[0]->Eval(pnu[0]));
      }
      if(ipnu[0] == -12){
        fluxWeight[0] = (reTot2[1]->Eval(pnu[0])*1.47e21*3.5)/ (500.*365.*24.*3600.*4.*TMath::Pi()*reTot[1]->Eval(pnu[0]));
        fluxWeight[1] = (reTot2[5]->Eval(pnu[0])*1.47e21*3.5)/ (500.*365.*24.*3600.*4.*TMath::Pi()*reTot[1]->Eval(pnu[0]));
      }
      if(ipnu[0] == 14){
        fluxWeight[0] = (reTot2[2]->Eval(pnu[0])*1.47e21*3.5)/ (500.*365.*24.*3600.*4.*TMath::Pi()*reTot[2]->Eval(pnu[0]));
        fluxWeight[1] = (reTot2[6]->Eval(pnu[0])*1.47e21*3.5)/ (500.*365.*24.*3600.*4.*TMath::Pi()*reTot[2]->Eval(pnu[0]));
      }
      if(ipnu[0] == -14){
        fluxWeight[0] = (reTot2[3]->Eval(pnu[0])*1.47e21*3.5)/ (500.*365.*24.*3600.*4.*TMath::Pi()*reTot[3]->Eval(pnu[0]));
        fluxWeight[1] = (reTot2[7]->Eval(pnu[0])*1.47e21*3.5)/ (500.*365.*24.*3600.*4.*TMath::Pi()*reTot[3]->Eval(pnu[0]));
      }

      if(TMath::Abs(mode) > 30) { fluxWeight[1] = fluxWeight[0]; }
        //if(TMath::Abs(ipnu[0]) == 12) { fluxWeight[1] = fluxWeight[1]/2.; }
        //if(fluxWeight[0]>0.1) {fluxWeight[0] = 10e-22;}
        //if(fluxWeight[1]>0.1) {fluxWeight[1] = 10e-22;}

      //std::cout<<"neutrino ip and energy and flux reweights : "<<ipnu[0]<<" "<<pnu[0]<<" "<<fluxWeight[0]<<" "<<fluxWeight[1]<<std::endl;

      //0 = GAMMA, 1 = ELECTRON, 2 = MUON, 3 = PION, 4 = KAON, 5 = PROTON,  6 = CONE GENERATOR

      if(SigBkgTagger){

	for(Int_t fqLoop=0;fqLoop<fqnmrfit;fqLoop++){
/*
		if(fqmrnring[fqLoop] == 1 ) {
			 fq1rE = fq1rnll[0][1];
		}
		if(fqmrnring[fqLoop] == 2 ) {
			if((fqmrpid[fqLoop][0] == 0 && fqmrpid[fqLoop][1] == 0) || (fqmrpid[fqLoop][1] == 0 && fqmrpid[fqLoop][0] == 0))  fq2rGG = fqmrnll[fqLoop];
                        if((fqmrpid[fqLoop][0] == 1 && fqmrpid[fqLoop][1] == 1) || (fqmrpid[fqLoop][1] == 1 && fqmrpid[fqLoop][0] == 1))  fq2rEE = fqmrnll[fqLoop];
                        if((fqmrpid[fqLoop][0] == 1 && fqmrpid[fqLoop][1] == 3) || (fqmrpid[fqLoop][1] == 1 && fqmrpid[fqLoop][0] == 3))  fq2rEP = fqmrnll[fqLoop];
                        if((fqmrpid[fqLoop][0] == 3 && fqmrpid[fqLoop][1] == 3) || (fqmrpid[fqLoop][1] == 3 && fqmrpid[fqLoop][0] == 3))  fq2rPP = fqmrnll[fqLoop];
		}
		if(fqmrnring[fqLoop] == 3 ) {
			if( fqmrpid[fqLoop][0] == 0 && fqmrpid[fqLoop][1] == 0 && fqmrpid[fqLoop][2] == 0 )  fq3rGGG = fqmrnll[fqLoop];
                        if( fqmrpid[fqLoop][0] == 1 && fqmrpid[fqLoop][1] == 1 && fqmrpid[fqLoop][2] == 1 )  fq3rEEE = fqmrnll[fqLoop];
                        if( fqmrpid[fqLoop][0] == 3 && fqmrpid[fqLoop][1] == 3 && fqmrpid[fqLoop][2] == 3 )  fq3rPPP = fqmrnll[fqLoop];
                        if( (fqmrpid[fqLoop][0] == 0 && fqmrpid[fqLoop][1] == 0 && fqmrpid[fqLoop][2] == 1) || (fqmrpid[fqLoop][0] == 0 && fqmrpid[fqLoop][1] == 1 && fqmrpid[fqLoop][2] == 0) || (fqmrpid[fqLoop][0] == 1 && fqmrpid[fqLoop][1] == 0 && fqmrpid[fqLoop][2] == 0) )  fq3rGGE = fqmrnll[fqLoop];
                        if( (fqmrpid[fqLoop][0] == 0 && fqmrpid[fqLoop][1] == 0 && fqmrpid[fqLoop][2] == 3) || (fqmrpid[fqLoop][0] == 0 && fqmrpid[fqLoop][1] == 3 && fqmrpid[fqLoop][2] == 0) || (fqmrpid[fqLoop][0] == 3 && fqmrpid[fqLoop][1] == 0 && fqmrpid[fqLoop][2] == 0) )  fq3rGGP = fqmrnll[fqLoop];
		}
*/
	int ringN = fqmrifit[fqLoop]/1e8;
        int pid1 = fqmrifit[fqLoop] % 10;
        int pid2 = fqmrifit[fqLoop] / 10 % 10;
        int pid3 = fqmrifit[fqLoop] / 100% 10;

	if(TMath::Abs(fqmrifit[fqLoop]) < 1e9 && ringN == 2){
		if(pid1 == 1 && pid2 == 1) {fq2rEE = fqmrnll[fqLoop]; angleee = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][1][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][1][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][1][2]; momee[0] = fqmrmom[fqLoop][0]; momee[1] = fqmrmom[fqLoop][1]; }
		if(pid1 == 3 && pid2 == 3) {fq2rPP = fqmrnll[fqLoop]; anglepp = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][1][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][1][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][1][2]; mompp[0] = fqmrmom[fqLoop][0]; mompp[1] = fqmrmom[fqLoop][1]; }
		if(pid1 == 1 && pid2 == 3) {fq2rEP = fqmrnll[fqLoop]; angleepi = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][1][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][1][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][1][2]; momepi[0] = fqmrmom[fqLoop][0]; momepi[1] = fqmrmom[fqLoop][1]; }
		if(pid1 == 3 && pid2 == 1) {fq2rPE = fqmrnll[fqLoop]; anglepie = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][1][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][1][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][1][2]; mompie[0] = fqmrmom[fqLoop][0]; mompie[1] = fqmrmom[fqLoop][1];}
	}
// angle123[3]: [0],[1],[2]-> 12,13,23
	else if(TMath::Abs(fqmrifit[fqLoop]) < 1e9 && ringN == 3){
                if(pid1 == 1 && pid2 == 1 && pid3 == 1) {fq3rEEE = fqmrnll[fqLoop]; 
			angleeee[0] = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][1][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][1][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][1][2]; 
			angleeee[1] = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][2][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][2][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][2][2];
			angleeee[2] = fqmrdir[fqLoop][1][0]*fqmrdir[fqLoop][2][0]+fqmrdir[fqLoop][1][1]*fqmrdir[fqLoop][2][1]+fqmrdir[fqLoop][1][2]*fqmrdir[fqLoop][2][2];				
			momeee[0] = fqmrmom[fqLoop][0]; momeee[1] = fqmrmom[fqLoop][1]; momeee[2] = fqmrmom[fqLoop][2]; }
                if(pid1 == 3 && pid2 == 3 && pid3 == 3) {fq3rPPP = fqmrnll[fqLoop];
                        angleppp[0] = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][1][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][1][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][1][2];
                        angleppp[1] = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][2][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][2][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][2][2];
                        angleppp[2] = fqmrdir[fqLoop][1][0]*fqmrdir[fqLoop][2][0]+fqmrdir[fqLoop][1][1]*fqmrdir[fqLoop][2][1]+fqmrdir[fqLoop][1][2]*fqmrdir[fqLoop][2][2];
                        momppp[0] = fqmrmom[fqLoop][0]; momppp[1] = fqmrmom[fqLoop][1]; momppp[2] = fqmrmom[fqLoop][2]; }
                if(pid1 == 1 && pid2 == 3 && pid3 == 3) {fq3rEPP = fqmrnll[fqLoop];
                        angleepp[0] = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][1][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][1][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][1][2];
                        angleepp[1] = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][2][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][2][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][2][2];
                        angleepp[2] = fqmrdir[fqLoop][1][0]*fqmrdir[fqLoop][2][0]+fqmrdir[fqLoop][1][1]*fqmrdir[fqLoop][2][1]+fqmrdir[fqLoop][1][2]*fqmrdir[fqLoop][2][2];
                        momepp[0] = fqmrmom[fqLoop][0]; momepp[1] = fqmrmom[fqLoop][1]; momepp[2] = fqmrmom[fqLoop][2]; }
                if(pid1 == 3 && pid2 == 1 && pid3 == 3) {fq3rPEP = fqmrnll[fqLoop];
                        anglepep[0] = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][1][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][1][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][1][2];
                        anglepep[1] = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][2][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][2][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][2][2];
                        anglepep[2] = fqmrdir[fqLoop][1][0]*fqmrdir[fqLoop][2][0]+fqmrdir[fqLoop][1][1]*fqmrdir[fqLoop][2][1]+fqmrdir[fqLoop][1][2]*fqmrdir[fqLoop][2][2];
                        mompep[0] = fqmrmom[fqLoop][0]; mompep[1] = fqmrmom[fqLoop][1]; mompep[2] = fqmrmom[fqLoop][2]; }
                if(pid1 == 3 && pid2 == 3 && pid3 == 1) {fq3rPPE = fqmrnll[fqLoop];
                        angleppe[0] = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][1][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][1][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][1][2];
                        angleppe[1] = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][2][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][2][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][2][2];
                        angleppe[2] = fqmrdir[fqLoop][1][0]*fqmrdir[fqLoop][2][0]+fqmrdir[fqLoop][1][1]*fqmrdir[fqLoop][2][1]+fqmrdir[fqLoop][1][2]*fqmrdir[fqLoop][2][2];
                        momppe[0] = fqmrmom[fqLoop][0]; momppe[1] = fqmrmom[fqLoop][1]; momppe[2] = fqmrmom[fqLoop][2]; }
                if(pid1 == 1 && pid2 == 1 && pid3 == 3) {fq3rEEP = fqmrnll[fqLoop];
                        angleeep[0] = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][1][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][1][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][1][2];
                        angleeep[1] = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][2][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][2][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][2][2];
                        angleeep[2] = fqmrdir[fqLoop][1][0]*fqmrdir[fqLoop][2][0]+fqmrdir[fqLoop][1][1]*fqmrdir[fqLoop][2][1]+fqmrdir[fqLoop][1][2]*fqmrdir[fqLoop][2][2];
                        momeep[0] = fqmrmom[fqLoop][0]; momeep[1] = fqmrmom[fqLoop][1]; momeep[2] = fqmrmom[fqLoop][2]; }
                if(pid1 == 1 && pid2 == 3 && pid3 == 1) {fq3rEPE = fqmrnll[fqLoop];
                        angleepe[0] = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][1][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][1][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][1][2];
                        angleepe[1] = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][2][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][2][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][2][2];
                        angleepe[2] = fqmrdir[fqLoop][1][0]*fqmrdir[fqLoop][2][0]+fqmrdir[fqLoop][1][1]*fqmrdir[fqLoop][2][1]+fqmrdir[fqLoop][1][2]*fqmrdir[fqLoop][2][2];
                        momepe[0] = fqmrmom[fqLoop][0]; momepe[1] = fqmrmom[fqLoop][1]; momepe[2] = fqmrmom[fqLoop][2]; }
                if(pid1 == 3 && pid2 == 1 && pid3 == 1) {fq3rPEE = fqmrnll[fqLoop];
                        anglepee[0] = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][1][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][1][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][1][2];
                        anglepee[1] = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][2][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][2][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][2][2];
                        anglepee[2] = fqmrdir[fqLoop][1][0]*fqmrdir[fqLoop][2][0]+fqmrdir[fqLoop][1][1]*fqmrdir[fqLoop][2][1]+fqmrdir[fqLoop][1][2]*fqmrdir[fqLoop][2][2];
                        mompee[0] = fqmrmom[fqLoop][0]; mompee[1] = fqmrmom[fqLoop][1]; mompee[2] = fqmrmom[fqLoop][2]; }
	}
      }
	

        double xpos = fq1rpos[0][1][0];
        double ypos = fq1rpos[0][1][1];
        double zpos = fq1rpos[0][1][2];
        double rpos = TMath::Sqrt(xpos*xpos+ypos*ypos);
        fqwall = std::min(1690.-rpos,std::min(1810.-zpos,1810.+zpos));
        double tempDir[3], tempPos[3];
        for(Int_t loopTemp=0;loopTemp<3;loopTemp++){
		tempDir[loopTemp] = fq1rdir[0][1][loopTemp];
                tempPos[loopTemp] = fq1rpos[0][1][loopTemp];
	}
        towall = GetToWall(tempPos, tempDir);
	//std::cout<<"towall is "<<towall<<" "<<fq1rdir[0][1][2]<<" "<<fq1rpos[0][1][2]<<std::endl;
	//std::cout<<"fqwall and towall "<<fqwall<<" "<<towall<<std::endl;
        double lemu = fq1rnll[0][2]-fq1rnll[0][1];
        double lpie = fq1rnll[0][1]-fqpi0nll[0];
        double lpimu = fq1rnll[0][2]-fq1rnll[0][3];

        double pe = fq1rmom[0][1];
        double me = 0.5109989461;
        double ee = TMath::Sqrt(pe*pe+me*me);
        double mp = 938.2720813;
        double mn = 939.5654133;
	erec1r = 0;
        eTOpre = TMath::Sqrt( (fqtwnd_prftpos[0][0] - fq1rpos[0][1][0])* (fqtwnd_prftpos[0][0] - fq1rpos[0][1][0]) + (fqtwnd_prftpos[0][1] - fq1rpos[0][1][1])* (fqtwnd_prftpos[0][1] - fq1rpos[0][1][1]) + (fqtwnd_prftpos[0][2] - fq1rpos[0][1][2])* (fqtwnd_prftpos[0][2] - fq1rpos[0][1][2]));

	// arxiv. 1502.01550 eq. 11
        double costhbeam = fq1rdir[0][1][0]*dirnu[0][0]
                              + fq1rdir[0][1][1]*dirnu[0][1]
                              + fq1rdir[0][1][2]*dirnu[0][2];
        erec1r = (me*me+(mn-27)*(mn-27)-mp*mp-2*(mn-27)*ee)/-2./(mn-27-ee+pe*costhbeam)/1000.;
	//std::cout<<"directoins for fq and nu: "<<fq1rdir[0][1][0]<<" "<<fq1rdir[0][1][1]<<" "<<fq1rdir[0][1][2]<<" "<<dirnu[0][0]<<" "<<dirnu[0][1]<<" "<<dirnu[0][2]<<std::endl;
        //std::cout<<"costhbeam, me, mn, mp, ee and erec1r "<<costhbeam<<" "<<me<<" "<<mn<<" "<<mp<<" "<<ee<<" "<<erec1r<<std::endl;


        double md = 1232;
        double mN = (mp + mn) / 2.;

	erecmr = 0;

	// 2 rings
	if (fqmrnring[0] == 2) {
	  int pidcode = 0;
	  int ie = -1;
	  // 1st (most energetic) ring
	  if ((fqmrpid[0][0]==2)||(fqmrpid[0][0]==3)) {
	    pidcode = 2;
	  } else if (fqmrpid[0][0] == 1) {
	    ie = 0;
	  } else {
	    std::cout << "Oh no! fqmrnring[0] = " << fqmrnring[0] << " and fqmrpid[0][0] = " << fqmrpid[0][0] << std::endl;
	  }
	  // 2nd ring
	  if ((fqmrpid[0][1]==2)||(fqmrpid[0][1]==3)) {
	    pidcode++;
	  } else if (fqmrpid[0][1] == 1) {
	    if (ie < 0) {ie = 1;}
	  } else {
	    std::cout << "Oh no! fqmrnring[0] = " << fqmrnring[0] << " and fqmrpid[0][1] = " << fqmrpid[0][1] << std::endl;
	  }
	  if (ie < 0) {
	    //	    std::cout << "Ugh, ie = " << ie << ". Setting to 0" << std::endl;
	    ie = 0;
	  }

	  // arxiv. 1707.01048 eq 5
	  pe = fqmrmom[0][ie];
	  ee = TMath::Sqrt(pe*pe+me*me);
	  costhbeam = fqmrdir[0][ie][0]*dirnu[0][0]
			   + fqmrdir[0][ie][1]*dirnu[0][1]
			   + fqmrdir[0][ie][2]*dirnu[0][2];
	  erecmr = (md*md-mN*mN-me*me+2*mN*ee)/2/(mN-ee+pe*costhbeam)/1000.;


	  // 3 rings
	} else if (fqmrnring[0] == 3) {
	  int pidcode = 0;
	  int ie = -1;
	  // 1st (most energetic) ring
	  if ((fqmrpid[0][0]==2)||(fqmrpid[0][0]==3)) {
	    pidcode = 4;
	  } else if (fqmrpid[0][0] == 1) {
	    ie = 0;
	  } else {
	    std::cout << "Oh no! fqmrnring[0] = " << fqmrnring[0] << " and fqmrpid[0][0] = " << fqmrpid[0][0] << std::endl;
	  }
	  // 2nd ring
	  if ((fqmrpid[0][1]==2)||(fqmrpid[0][1]==3)) {
	    pidcode += 2;
	  } else if (fqmrpid[0][1] == 1) {
	    if (ie < 0) {ie = 1;}
	  } else {
	    std::cout << "Oh no! fqmrnring[0] = " << fqmrnring[0] << " and fqmrpid[0][1] = " << fqmrpid[0][1] << std::endl;
	  }
	  // 3rd ring
	  if ((fqmrpid[0][2]==2)||(fqmrpid[0][2]==3)) {
	    pidcode++;
	  } else if (fqmrpid[0][2] == 1) {
	    if (ie < 0) {ie = 2;}
	  } else {
	    std::cout << "Oh no! fqmrnring[0] = " << fqmrnring[0] << " and fqmrpid[0][2] = " << fqmrpid[0][2] << std::endl;
	  }
	  if (ie < 0) {
	    //	    std::cout << "Ugh, ie = " << ie << ". Setting to 0" << std::endl;
	    ie = 0;
	  }

	  pe = fqmrmom[0][ie];
	  ee = TMath::Sqrt(pe*pe+me*me);
	  costhbeam = fqmrdir[0][ie][0]*dirnu[0][0]
			   + fqmrdir[0][ie][1]*dirnu[0][1]
			   + fqmrdir[0][ie][2]*dirnu[0][2];
	  erecmr = (md*md-mN*mN-me*me+2*mN*ee)/2/(mN-ee+pe*costhbeam)/1000.;
	}

	else{
	  erecmr = erec1r;
	}

        /////////////////////////////////////////////////////////////////////////
        ////////   Neutron information   ///////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////
	
	for(Int_t neutronloop=0;neutronloop<1000;neutronloop++) tdist[neutronloop]=0;
        nCapture = 0;
        for(int iw=0; iw<nscndprt; iw++){
          if( lmecscnd[iw]==18 && /* Neutron capture */
          iprtscnd[iw]==22 /* PDG code for gamma */
          )
          {
            for(int innerloop =0 ; innerloop<10; innerloop++) tdist[innerloop]=0.0;
            for(int jw=0; jw<3; jw++)
            {
              tdist[nCapture]+=(posv[jw] - vtxscnd[iw][jw])*(posv[jw] - vtxscnd[iw][jw]);
              //std::cout<<vtxscnd[i][j]<<" "<<posv[j]<<" "<<(posv[j] - vtxscnd[i][j])*(posv[j] - vtxscnd[i][j])<<std::endl;
            }
            nCapture ++;
	    nCaptureEff += neutronSpline->Eval(tdist[nCapture]);	    
	    //std::cout<<"one neutron at "<<nCapture<<" with distance of "<<tdist[nCapture-1]<<" "<<std::endl;
          }
        }

	//std::cout<<"erec and likelihood ratios examine: "<<erec1r<<" "<<erecmr<<" "<<fq2rGG<<" "<<fq2rEE<<std::endl;
	sigCategory = -1;
	bkgCategory = -1;
	
	//std::cout<<"nhitac, fqwall, fqmrnring[0], evis, lemu, fq1rmom[0][1], fqnse, mode: "<<nhitac<<" "<< fqwall<<" "<< fqmrnring[0]<<" "<<evis<<" "<< lemu<<" "<< fq1rmom[0][1]<<" "<< fqnse<< " "<<mode<<std::endl;
///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Check signal and background categories:  1 ring 0 decay, 1ring 1decay and 2 ring 0 decay.// 1ring 0 decay

          isBKG = false;
          isSIG = false;	
          if((nhitac<16)
          && (fqwall > 200.)
          && (fqmrnring[0] == 1)
	  && fq1rmom[0][1] >30
          && (lemu > fq1rmom[0][1]*0.2)
          //&& (fq1rmom[0][1]>100.)
	  && fqnse == 1){
		//std::cout<<"towall is "<<towall<<" "<<fq1rdir[0][1][2]<<" "<<fq1rpos[0][1][2]<<std::endl;

		if(TMath::Abs(mode) < 30  && TMath::Abs(ipnu[0])==12) isSIG = true;
		else isBKG = true; 
/*
                //std::cout<<"pass 1 "<<std::endl;
		if(TMath::Abs(mode) >30) {
			isBKG = true;

			std::cout<<"pass 2 "<<std::endl;
			for(Int_t l1=0;l1<Npvc;l1++){
				std::cout<<"Ipvc[l1], Iflvc[l1]: "<<Ipvc[l1]<<" "<<Iflvc[l1]<<std::endl;
				if(Ipvc[l1] == 111 && Iflvc[l1] != 3 && Iflvc[l1] != 4 && Iflvc[l1] != 5) { isBKG = true; std::cout<<"got one. "<<std::endl; exit(1);	}
			}
				if(isBKG == true){
					for(Int_t l2=0;l2<nscndprt;l2++){
						if(iprntprt[l2] == 111 && (iprtscnd[l2] == 3 || iprtscnd[l2] == 4 || iprtscnd[l2] == 5) ) isBKG = false;
					}
				}

			for(Int_t l1=0;l1<nscndprt;l1++){
                                if(iprtscnd[l1] == 111 && iprtscnd[l1] != 3 && iprtscnd[l1] != 4 && iprtscnd[l1] != 5) isBKG = true;
                        }

		}	  
		else {
			if(TMath::Abs(ipnu[0])==12) isSIG = true; 
                        for(Int_t l1=0;l1<nscndprt;l1++){
                                if(iprtscnd[l1] == 111 && iprtscnd[l1] != 3 && iprtscnd[l1] != 4 && iprtscnd[l1] != 5) isSIG = false;
			}

		}
*/
		if(isBKG == true) bkgCategory = 0;
                if(isSIG == true) sigCategory = 0;

	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
// 1ring 1 decay 

          else if((nhitac<16)
          && (fqwall > 200.)
	  && fq1rmom[0][1] > 30
          && (fqmrnring[0] == 1)
          && (lemu > fq1rmom[0][1]*0.2)
          //&& (fq1rmom[0][1]>100.)
          && fqnse == 2){

                if(TMath::Abs(mode) < 30  && ipnu[0]==12) isSIG = true;
                else isBKG = true;
/*
                if(TMath::Abs(mode) >30) {
		isBKG = true;

                        for(Int_t l1=0;l1<Npvc;l1++){
                                if(Ipvc[l1] == 111 && Iflvc[l1] != 3 && Iflvc[l1] != 4 && Iflvc[l1] != 5) isBKG = true;
                        }
                                if(isBKG == true){
                                        for(Int_t l2=0;l2<nscndprt;l2++){
                                                if(iprntprt[l2] == 111 && (iprtscnd[l2] == 3 || iprtscnd[l2] == 4 || iprtscnd[l2] == 5) ) isBKG = false;
                                        }
                                }

                        for(Int_t l1=0;l1<nscndprt;l1++){
                                if(iprtscnd[l1] == 111 && iprtscnd[l1] != 3 && iprtscnd[l1] != 4 && iprtscnd[l1] != 5) isBKG = true;
                        }

                }
                else {
                        if(TMath::Abs(ipnu[0])==12) isSIG = true;
                        for(Int_t l1=0;l1<nscndprt;l1++){
                                if(iprtscnd[l1] == 111 && iprtscnd[l1] != 3 && iprtscnd[l1] != 4 && iprtscnd[l1] != 5) isSIG = false;
                        }

                }
*/
                if(isBKG == true) bkgCategory = 1;
                if(isSIG == true) sigCategory = 1;

	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
// 2 ring 0 decay

          else if((nhitac<16)
          && (fqwall > 200.)
	  && fq1rmom[0][1] > 30
          && (fqmrnring[0] > 1)
          && (lemu > fq1rmom[0][1]*0.2)
          //&& (fq1rmom[0][1]>100.)
          && fqnse < 3){

                if(TMath::Abs(mode) < 30  && ((ipnu[0]==12 && fqnse <3) || (ipnu[0]==-12 && fqnse == 1)) ) isSIG = true;
                else isBKG = true;
/*
                if(TMath::Abs(mode) >30) {
			isBKG = true;

                        for(Int_t l1=0;l1<Npvc;l1++){
				//std::cout<<"Ipvc[l1], Iflvc[l1]: "<<Ipvc[l1]<<" "<<Iflvc[l1]<<std::endl;
                                if(Ipvc[l1] == 111 && Iflvc[l1] != 3 && Iflvc[l1] != 4 && Iflvc[l1] != 5) {
					isBKG = true; 
				}
                        }
                                if(isBKG == true){
                                        for(Int_t l2=0;l2<nscndprt;l2++){
                                                if(iprntprt[l2] == 111 && (iprtscnd[l2] == 3 || iprtscnd[l2] == 4 || iprtscnd[l2] == 5) ) isBKG = false;
                                        }
                                }

                        for(Int_t l1=0;l1<nscndprt;l1++){
                                if(iprtscnd[l1] == 111 && iprtscnd[l1] != 3 && iprtscnd[l1] != 4 && iprtscnd[l1] != 5) isBKG = true;
                        }
                }
                else {
                        if(TMath::Abs(ipnu[0])==12) isSIG = true;
                        for(Int_t l1=0;l1<nscndprt;l1++){
                                if(iprtscnd[l1] == 111 && iprtscnd[l1] != 3 && iprtscnd[l1] != 4 && iprtscnd[l1] != 5) isSIG = false;
                        }
                }
*/
                if(isBKG == true) bkgCategory = 2;
                if(isSIG == true) sigCategory = 2;

	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

	}


        tt->Fill();
   }

   tt->Write();
   ff->Write();

   ff->Close();
}


//#endif // #ifdef THEIA_cxx
