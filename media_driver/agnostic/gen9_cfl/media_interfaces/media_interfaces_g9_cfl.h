/*
* Copyright (c) 2017-2018, Intel Corporation
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
* OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
*/
//!
//! \file     media_interfaces_g9_cfl.h
//! \brief    All interfaces used for CFL that require factory creation
//!

#ifndef __MEDIA_INTERFACES_G9_CFL_H__
#define __MEDIA_INTERFACES_G9_CFL_H__

#include "media_interfaces.h"
#include "media_interfaces_cmhal.h"
#include "media_interfaces_decode_histogram.h"

#include "cm_hal_g9.h"

#include "codechal_decode_histogram_vebox_g9.h"

#ifdef _AVC_ENCODE_VME_SUPPORTED
#include "codechal_encode_avc_g9_skl.h"
#endif

class CMHalInterfacesG9Cfl : public CMHalDevice
{
protected:
    using CMHal = CM_HAL_G9_X;
    MOS_STATUS Initialize(
        CM_HAL_STATE *pCmState);
};

class DecodeHistogramDeviceG9Cfl : public DecodeHistogramDevice
{
public:
    using DecodeHistogramVebox = CodechalDecodeHistogramVeboxG9;

    MOS_STATUS Initialize(
        CodechalHwInterface *hwInterface,
        PMOS_INTERFACE osInterface);
};

class CodechalEncodeInterfacesG9Cfl
{
public:
#ifdef _JPEG_ENCODE_SUPPORTED
    using Jpeg = CodechalEncodeJpegState;
#endif
#ifdef _MPEG2_ENCODE_VME_SUPPORTED
    using Mpeg2 = CodechalEncodeMpeg2G9;
#endif

    using CscDs = CodechalEncodeCscDsG9;

#ifdef _HEVC_ENCODE_VME_SUPPORTED
    using HevcEnc = CodechalEncHevcStateG9Kbl;
#endif

#ifdef _AVC_ENCODE_VME_SUPPORTED
    using AvcEnc   = CodechalEncodeAvcEncG9Skl;
#endif
#ifdef _AVC_ENCODE_VDENC_SUPPORTED
    using AvcVdenc = CodechalVdencAvcStateG9Kbl;
#endif
#ifdef _VP8_ENCODE_SUPPORTED
    using Vp8 = CodechalEncodeVp8G9;
#endif
};

class CodechalInterfacesG9Cfl : public CodechalDevice
{
public:
    using Decode = CodechalDecodeInterfacesG9Kbl;
    using Encode = CodechalEncodeInterfacesG9Cfl;
    using Hw = CodechalHwInterfaceG9Kbl;

    MOS_STATUS Initialize(
        void *standardInfo,
        void *settings,
        MhwInterfaces *mhwInterfaces,
        PMOS_INTERFACE osInterface) override;
};

#endif // __MEDIA_INTERFACES_G9_CFL_H__
