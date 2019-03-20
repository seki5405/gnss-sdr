/*!
 * \file beidou_b1i_pcps_acquisition.h
 * \brief Adapts a PCPS acquisition block to an AcquisitionInterface for
 *  Beidou B1I signals
 * \authors <ul>
 *          <li> Sergi Segura, 2018. sergi.segura.munoz(at)gmail.com
 *          </ul>
 *
 * -------------------------------------------------------------------------
 *
 * Copyright (C) 2010-2018  (see AUTHORS file for a list of contributors)
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

#ifndef GNSS_SDR_BEIDOU_B1I_PCPS_ACQUISITION_H_
#define GNSS_SDR_BEIDOU_B1I_PCPS_ACQUISITION_H_

#include "channel_fsm.h"
#include "complex_byte_to_float_x2.h"
#include "gnss_synchro.h"
#include "pcps_acquisition.h"
#include <gnuradio/blocks/float_to_complex.h>
#include <gnuradio/blocks/stream_to_vector.h>
#include <volk_gnsssdr/volk_gnsssdr.h>
#include <cstdint>
#include <string>


class ConfigurationInterface;

/*!
 * \brief This class adapts a PCPS acquisition block to an AcquisitionInterface
 *  for GPS L1 C/A signals
 */
class BeidouB1iPcpsAcquisition : public AcquisitionInterface
{
public:
    BeidouB1iPcpsAcquisition(ConfigurationInterface* configuration,
        const std::string& role, unsigned int in_streams,
        unsigned int out_streams);

    virtual ~BeidouB1iPcpsAcquisition();

    inline std::string role() override
    {
        return role_;
    }

    /*!
     * \brief Returns "BEIDOU_B1I_PCPS_Acquisition"
     */
    inline std::string implementation() override
    {
        return "BEIDOU_B1I_PCPS_Acquisition";
    }

    inline size_t item_size() override
    {
        return item_size_;
    }

    void connect(gr::top_block_sptr top_block) override;
    void disconnect(gr::top_block_sptr top_block) override;
    gr::basic_block_sptr get_left_block() override;
    gr::basic_block_sptr get_right_block() override;

    /*!
     * \brief Set acquisition/tracking common Gnss_Synchro object pointer
     * to efficiently exchange synchronization data between acquisition and
     *  tracking blocks
     */
    void set_gnss_synchro(Gnss_Synchro* p_gnss_synchro) override;

    /*!
     * \brief Set acquisition channel unique ID
     */
    inline void set_channel(unsigned int channel)
    {
        channel_ = channel;
        acquisition_->set_channel(channel_);
    }

    /*!
      * \brief Set channel fsm associated to this acquisition instance
      */
    inline void set_channel_fsm(std::shared_ptr<ChannelFsm> channel_fsm)
    {
        channel_fsm_ = channel_fsm;
        acquisition_->set_channel_fsm(channel_fsm);
    }


    /*!
     * \brief Set statistics threshold of PCPS algorithm
     */
    void set_threshold(float threshold) override;

    /*!
     * \brief Set maximum Doppler off grid search
     */
    void set_doppler_max(uint32_t doppler_max) override;

    /*!
     * \brief Set Doppler steps for the grid search
     */
    void set_doppler_step(uint32_t doppler_step) override;

    /*!
     * \brief Initializes acquisition algorithm.
     */
    void init() override;

    /*!
     * \brief Sets local code for GPS L1/CA PCPS acquisition algorithm.
     */
    void set_local_code() override;

    /*!
     * \brief Returns the maximum peak of grid search
     */
    signed int mag() override;

    /*!
     * \brief Restart acquisition algorithm
     */
    void reset() override;

    /*!
     * \brief If state = 1, it forces the block to start acquiring from the first sample
     */
    void set_state(int state) override;

    /*!
     * \brief Stop running acquisition
     */
    void stop_acquisition() override;

    /*!
     * \brief Sets the resampler latency to account it in the acquisition code delay estimation
     */
    void set_resampler_latency(uint32_t latency_samples) override;


private:
    ConfigurationInterface* configuration_;
    pcps_acquisition_sptr acquisition_;
    gr::blocks::stream_to_vector::sptr stream_to_vector_;
    gr::blocks::float_to_complex::sptr float_to_complex_;
    complex_byte_to_float_x2_sptr cbyte_to_float_x2_;
    size_t item_size_;
    std::string item_type_;
    uint32_t vector_length_;
    uint32_t code_length_;
    bool bit_transition_flag_;
    bool use_CFAR_algorithm_flag_;
    uint32_t channel_;
    std::shared_ptr<ChannelFsm> channel_fsm_;
    float threshold_;
    uint32_t doppler_max_;
    uint32_t doppler_step_;
    uint32_t sampled_ms_;
    uint32_t max_dwells_;
    int64_t fs_in_;
    bool dump_;
    bool blocking_;
    std::string dump_filename_;
    std::complex<float>* code_;
    Gnss_Synchro* gnss_synchro_;
    std::string role_;
    uint32_t in_streams_;
    uint32_t out_streams_;

    float calculate_threshold(float pfa);
};

#endif /* GNSS_SDR_BEIDOU_B1I_PCPS_ACQUISITION_H_ */
