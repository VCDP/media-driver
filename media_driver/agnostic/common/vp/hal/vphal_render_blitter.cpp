#include "vphal_render_blitter.h"
#include <unistd.h>
#include "vphal_renderer.h"
#include "vphal_debug.h"


VPHAL_BLITTER_STATE::VPHAL_BLITTER_STATE(
		PMOS_INTERFACE                  pOsInterface,
		PRENDERHAL_INTERFACE            pRenderHal,
		PVPHAL_RNDR_PERF_DATA           pPerfData,
		MOS_STATUS                      *peStatus
	):RenderState(pOsInterface, pRenderHal, pPerfData, peStatus)
{}


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

    eStatus = MOS_STATUS_SUCCESS;
	pRenderHal	 = pBlitterState->m_pRenderHal;

	if(pRenderHal == nullptr)
    {
        eStatus = MOS_STATUS_UNKNOWN;
        goto finish;
    }

	MOS_UNUSED(pSettings);
    VPHAL_RENDER_CHK_NULL(pKernelDllState);

	if(m_reporting == nullptr)
    {
        m_reporting = MOS_New(VphalFeatureReport);
    }

	pBlitterState->m_pKernelDllState = pKernelDllState;

finish:
	return eStatus;

}

MOS_STATUS VPHAL_BLITTER_STATE::Render(
    PCVPHAL_RENDER_PARAMS  pcRenderParams,
    RenderpassData         *pRenderPassData)         // RenderpassData isn't used
{
    MOS_STATUS              eStatus = MOS_STATUS_SUCCESS;

    PVPHAL_SURFACE           pSrcSurface;
    PVPHAL_SURFACE           pOutputSurface;
    PMOS_INTERFACE           pOsInterface;

    pSrcSurface              = pcRenderParams->pSrc[0];
    pOutputSurface           = pcRenderParams->pTarget[0];
    PVPHAL_BLITTER_STATE     pBlitterState = this;
    pOsInterface             = pBlitterState->m_pOsInterface;

    MOS_UNUSED(pcRenderParams);
    VPHAL_RENDER_ASSERT(pSrcSurface);
    VPHAL_RENDER_ASSERT(pOutputSurface);

    drm_intel_bo_switch(pSrcSurface->OsResource.bo , pOutputSurface->OsResource.bo,  pSrcSurface->OsResource.pGmmResInfo->GetBaseHeight() * 3 / 2, pSrcSurface->OsResource.pGmmResInfo->GetRenderPitch());

    /* The first frame could get good result after waiting a period of time. This will be modified soon.*/
    if (iframe == 0)
    {
        usleep(10000);   //sleep 10ms for the first frame
        iframe++;
    }

    VpHal_RndrUpdateStatusTableAfterSubmit(pOsInterface, &m_StatusTableUpdateParams, MOS_GPU_CONTEXT_BLITTER, eStatus);
    return eStatus;
}

MOS_STATUS VpHal_RndrRenderBlitter(
    VphalRenderer           *pRenderer,
    PVPHAL_RENDER_PARAMS   pRenderParams,
    RenderpassData          *pRenderPassData)
{
    MOS_STATUS               eStatus;
    PMOS_INTERFACE           pOsInterface;
    RenderState              *pRenderState;
    VphalFeatureReport*      pReport;


    //------------------------------------------------------
    VPHAL_RENDER_ASSERT(pRenderer);
    VPHAL_RENDER_ASSERT(pRenderParams);
    //------------------------------------------------------

    eStatus                 = MOS_STATUS_SUCCESS;
    pReport                 = pRenderer->GetReport();
    pRenderState            = pRenderer->pRender[VPHAL_RENDER_ID_BLITTER];



    VPHAL_RENDER_CHK_NULL(pRenderState);
    VPHAL_RENDER_ASSERT(pRenderState->GetRenderHalInterface());

    pRenderer->pRender[VPHAL_RENDER_ID_BLITTER]->SetStatusReportParams(pRenderer, pRenderParams);

    VPHAL_RENDER_CHK_STATUS(pRenderState->Render(
                                                pRenderParams,
                                                pRenderPassData));

    pRenderState->CopyReporting(pReport);

finish:
    VPHAL_RENDER_NORMALMESSAGE("VPOutputPipe = %d, VEFeatureInUse = %d",
        pRenderer->GetReport()->OutputPipeMode, pRenderer->GetReport()->VEFeatureInUse);

	return eStatus;


}
