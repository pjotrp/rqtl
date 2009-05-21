# Make file for BioLib modules 
#
#   Usage: cmake . ; make
#
# this cmake file requires the full biolib source tree

cmake_minimum_required(VERSION 2.6)

PROJECT(Biolib_rqtl)
SET (M_NAME rqtl)
SET (M_VERSION 1.12-19)

IF(NOT BUILD_LIBS)
  # Building in a local module: Set the module search path manually
  SET (MAP_ROOT ../../../../..)
  SET (CMAKE_MODULE_PATH ${MAP_ROOT}/tools/cmake-support/modules)
  IF(NOT IS_DIRECTORY ${CMAKE_MODULE_PATH})
    MESSAGE(FATAL_ERROR "Can not find BioLib context")
  ENDIF(NOT IS_DIRECTORY ${CMAKE_MODULE_PATH})
ENDIF(NOT BUILD_LIBS)

FIND_PACKAGE(RLibs REQUIRED)  # require some Rlib functionality at runtime
FIND_PACKAGE(Map REQUIRED)

SET(LIBNAME biolib_rqtl-${BIOLIB_VERSION})  # shared library name

SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../../build)

INCLUDE_DIRECTORIES(../../src)
INCLUDE_DIRECTORIES(${R_INCLUDE_PATH})

BUILD_CLIB()

ADD_LIBRARY(${LIBNAME} SHARED
../../src/countXO.c
../../src/discan.c
../../src/discan_covar.c
../../src/effectscan.c
../../src/fitqtl_hk.c
../../src/fitqtl_imp.c
../../src/forwsel.c
../../src/hmm_4way.c
../../src/hmm_bc.c
../../src/hmm_bci.c
../../src/hmm_f2.c
../../src/hmm_f2i.c
../../src/hmm_main.c
../../src/hmm_ri4self.c
../../src/hmm_ri4sib.c
../../src/hmm_ri8self.c
../../src/hmm_ri8sib.c
../../src/info.c
../../src/lapackutil.c
../../src/ril48_reorg.c
../../src/ripple.c
../../src/scanone_ehk.c
../../src/scanone_em.c
../../src/scanone_em_covar.c
../../src/scanone_hk.c
../../src/scanone_imp.c
../../src/scanone_mr.c
../../src/scanone_np.c
../../src/scantwo_binary_em.c
../../src/scantwo_em.c
../../src/scantwo_hk.c
../../src/scantwo_imp.c
../../src/scantwo_mr.c
../../src/simulate.c
../../src/simulate_ril.c
../../src/stahl_mf.c
../../src/summary_scantwo.c
../../src/util.c
../../src/vbscan.c
)

# ---- The following may be required for OSX
# TARGET_LINK_LIBRARIES(${LIBNAME} ${ZLIB_NAME})

INSTALL_CLIB()
