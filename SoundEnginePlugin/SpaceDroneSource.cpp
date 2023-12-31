/*******************************************************************************
The content of this file includes portions of the AUDIOKINETIC Wwise Technology
released in source code form as part of the SDK installer package.

Commercial License Usage

Licensees holding valid commercial licenses to the AUDIOKINETIC Wwise Technology
may use this file in accordance with the end user license agreement provided
with the software or, alternatively, in accordance with the terms contained in a
written agreement between you and Audiokinetic Inc.

Apache License Usage

Alternatively, this file may be used under the Apache License, Version 2.0 (the
"Apache License"); you may not use this file except in compliance with the
Apache License. You may obtain a copy of the Apache License at
http://www.apache.org/licenses/LICENSE-2.0.

Unless required by applicable law or agreed to in writing, software distributed
under the Apache License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES
OR CONDITIONS OF ANY KIND, either express or implied. See the Apache License for
the specific language governing permissions and limitations under the License.

  Copyright (c) 2023 Audiokinetic Inc.
*******************************************************************************/

#include <string>

#include "SpaceDroneSource.h"
#include "../SpaceDroneConfig.h"

#include <AK/AkWwiseSDKVersion.h>

AK::IAkPlugin* CreateSpaceDroneSource(AK::IAkPluginMemAlloc* in_pAllocator)
{
    return AK_PLUGIN_NEW(in_pAllocator, SpaceDroneSource());
}

AK::IAkPluginParam* CreateSpaceDroneSourceParams(AK::IAkPluginMemAlloc* in_pAllocator)
{
    return AK_PLUGIN_NEW(in_pAllocator, SpaceDroneSourceParams());
}

AK_IMPLEMENT_PLUGIN_FACTORY(SpaceDroneSource, AkPluginTypeSource, SpaceDroneConfig::CompanyID, SpaceDroneConfig::PluginID)

SpaceDroneSource::SpaceDroneSource()
    : m_pParams(nullptr)
    , m_pAllocator(nullptr)
    , m_pContext(nullptr)
{

}

SpaceDroneSource::~SpaceDroneSource()
{
}

AKRESULT SpaceDroneSource::Init(AK::IAkPluginMemAlloc* in_pAllocator, AK::IAkSourcePluginContext* in_pContext, AK::IAkPluginParam* in_pParams, AkAudioFormat& in_rFormat)
{
    m_pParams = (SpaceDroneSourceParams*)in_pParams;
    m_pAllocator = in_pAllocator;
    m_pContext = in_pContext;

    m_durationHandler.Setup(m_pParams->RTPC.fDuration, in_pContext->GetNumLoops(), in_rFormat.uSampleRate);

    return AK_Success;
}

AKRESULT SpaceDroneSource::Term(AK::IAkPluginMemAlloc* in_pAllocator)
{
    AK_PLUGIN_DELETE(in_pAllocator, this);
    return AK_Success;
}

AKRESULT SpaceDroneSource::Reset()
{
    return AK_Success;
}

AKRESULT SpaceDroneSource::GetPluginInfo(AkPluginInfo& out_rPluginInfo)
{
    out_rPluginInfo.eType = AkPluginTypeSource;
    out_rPluginInfo.bIsInPlace = true;
    out_rPluginInfo.uBuildVersion = AK_WWISESDK_VERSION_COMBINED;
    return AK_Success;
}

void SpaceDroneSource::Execute(AkAudioBuffer* out_pBuffer)
{
    AKPLATFORM::OutputDebugMsg(std::to_string(m_pParams->RTPC.fDensity).c_str());
    AKPLATFORM::OutputDebugMsg("\n");
    AKPLATFORM::OutputDebugMsg(std::to_string(m_pParams->RTPC.fRnd).c_str());
    AKPLATFORM::OutputDebugMsg("\n");
    AKPLATFORM::OutputDebugMsg(std::to_string(m_pParams->RTPC.fDynamic).c_str());
    AKPLATFORM::OutputDebugMsg("\n");

    mGeiger.process(m_pParams->RTPC.fDensity, m_pParams->RTPC.fRnd, m_pParams->RTPC.fDynamic);

    m_durationHandler.SetDuration(m_pParams->RTPC.fDuration);
    m_durationHandler.ProduceBuffer(out_pBuffer);

    const AkUInt32 uNumChannels = out_pBuffer->NumChannels();

    AkUInt16 uFramesProduced;
    for (AkUInt32 i = 0; i < uNumChannels; ++i)
    {
        AkReal32* AK_RESTRICT pBuf = (AkReal32* AK_RESTRICT)out_pBuffer->GetChannel(i);

        uFramesProduced = 0;
        while (uFramesProduced < out_pBuffer->uValidFrames)
        {
            float amplitude = 0.5f;  // Adjust this value as needed
            *pBuf++ = amplitude * ((2.0f * (float)rand() / RAND_MAX) - 1.0f);
            ++uFramesProduced;
        }
    }
}

AkReal32 SpaceDroneSource::GetDuration() const
{
    return m_durationHandler.GetDuration() * 1000.0f;
}

