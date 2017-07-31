/*******************************************************************************
 * Copyright (C) 2017 Advanced Micro Devices, Inc. All rights reserved.
 *******************************************************************************/
#include <string>
#include <miopengemm/devmiogemm.hpp>
#include <miopengemm/redirection.hpp>


int main()
{
  using namespace MIOpenGEMM;

  Geometry gg("tC0_tA0_tB1_colMaj1_m125_n25_k625_lda125_ldb25_ldc125_ws0_f32");  
  HyPas    hp("A_MIC4_PAD1_PLU0_LIW1_MIW0_WOS0_VEW2__B_MIC4_PAD1_PLU0_LIW0_MIW1_WOS0_VEW1__C_UNR16_GAL3_PUN1_ICE1_IWI0_SZT0_NAW16_UFO1_MAC4_SKW10_AFI1_MIA0");



  std::cout << "\n" << gg.get_string(); 
  std::cout << "\n" << hp.get_string() << '\n';
  CLHint         devhint;
  Offsets        offsets = get_zero_offsets();
  owrite::Writer mowri(Ver::E::TERMINAL, "");
  dev::Boa       boa(gg, offsets, mowri, devhint);
  for  (unsigned i = 0 ; i < 1; ++i){
    std::cout << "\n\n\n";
    boa.benchgemm({hp}, {{0, 30}, {0., 100.}});
  }

  return 0;
}




