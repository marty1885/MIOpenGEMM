
/*******************************************************************************
 * Copyright (C) 2017 Advanced Micro Devices, Inc. All rights reserved. 
 *******************************************************************************/
#ifndef GUARD_MIOPENGEMM_OUTPUTWRITER_H
#define GUARD_MIOPENGEMM_OUTPUTWRITER_H

#include <fstream>
#include <iostream>
#include <string>

#include <miopengemm/enums.hpp>
namespace MIOpenGEMM
{
namespace outputwriting
{

class Flusher {};

class Endline {};

class BasicWriter
{

  private:  
  bool            to_terminal;
  std::ofstream * ptr_file;

  public:
  BasicWriter(bool to_terminal_, std::ofstream * ptr_file_): to_terminal(to_terminal_), ptr_file(ptr_file_) {}
  BasicWriter():BasicWriter(false, nullptr){}

  template <typename T>
  BasicWriter& operator<<(T t)
  {
    if (to_terminal)
    {
      std::cout << t;
    }

    if (ptr_file != nullptr)
    {
      (*ptr_file) << t;
    }
    return *this;
  }
};

template <>
BasicWriter& BasicWriter::operator<<(Flusher f);

template <>
BasicWriter& BasicWriter::operator<<(Endline e);


class OutputWriter
{
  private:
    Ver::E v;
    std::string filename;
    // to extract from v
    bool main_to_file;
    bool main_to_terminal;
    bool tracker_to_file;
    bool tracker_to_terminal;
    
  
    void set_v_bits();
    void initialise_file();
    
  public:
    std::ofstream file;
   BasicWriter main;
   BasicWriter tracker;
  
  public:
  
   OutputWriter();
  ~OutputWriter();
   OutputWriter(Ver::E v, std::string filename);

  template <typename T>
  OutputWriter& operator<<(T t)
  {
    main << t;
    return  *this;
  }

};

}
extern outputwriting::Flusher Flush;
extern outputwriting::Endline Endl;
}

#endif
