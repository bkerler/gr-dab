/* -*- c++ -*- */
/*
 * Copyright 2004 Free Software Foundation, Inc.
 * 
 * This file is part of GNU Radio
 * 
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

/*
 * config.h is generated by configure.  It contains the results
 * of probing for features, options etc.  It should be the first
 * file included in your .cc file.
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <dab_unpuncture_vff.h>
#include <gnuradio/io_signature.h>

/*
 * Create a new instance of dab_unpuncture_vff and return
 * a boost shared_ptr.  This is effectively the public constructor.
 */
dab_unpuncture_vff_sptr 
dab_make_unpuncture_vff (const std::vector<unsigned char> &puncturing_vector, float fillval)
{
  return gnuradio::get_initial_sptr (new dab_unpuncture_vff (puncturing_vector, fillval));
}

unsigned int dab_unpuncture_vff::ones (const std::vector<unsigned char> &puncturing_vector) {
  unsigned int onescount = 0;
  for (unsigned int i=0; i<puncturing_vector.size(); i++) {
    if (puncturing_vector[i]==1)
      onescount++;
  }
  return onescount;
}

dab_unpuncture_vff::dab_unpuncture_vff (const std::vector<unsigned char> &puncturing_vector, float fillval) : 
  gr::sync_block ("unpuncture_vff",
             gr::io_signature::make (1, 1, sizeof(float)*ones(puncturing_vector)),
             gr::io_signature::make (1, 1, sizeof(float)*puncturing_vector.size())),
  d_puncturing_vector(puncturing_vector), d_fillval(fillval)
{
  d_vlen_in  = ones(puncturing_vector);
  d_vlen_out = puncturing_vector.size();
}

int 
dab_unpuncture_vff::work (int noutput_items,
                        gr_vector_const_void_star &input_items,
                        gr_vector_void_star &output_items)
{
  int i;
  unsigned int j;
  
  const float *in = (const float *) input_items[0];
  float *out = (float *) output_items[0];

  for (i=0; i<noutput_items; i++) {
    for (j=0;j<d_vlen_out;j++) {
      if (d_puncturing_vector[j]==1)
        *out++ = *in++;
      else
        *out++ = d_fillval;
    }
  }

  return noutput_items;
}
