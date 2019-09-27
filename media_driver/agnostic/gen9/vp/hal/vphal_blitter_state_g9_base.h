#ifndef __VPHAL_BLITTER_STATE_G9_BASE_H__
#define __VPHAL_BLITTER_STATE_G9_BASE_H__

#include "vphal_render_blitter.h"

class VPHAL_BLITTER_STATE_G9_BASE : virtual public VPHAL_BLITTER_STATE
{
public:

	VPHAL_BLITTER_STATE_G9_BASE(
		PMOS_INTERFACE                  pOsInterface,
		PRENDERHAL_INTERFACE            pRenderHal,
		PVPHAL_RNDR_PERF_DATA           pPerfData,
		const VPHAL_DNDI_CACHE_CNTL     &dndiCacheCntl,
		MOS_STATUS                      *peStatus);
	
	virtual ~VPHAL_BLITTER_STATE_G9_BASE();
		




};













#endif // __VPHAL_BLITTER_STATE_G9_BASE_H__


