#include <iostream>
#include "libmcdriver_rasterizer_dynamic.hpp"


int main()
{
  try
  {
    std::string libpath = (""); // TODO: put the location of the LibMCDriver_Rasterizer-library file here.
    auto wrapper = LibMCDriver_Rasterizer::CWrapper::loadLibrary(libpath + "/libmcdriver_rasterizer."); // TODO: add correct suffix of the library
    LibMCDriver_Rasterizer_uint32 nMajor, nMinor, nMicro;
    wrapper->GetVersion(nMajor, nMinor, nMicro);
    std::cout << "LibMCDriver_Rasterizer.Version = " << nMajor << "." << nMinor << "." << nMicro;
    std::cout << std::endl;
  }
  catch (std::exception &e)
  {
    std::cout << e.what() << std::endl;
    return 1;
  }
  return 0;
}

