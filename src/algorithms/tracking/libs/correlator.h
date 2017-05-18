/*!
 * \file correlator.h
 * \brief High optimized vector correlator class
 * \authors <ul>
 *          <li> Javier Arribas, 2011. jarribas(at)cttc.es
 *          <li> Luis Esteve, 2012. luis(at)epsilon-formacion.com
 *          </ul>
 *
 * Class that implements a high optimized vector correlator class
 * using the volk library
 *
 * -------------------------------------------------------------------------
 *
 * Copyright (C) 2010-2015  (see AUTHORS file for a list of contributors)
 *
 * GNSS-SDR is a software defined Global Navigation
 *          Satellite Systems receiver
 *
 * This file is part of GNSS-SDR.
 *
 * GNSS-SDR is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GNSS-SDR is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNSS-SDR. If not, see <http://www.gnu.org/licenses/>.
 *
 * -------------------------------------------------------------------------
 */

#ifndef GNSS_SDR_CORRELATOR_H_
#define GNSS_SDR_CORRELATOR_H_

#include <string>
#include <volk/volk.h>
#include <gnuradio/gr_complex.h>

#if !defined(GENERIC_ARCH) && HAVE_SSE3
#define USING_VOLK_CW_EPL_CORR_CUSTOM 1
#endif

/*!
 * \brief Class that implements carrier wipe-off and correlators.
 *
 * Implemented versions:
 * - Generic: Standard C++ implementation.
 * - Volk: uses VOLK (Vector-Optimized Library of Kernels) and uses the processor's SIMD instruction sets. See http://gnuradio.org/redmine/projects/gnuradio/wiki/Volk
 *
 */
class Correlator
{
public:
    Correlator();
    ~Correlator();
    void Carrier_wipeoff_and_EPL_generic(int signal_length_samples, const gr_complex* input, gr_complex* carrier, gr_complex* E_code, gr_complex* P_code, gr_complex* L_code, gr_complex* E_out, gr_complex* P_out, gr_complex* L_out);
    void Carrier_wipeoff_and_EPL_volk(int signal_length_samples, const gr_complex* input, gr_complex* carrier, gr_complex* E_code, gr_complex* P_code, gr_complex* L_code, gr_complex* E_out, gr_complex* P_out, gr_complex* L_out);
    void Carrier_wipeoff_and_VEPL_volk(int signal_length_samples, const gr_complex* input, gr_complex* carrier, gr_complex* VE_code, gr_complex* E_code, gr_complex* P_code, gr_complex* L_code, gr_complex* VL_code, gr_complex* VE_out, gr_complex* E_out, gr_complex* P_out, gr_complex* L_out, gr_complex* VL_out);
    // void Carrier_wipeoff_and_EPL_volk_IQ(int prn_length_samples,int integration_time ,const gr_complex* input, gr_complex* carrier, gr_complex* E_code, gr_complex* P_code, gr_complex* L_code, gr_complex* P_data_code, gr_complex* E_out, gr_complex* P_out, gr_complex* L_out, gr_complex* P_data_out);
    void Carrier_wipeoff_and_EPL_volk_IQ(int signal_length_samples, const gr_complex* input, gr_complex* carrier, gr_complex* E_code, gr_complex* P_code, gr_complex* L_code, gr_complex* P_data_code, gr_complex* E_out, gr_complex* P_out, gr_complex* L_out, gr_complex* P_data_out);
    void Carrier_wipeoff_and_DE_volk(int signal_length_samples,
            const gr_complex* input,
            gr_complex* carrier,
            gr_complex* E_code, gr_complex* P_code, gr_complex* L_code,
            gr_complex* E_subcarrier, gr_complex* P_subcarrier, gr_complex *L_subcarrier,
            gr_complex* P_subcarrier_E_code_out,
            gr_complex* P_subcarrier_P_code_out,
            gr_complex* P_subcarrier_L_code_out,
            gr_complex* P_code_E_subcarrier_out,
            gr_complex* P_code_L_subcarrier_out );

#if USING_VOLK_CW_EPL_CORR_CUSTOM
    void Carrier_wipeoff_and_EPL_volk_custom(int signal_length_samples, const gr_complex* input, gr_complex* carrier, gr_complex* E_code, gr_complex* P_code, gr_complex* L_code, gr_complex* E_out, gr_complex* P_out, gr_complex* L_out);
#endif

