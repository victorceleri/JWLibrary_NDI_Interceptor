#include <iostream>
#include "sinks/NDIMediaSink.h"

int main() {
    std::cout << "Starting JWLibrary NDI Interceptor..." << std::endl;

    NDIMediaSink mediaSink;
    mediaSink.StartStreaming();

    std::cout << "Interceptor running. Press any key to exit." << std::endl;
    char exitKey = getchar(); // Armazena o valor de retorno
    (void)exitKey; // Opcional, se você quiser indicar que o valor não será usado
}
