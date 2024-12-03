#include <mfidl.h>
#include <mfapi.h>
#include <Processing.NDI.Lib.h>
#include <iostream>

class NDIMediaSink : public IMFMediaSink {
public:
    NDIMediaSink() : m_refCount(1), m_streamSinkCount(0), m_NDISender(nullptr) {
        if (NDIlib_initialize()) {
            std::cout << "NDI Initialized successfully!" << std::endl;
        }
        else {
            std::cerr << "NDI Initialization failed!" << std::endl;
        }
    }

    ~NDIMediaSink() {
        if (m_NDISender) {
            NDIlib_send_destroy(m_NDISender);
        }
        NDIlib_destroy();
    }

    HRESULT STDMETHODCALLTYPE AddStreamSink(
        DWORD dwStreamSinkIdentifier,
        IMFMediaType* pMediaType,
        IMFStreamSink** ppStreamSink
    ) override {
        *ppStreamSink = nullptr; // Adicione lógica real aqui
        m_streamSinkCount++;
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE RemoveStreamSink(DWORD dwStreamSinkIdentifier) override {
        // Lógica para remover stream sink
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE GetCharacteristics(DWORD* pdwCharacteristics) override {
        *pdwCharacteristics = 0; // Defina os caracteres necessários
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE GetStreamSinkCount(DWORD* pcStreamSinkCount) override {
        *pcStreamSinkCount = m_streamSinkCount;
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE GetStreamSinkByIndex(DWORD dwIndex, IMFStreamSink** ppStreamSink) override {
        *ppStreamSink = nullptr; // Lógica para obter stream sink por índice
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE GetStreamSinkById(DWORD dwStreamSinkIdentifier, IMFStreamSink** ppStreamSink) override {
        *ppStreamSink = nullptr; // Lógica para obter stream sink por ID
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE StartStreaming() override {
        std::cout << "Starting NDI Streaming..." << std::endl;

        NDIlib_send_create_t createDesc;
        createDesc.p_groups = "NDI";
        createDesc.color_format = NDIlib_recv_color_format_BGRX_BGRA;
        createDesc.p_tcp_address = nullptr;

        m_NDISender = NDIlib_send_create(&createDesc);

        if (!m_NDISender) {
            std::cerr << "Failed to create NDI sender instance!" << std::endl;
            return E_FAIL;
        }

        std::cout << "NDI Streaming started successfully!" << std::endl;
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE Shutdown() override {
        if (m_NDISender) {
            NDIlib_send_destroy(m_NDISender);
            m_NDISender = nullptr;
        }
        return S_OK;
    }

private:
    LONG m_refCount;
    DWORD m_streamSinkCount;
    NDIlib_send_instance_t m_NDISender;
};