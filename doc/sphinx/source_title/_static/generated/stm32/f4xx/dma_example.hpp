//! \file
//! \brief Header provides template of DMA driver configuration
#ifndef STM32_DMA_CFGS_HPP_
#define STM32_DMA_CFGS_HPP_

#include <stm32_device.hpp>

namespace ecl
{


/* I2S3 TX DMA */
using i2s3_tx_dma = ecl::dma_wrap<ecl::dma_stream::dma1_5, ecl::dma_channel::ch0>;

/* I2S3 RX DMA */
using i2s3_rx_dma = ecl::dma_wrap<ecl::dma_stream::dma1_0, ecl::dma_channel::ch0>;

} // namespace ecl

#endif // STM32_DMA_CFGS_HPP_
