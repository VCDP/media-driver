/*buffer sharing in hal layer for video copy*/
//!
//! \file     vphal_render_blitter.h
//! \brief    Common interface and structure used in Blitter
//! \details  Common interface and structure used in Blitter which are platform independent
//!

#ifndef __VPHAL_BLITTER_STATE_H__
#define __VPHAL_BLITTER_STATE_H__

#include "vphal_render_renderstate.h"
#include "vphal_common.h"
#include "hal_kerneldll.h"
#include "mos_os.h"




typedef class VPHAL_BLITTER_STATE *PVPHAL_BLITTER_STATE;

class VPHAL_BLITTER_STATE : public RenderState
{

public:

	VPHAL_DNDI_CACHE_CNTL           DnDiSurfMemObjCtl;
	Kdll_State                      *m_pKernelDllState;                           //!< Kernel DLL state
    static int                      iframe;

	VPHAL_BLITTER_STATE(
		PMOS_INTERFACE                  pOsInterface,
		PRENDERHAL_INTERFACE            pRenderHal,
		PVPHAL_RNDR_PERF_DATA           pPerfData,
		const VPHAL_DNDI_CACHE_CNTL     &dndiCacheCntl,
		MOS_STATUS                      *peStatus
	);

	VPHAL_BLITTER_STATE( const VPHAL_BLITTER_STATE& ) = delete;
	VPHAL_BLITTER_STATE& operator=(const VPHAL_BLITTER_STATE&) = delete;

	virtual ~VPHAL_BLITTER_STATE();

	virtual MOS_STATUS Initialize(
        const VphalSettings    *pSettings,
        Kdll_State             *pKernelDllState);

	virtual void Destroy()
	{};

	virtual bool IsNeeded(
        PCVPHAL_RENDER_PARAMS  pcRenderParams,
        RenderpassData         *pRenderPassData)
	{

		return false;
	};


	virtual bool IsMultipleStreamSupported()
    {

        return false;
    }


	virtual	MOS_STATUS Render(
        PCVPHAL_RENDER_PARAMS  pcRenderParams,
        RenderpassData         *pRenderPassData);




};




#endif // __VPHAL_BLITTER_STATE_H__


