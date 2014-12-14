# Copyright 2011 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX

add_library(gnuradio-dab SHARED
        dab_moving_sum_ff.cc                    
        dab_moving_sum_cc.cc                    
        dab_ofdm_sampler.cc                     
        dab_ofdm_coarse_frequency_correct.cc    
        dab_diff_phasor_vcc.cc                  
        dab_correct_individual_phase_offset_vff.cc 
        dab_ofdm_remove_first_symbol_vcc.cc     
        dab_estimate_sample_rate_bf.cc          
        dab_ofdm_ffs_sample.cc                  
        dab_ofdm_ffe_all_in_one.cc              
        dab_fractional_interpolator_triggered_update_cc.cc
        dab_frequency_interleaver_vcc.cc
        dab_ofdm_coarse_frequency_correct.cc
        dab_diff_phasor_vcc.cc                  
        dab_correct_individual_phase_offset_vff.cc 
        dab_ofdm_remove_first_symbol_vcc.cc     
        dab_estimate_sample_rate_bf.cc          
        dab_ofdm_ffs_sample.cc                  
        dab_ofdm_ffe_all_in_one.cc              
        dab_fractional_interpolator_triggered_update_cc.cc 
        dab_frequency_interleaver_vcc.cc        
        dab_qpsk_mapper_vbc.cc                  
        dab_qpsk_demapper_vcb.cc                
        dab_ofdm_insert_pilot_vcc.cc            
        dab_sum_phasor_trig_vcc.cc              
        dab_ofdm_move_and_insert_zero.cc        
        dab_insert_null_symbol.cc               
        dab_concatenate_signals.cc              
        dab_measure_processing_rate.cc          
        dab_sum_elements_vff.cc                 
        dab_modulo_ff.cc                        
        dab_measure_ber_b.cc                    
        dab_select_vectors.cc                   
        dab_repartition_vectors.cc              
        dab_puncture_vbb.cc                     
        dab_unpuncture_vff.cc                   
        dab_magnitude_equalizer_vcc.cc          
        dab_complex_to_interleaved_float_vcf.cc 
        dab_prune_vectors.cc                    
        dab_fib_sink_vb.cc                      
        crc16.cc

)
target_link_libraries(gnuradio-dab ${Boost_LIBRARIES} ${GRUEL_LIBRARIES} ${GNURADIO_RUNTIME_LIBRARIES} ${GNURADIO_ALL_LIBRARIES} ${GNURADIO_FILTER_LIBRARIES} ${GNURADIO_BLOCKS_LIBRARIES} ${LIBXML2_LIBRARIES})
set_target_properties(gnuradio-dab PROPERTIES DEFINE_SYMBOL "gnuradio_dab_EXPORTS")

########################################################################
# Install built library files
########################################################################
install(TARGETS gnuradio-dab
    LIBRARY DESTINATION lib${LIB_SUFFIX} # .so/.dylib file
    ARCHIVE DESTINATION lib${LIB_SUFFIX} # .lib file
    RUNTIME DESTINATION bin              # .dll file
)

########################################################################
# Build and register unit test
########################################################################
find_package(Boost COMPONENTS unit_test_framework)

include(GrTest)
set(GR_TEST_TARGET_DEPS gnuradio-dab)
#turn each test cpp file into an executable with an int main() function
add_definitions(-DBOOST_TEST_DYN_LINK -DBOOST_TEST_MAIN)

#add_executable(qa_howto_square_ff qa_howto_square_ff.cc)
#target_link_libraries(qa_howto_square_ff gnuradio-howto ${Boost_LIBRARIES})
#GR_ADD_TEST(qa_howto_square_ff qa_howto_square_ff)

#add_executable(qa_howto_square2_ff qa_howto_square2_ff.cc)
#target_link_libraries(qa_howto_square2_ff gnuradio-howto ${Boost_LIBRARIES})
#GR_ADD_TEST(qa_howto_square2_ff qa_howto_square2_ff)

########################################################################
# Python/SWIG ##########################################################
########################################################################

########################################################################
# Include swig generation macros
########################################################################
find_package(SWIG)
find_package(PythonLibs)
if(NOT SWIG_FOUND OR NOT PYTHONLIBS_FOUND)
    return()
endif()
include(GrSwig)
include(GrPython)

########################################################################
# Setup swig generation
########################################################################
foreach(incdir ${GNURADIO_RUNTIME_INCLUDE_DIRS})
    list(APPEND GR_SWIG_INCLUDE_DIRS ${incdir}/swig ${incdir}/gnuradio/swig)
endforeach(incdir)

foreach(incdir ${GRUEL_INCLUDE_DIRS})
    list(APPEND GR_SWIG_INCLUDE_DIRS ${incdir}/gruel/swig)
endforeach(incdir)

set(GR_SWIG_LIBRARIES gnuradio-dab)
#set(GR_SWIG_DOC_FILE ${CMAKE_CURRENT_BINARY_DIR}/dab_doc.i)	# howto_dab_doc
#set(GR_SWIG_DOC_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../include)

GR_SWIG_MAKE(dab_swig dab.i) # dab_swig dab_swig.i

########################################################################
# Install the build swig module
########################################################################
GR_SWIG_INSTALL(TARGETS dab_swig DESTINATION ${GR_PYTHON_DIR}${DAB_PYTHON_SUBDIR}/dab)	# dab_swig

########################################################################
# Install swig .i files for development
########################################################################
install(
    FILES
    dab.i # dab_swig.i
#    ${CMAKE_CURRENT_BINARY_DIR}/dab_doc.i # dab_swig_doc.i
    DESTINATION ${GR_INCLUDE_DIR}/dab/swig	# Not adding ${DAB_PYTHON_SUBDIR} here
)

