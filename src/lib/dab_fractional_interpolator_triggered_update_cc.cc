/* -*- c++ -*- */
/*
 * Copyright 2004,2007 Free Software Foundation, Inc.
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>

#include <gnuradio/io_signature.h>
#include <dab_fractional_interpolator_triggered_update_cc.h>
#include <gnuradio/filter/mmse_fir_interpolator_cc.h>
#include <stdexcept>

// Public constructor
dab_fractional_interpolator_triggered_update_cc_sptr dab_make_fractional_interpolator_triggered_update_cc(float phase_shift, float interp_ratio)
{
  return gnuradio::get_initial_sptr (new dab_fractional_interpolator_triggered_update_cc(phase_shift, interp_ratio));
}

dab_fractional_interpolator_triggered_update_cc::dab_fractional_interpolator_triggered_update_cc(float phase_shift, float interp_ratio)
  : gr::block ("fractional_interpolator_triggered_update_cc",
        gr::io_signature::make2 (2, 2, sizeof (gr_complex), sizeof(char)),
        gr::io_signature::make (1, 1, sizeof (gr_complex))),
    d_mu (phase_shift), d_mu_inc (interp_ratio), d_next_mu_inc(interp_ratio), d_interp(new gr::filter::mmse_fir_interpolator_cc())
{
  if (interp_ratio <=  0)
    throw std::out_of_range ("interpolation ratio must be > 0");
  if (phase_shift <  0  || phase_shift > 1)
    throw std::out_of_range ("phase shift ratio must be > 0 and < 1");

  set_relative_rate (1.0 / interp_ratio);
}

dab_fractional_interpolator_triggered_update_cc::~dab_fractional_interpolator_triggered_update_cc()
{
  delete d_interp;
}

void
dab_fractional_interpolator_triggered_update_cc::forecast(int noutput_items, gr_vector_int &ninput_items_required)
{
  unsigned ninputs = ninput_items_required.size();
  for (unsigned i=0; i < ninputs; i++)

    ninput_items_required[i] =
      (int) ceil((noutput_items * d_mu_inc) + d_interp->ntaps());
}

int
dab_fractional_interpolator_triggered_update_cc::general_work(int noutput_items,
              gr_vector_int &ninput_items,
              gr_vector_const_void_star &input_items,
              gr_vector_void_star &output_items)
{
  const gr_complex *in = (const gr_complex *) input_items[0];
  const char *trigger = (const char *) input_items[1];
  gr_complex *out = (gr_complex *) output_items[0];

  int ii = 0;       // input index
  int oo = 0;        // output index

  while (oo < noutput_items && ii+(int)floor(d_mu+d_mu_inc)<ninput_items[0]) {

    out[oo++] = d_interp->interpolate(&in[ii], d_mu);

    double s = d_mu + d_mu_inc;
    double f = floor (s);
    int incr = (int) f;
    d_mu = s - f;
    ii += incr;

    for (int i=0; i<incr; i++) {
      if (*trigger == 1) {
        d_mu_inc = d_next_mu_inc;
        // fprintf(stderr, "fractional_interpolator_triggered_update: adjusting interp ratio to %f\n", d_mu_inc);
        set_relative_rate (1.0 / d_mu_inc);
      }
      trigger++;
    }
  }

  assert(ii<ninput_items[0]);
  consume_each (ii);

  return noutput_items;
}
