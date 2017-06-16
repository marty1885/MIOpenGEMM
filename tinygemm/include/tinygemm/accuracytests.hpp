#ifndef ACCURACYTESTS_HPP
#define ACCURACYTESTS_HPP


#include <algorithm>
#include <sstream>

#include <tinygemm/error.hpp>
#include <tinygemm/outputwriter.hpp>

namespace tinygemm {
namespace accuracytests {

template <typename TFloat>
void elementwise_compare(const TFloat * c_before, double beta, const TFloat * c_cpu, const TFloat * c_gpu, unsigned nels, outputwriting::OutputWriter & mowri);


}
} //namespaces

#endif
