/* COPYRIGHT (c) 2014 Umut Acar, Arthur Chargueraud, and Michael
 * Rainey
 * All rights reserved.
 *
 * \file mcss.hpp
 * \brief Maximum contiguous subsequence
 *
 */

#include "hash.hpp"
#include "sparray.hpp"

#ifndef _MINICOURSE_MCSS_H_
#define _MINICOURSE_MCSS_H_

/***********************************************************************/

/*---------------------------------------------------------------------*/
/* Maximum contiguous subsequence */

value_type mcss_seq(const sparray& xs) {
  if (xs.size() == 0)
    return LONG_MIN;
  long max_so_far = xs[0];
  long curr_max = xs[0];
  for (long i = 1; i < xs.size(); i++) {
    curr_max = std::max(xs[i], curr_max+xs[i]);
    max_so_far = std::max(max_so_far, curr_max);
  }
  return max_so_far;
}

value_type mcss_par(const sparray& xs) {
  sparray ys = partial_sums_inclusive(xs);
  scan_result m = scan(min_fct, 0l, ys);
  sparray zs = tabulate([&] (long i) { return ys[i]-m.prefix[i]; }, xs.size());
  return max(zs);
}

value_type mcss(const sparray& xs) {
#ifdef SEQUENTIAL_BASELINE
  return mcss_seq(xs);
#else
  return mcss_par(xs);
#endif
}

/***********************************************************************/

#endif /*! _MINICOURSE_MCSS_H_ */
