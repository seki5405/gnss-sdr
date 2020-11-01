/*!
 * \file notch_lite_cc.h
 * \brief Implements a notch filter light algorithm
 * \author Antonio Ramos (antonio.ramosdet(at)gmail.com)
 *
 * -----------------------------------------------------------------------------
 *
 * Copyright (C) 2010-2019 (see AUTHORS file for a list of contributors)
 *
 * GNSS-SDR is a software defined Global Navigation
 *          Satellite Systems receiver
 *
 * This file is part of GNSS-SDR.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * -----------------------------------------------------------------------------
 */

#ifndef GNSS_SDR_NOTCH_LITE_CC_H
#define GNSS_SDR_NOTCH_LITE_CC_H

#if GNURADIO_USES_STD_POINTERS
#else
#include <boost/shared_ptr.hpp>
#endif
#include <gnuradio/block.h>
#include <gnuradio/fft/fft.h>
#include <volk_gnsssdr/volk_gnsssdr_alloc.h>  // for volk_gnsssdr::vector
#include <cstdint>
#include <memory>

/** \addtogroup Input_Filter
 * \{ */
/** \addtogroup Input_filter_gnuradio_blocks
 * \{ */


class NotchLite;

#if GNURADIO_USES_STD_POINTERS
using notch_lite_sptr = std::shared_ptr<NotchLite>;
#else
using notch_lite_sptr = boost::shared_ptr<NotchLite>;
#endif

notch_lite_sptr make_notch_filter_lite(
    float p_c_factor,
    float pfa,
    int32_t length,
    int32_t n_segments_est,
    int32_t n_segments_reset,
    int32_t n_segments_coeff);

/*!
 * \brief This class implements a real-time software-defined multi state notch filter light version
 */
class NotchLite : public gr::block
{
public:
    ~NotchLite() = default;

    int general_work(int noutput_items, gr_vector_int &ninput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items);

private:
    friend notch_lite_sptr make_notch_filter_lite(float p_c_factor, float pfa, int32_t length, int32_t n_segments_est, int32_t n_segments_reset, int32_t n_segments_coeff);
    NotchLite(float p_c_factor, float pfa, int32_t length, int32_t n_segments_est, int32_t n_segments_reset, int32_t n_segments_coeff);
    std::unique_ptr<gr::fft::fft_complex> d_fft_;
    volk_gnsssdr::vector<float> power_spect_;
    gr_complex last_out_;
    gr_complex z_0_;
    gr_complex p_c_factor_;
    gr_complex c_samples1_;
    gr_complex c_samples2_;
    float pfa_;
    float thres_;
    float noise_pow_est_;
    float angle1_;
    float angle2_;
    int32_t length_;
    int32_t n_segments_;
    int32_t n_segments_est_;
    int32_t n_segments_reset_;
    int32_t n_segments_coeff_reset_;
    int32_t n_segments_coeff_;
    int32_t n_deg_fred_;
    bool filter_state_;
};


/** \} */
/** \} */
#endif  // GNSS_SDR_NOTCH_LITE_CC_H
