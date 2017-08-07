/*******************************************************************************
 * Copyright (C) 2017 Advanced Micro Devices, Inc. All rights reserved.
 *******************************************************************************/
#include <miopengemm/generic.hpp>
#include <miopengemm/jinx.hpp>
#include <miopengemm/miogemm.hpp>

namespace MIOpenGEMM
{

Solution find(float            allotted_time,
              cl_command_queue command_queue,
              cl_mem           a,
              cl_mem           b,
              cl_mem           c,
              bool             enforce_determinism,
              const Geometry&  tgg,
              bool             verbose,
              bool             with_warnings)
{

  (void)with_warnings;
  bool   c_is_const    = true;
  cl_mem workspace_gpu = nullptr;
  Ver::E e_ver         = verbose ? Ver::E::TERMINAL : Ver::E::SILENT;

  // std::cout << "\n\n" << tgg.get_string() << std::flush;
  // e_ver         = Ver::E::TERMINAL;

  std::string    constraints_string = enforce_determinism ? "C__ICE1" : "";
  Constraints    constraints(constraints_string);
  auto           find_params = get_at_least_n_seconds(allotted_time);
  owrite::Writer mowri(e_ver, "");
  Offsets        offsets = get_zero_offsets();
  Jinx           jinx(command_queue, tgg, offsets, a, b, c, c_is_const, workspace_gpu, mowri);

  if (allotted_time > 0.1)
  {
    auto soln = jinx.find(constraints, find_params);
    return soln;
  }
  else
  {
    size_t rank = 0;
    return get_default(command_queue, tgg, constraints, mowri, IfNoCache::E::GENERIC, rank);
  }
}
}