    void Carrier_rotate_and_EPL_volk(int signal_length_samples,
            const gr_complex* input,
            gr_complex *phase_as_complex,
            gr_complex phase_inc_as_complex,
            const gr_complex* E_code,
            const gr_complex* P_code,
            const gr_complex* L_code,
            gr_complex* E_out,
            gr_complex* P_out,
            gr_complex* L_out );

    void Carrier_rotate_and_VEPL_volk(int signal_length_samples,
            const gr_complex* input,
            gr_complex *phase_as_complex,
            gr_complex phase_inc_as_complex,
            const gr_complex* VE_code,
            const gr_complex* E_code,
            const gr_complex* P_code,
            const gr_complex* L_code,
            const gr_complex* VL_code,
            gr_complex* VE_out,
            gr_complex* E_out,
            gr_complex* P_out,
            gr_complex* L_out,
            gr_complex* VL_out );

    void Carrier_rotate_and_DE_volk(int signal_length_samples,
            const gr_complex* input,
            gr_complex *phase_as_complex,
            gr_complex phase_inc_as_complex,
            const gr_complex* E_code,
            const gr_complex* P_code,
            const gr_complex* L_code,
            const gr_complex* E_subcarrier,
            const gr_complex* P_subcarrier,
            const gr_complex *L_subcarrier,
            gr_complex* P_subcarrier_E_code_out,
            gr_complex* P_subcarrier_P_code_out,
            gr_complex* P_subcarrier_L_code_out,
            gr_complex* P_code_E_subcarrier_out,
            gr_complex* P_code_L_subcarrier_out );

    void Carrier_rotate_and_DPE_volk(int signal_length_samples,
            const gr_complex* input,
            gr_complex *phase_as_complex,
            gr_complex phase_inc_as_complex,
            const gr_complex* E_code,
            const gr_complex* P_code,
            const gr_complex* L_code,
            const gr_complex* P_subcarrier,
            const gr_complex* PQ_subcarrier,
            gr_complex* P_subcarrier_E_code_out,
            gr_complex* P_subcarrier_P_code_out,
            gr_complex* P_subcarrier_L_code_out,
            gr_complex* P_code_PQ_subcarrier_out );

    void Carrier_rotate_and_EPL_codeless(int signal_length_samples,
            const gr_complex* input,
            gr_complex *phase_as_complex,
            gr_complex phase_inc_as_complex,
            const int *E_code_phases,
            const int *P_code_phases,
            const int *L_code_phases,
            gr_complex* E_out,
            gr_complex* P_out,
            gr_complex* L_out,
            int code_length);

    void Carrier_rotate_and_VEPL_codeless(int signal_length_samples,
            const gr_complex* input,
            gr_complex *phase_as_complex,
            gr_complex phase_inc_as_complex,
            const int *VE_code_phases,
            const int *E_code_phases,
            const int *P_code_phases,
            const int *L_code_phases,
            const int *VL_code_phases,
            const gr_complex *VE_subcarrier,
            const gr_complex *E_subcarrier,
            const gr_complex *P_subcarrier,
            const gr_complex *L_subcarrier,
            const gr_complex *VL_subcarrier,
            gr_complex* VE_out,
            gr_complex* E_out,
            gr_complex* P_out,
            gr_complex* L_out,
            gr_complex* VL_out,
            int code_length);

private:
    unsigned long next_power_2(unsigned long v);
};
#endif
