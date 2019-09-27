#include "vphal_blitter_state_g9_base.h"

VPHAL_BLITTER_STATE_G9_BASE::VPHAL_BLITTER_STATE_G9_BASE(
		PMOS_INTERFACE                  pOsInterface,
		PRENDERHAL_INTERFACE            pRenderHal,
		PVPHAL_RNDR_PERF_DATA           pPerfData,
		const VPHAL_DNDI_CACHE_CNTL     &dndiCacheCntl,
		MOS_STATUS                      *peStatus)
		:VPHAL_BLITTER_STATE(pOsInterface, pRenderHal, pPerfData, dndiCacheCntl, peStatus)
{
}

VPHAL_BLITTER_STATE_G9_BASE::~VPHAL_BLITTER_STATE_G9_BASE()
{}


