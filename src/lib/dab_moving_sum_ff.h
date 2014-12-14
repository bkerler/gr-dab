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
#ifndef INCLUDED_DAB_MOVING_SUM_FF_H
#define INCLUDED_DAB_MOVING_SUM_FF_H

#include <gnuradio/sync_block.h>

class dab_moving_sum_ff;

/*
 * We use boost::shared_ptr's instead of raw pointers for all access
 * to gr::blocks (and many other data structures).  The shared_ptr gets
 * us transparent reference counting, which greatly simplifies storage
 * management issues.  This is especially helpful in our hybrid
 * C++ / Python system.
 *
 * See http://www.boost.org/libs/smart_ptr/smart_ptr.htm
 *
 * As a convention, the _sptr suffix indicates a boost::shared_ptr
 */
typedef boost::shared_ptr<dab_moving_sum_ff> dab_moving_sum_ff_sptr;

/*!
 * \brief Return a shared_ptr to a new instance of dab_moving_sum_ff.
 *
 * To avoid accidental use of raw pointers, dab_moving_sum_ff's
 * constructor is private.  dab_make_moving_sum_ff is the public
 * interface for creating new instances.
 */
dab_moving_sum_ff_sptr dab_make_moving_sum_ff (int length);

/*!
 * \brief Moving sum over a stream of floats.
 * \ingroup filter
 * \param length length of the moving sum (=number of taps)
 *
 * input: float
 * output: float
 *
 * This is the same as an FIR filter with length taps 1, but much faster
 * (linear time instead of O(n*m)). On the other hand, since only the diff is
 * calculated for each sample, there is some chance of an accumulating error.
 */
class dab_moving_sum_ff : public gr::sync_block
{
private:
  // The friend declaration allows dab_make_moving_sum_ff to
  // access the private constructor.

  friend dab_moving_sum_ff_sptr dab_make_moving_sum_ff (int length);

  dab_moving_sum_ff (int length);    // private constructor

  double d_sum;
  int d_length;

 public:
  ~dab_moving_sum_ff ();  // public destructor
  int length() const {return d_length;}
  void reset() {d_sum=0;}

  // Where all the action really happens

  int work (int noutput_items,
            gr_vector_const_void_star &input_items,
            gr_vector_void_star &output_items);
};

#endif /* INCLUDED_DAB_MOVING_SUM_FF_H */
