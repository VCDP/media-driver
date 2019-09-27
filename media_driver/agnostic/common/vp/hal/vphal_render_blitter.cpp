#include "vphal_render_blitter.h"
#include <unistd.h>

VPHAL_BLITTER_STATE::VPHAL_BLITTER_STATE(
		PMOS_INTERFACE                  pOsInterface,
		PRENDERHAL_INTERFACE            pRenderHal,
		PVPHAL_RNDR_PERF_DATA           pPerfData,
		const VPHAL_DNDI_CACHE_CNTL     &dndiCacheCntl,
		MOS_STATUS                      *peStatus
	):RenderState(pOsInterface, pRenderHal, pPerfData, peStatus)
{
	DnDiSurfMemObjCtl = dndiCacheCntl;
}


VPHAL_BLITTER_STATE::~VPHAL_BLITTER_STATE()
{}

int VPHAL_BLITTER_STATE::iframe=0;

MOS_STATUS VPHAL_BLITTER_STATE::Initialize(
        const VphalSettings    *pSettings,
        Kdll_State             *pKernelDllState)
{
	MOS_STATUS                       eStatus;
	PRENDERHAL_INTERFACE             pRenderHal;
	PVPHAL_BLITTER_STATE              pBlitterState = this;
//	MOS_USER_FEATURE_VALUE_DATA     UserFeatureData;
//    MOS_NULL_RENDERING_FLAGS        NullRenderingFlags;


    eStatus = MOS_STATUS_SUCCESS;
	pRenderHal	 = pBlitterState->m_pRenderHal;

	if (pRenderHal == nullptr)
    {
        eStatus = MOS_STATUS_UNKNOWN;
        goto finish;
    }

	MOS_UNUSED(pSettings);
    VPHAL_RENDER_CHK_NULL(pKernelDllState);

	if (m_reporting == nullptr)
    {
        m_reporting = MOS_New(VphalFeatureReport);
    }

	pBlitterState->m_pKernelDllState = pKernelDllState;

finish:
	return eStatus;

}

MOS_STATUS VPHAL_BLITTER_STATE::Render(
    PCVPHAL_RENDER_PARAMS  pcRenderParams,     // parameter isn't used
    RenderpassData         *pRenderPassData)
{
	MOS_STATUS              eStatus = MOS_STATUS_SUCCESS;

	PVPHAL_SURFACE           pSrcSurface;
    PVPHAL_SURFACE           pOutputSurface;
	pSrcSurface     = pRenderPassData->pSrcSurface;
    pOutputSurface  = pRenderPassData->pOutSurface;
    //pSrcSurface    = pcRenderParams->pSrc[0];
    //pOutputSurface = pcRenderParams->pTarget[0];
    PMOS_INTERFACE           pOsInterface;
	PVPHAL_BLITTER_STATE     pBlitterState = this;
    pOsInterface            = pBlitterState->m_pOsInterface;



	MOS_UNUSED(pcRenderParams);
	VPHAL_RENDER_ASSERT(pSrcSurface);
    VPHAL_RENDER_ASSERT(pOutputSurface);

	drm_intel_bo_switch(pSrcSurface->OsResource.bo , pOutputSurface->OsResource.bo,  pSrcSurface->OsResource.pGmmResInfo->GetBaseHeight() * 3 / 2, pSrcSurface->OsResource.pGmmResInfo->GetRenderPitch());

    if (iframe == 0)
	{
		usleep(10000);   //sleep 10ms for the first frame
		iframe++;
	}
    VpHal_RndrUpdateStatusTableAfterSubmit(pOsInterface, &m_StatusTableUpdateParams, MOS_GPU_CONTEXT_VEBOX, eStatus);
    return eStatus;
}

