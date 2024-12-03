#ifndef NDIMEDIA_SINK_H
#define NDIMEDIA_SINK_H

#include <mfidl.h>
#include <mfapi.h>
#include <Processing.NDI.Lib.h>
#include <iostream>

class NDIMediaSink : public IMFMediaSink {
public:
    NDIMediaSink();
    ~NDIMediaSink();

    HRESULT STDMETHODCALLTYPE AddStreamSink(
        DWORD dwStreamSinkIdentifier,
        IMFMediaType* pMediaType,
        IMFStreamSink** ppStreamSink
    ) override;

    HRESULT STDMETHODCALLTYPE StartStreaming() override;
    HRESULT STDMETHODCALLTYPE Shutdown() override;

    // Outros métodos obrigatórios de IMFMediaSink
    HRESULT STDMETHODCALLTYPE RemoveStreamSink(DWORD dwStreamSinkIdentifier) override;
    HRESULT STDMETHODCALLTYPE GetCharacteristics(DWORD* pdwCharacteristics) override;
    HRESULT STDMETHODCALLTYPE GetStreamSinkCount(DWORD* pcStreamSinkCount) override;
    HRESULT STDMETHODCALLTYPE GetStreamSinkByIndex(DWORD dwIndex, IMFStreamSink** ppStreamSink) override;
    HRESULT STDMETHODCALLTYPE GetStreamSinkById(DWORD dwStreamSinkIdentifier, IMFStreamSink** ppStreamSink) override;

private:
    LONG m_refCount;
    DWORD m_streamSinkCount;
    NDIlib_send_instance_t m_NDISender;
};

#endif // NDIMEDIA_SINK_H
#pragma once
