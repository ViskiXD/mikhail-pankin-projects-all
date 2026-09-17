// Standalone smoke test for the RNBO "Space Echo" C++ export.
//
// It links the exported DSP (Space Echo.cpp + RNBO.cpp), instantiates the
// audio engine, drives an impulse through it, and checks that the effect
// produces a delayed/feedback tail. This verifies the cross-platform RNBO
// audio pipeline compiles AND actually runs, without needing Unity/Max.

#include "RNBO.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>

using namespace RNBO;

int main() {
    CoreObject core;

    const double sampleRate = 48000.0;
    const Index blockSize = 256;

    if (!core.prepareToProcess(sampleRate, blockSize)) {
        std::fprintf(stderr, "prepareToProcess failed\n");
        return 1;
    }

    const Index numIn = core.getNumInputChannels();
    const Index numOut = core.getNumOutputChannels();
    const ParameterIndex numParams = core.getNumParameters();

    std::printf("Space Echo engine initialized\n");
    std::printf("  sampleRate   = %.0f Hz\n", sampleRate);
    std::printf("  blockSize    = %zu\n", (size_t)blockSize);
    std::printf("  inputs       = %zu\n", (size_t)numIn);
    std::printf("  outputs      = %zu\n", (size_t)numOut);
    std::printf("  parameters   = %zu\n", (size_t)numParams);
    std::printf("\nParameters:\n");
    for (ParameterIndex i = 0; i < numParams; ++i) {
        std::printf("  [%2zu] %-24s = %.4f\n", (size_t)i,
                    core.getParameterName(i), core.getParameterValue(i));
    }

    // Configure an audible echo: pick delay/feedback/reverb-ish params by name.
    for (ParameterIndex i = 0; i < numParams; ++i) {
        const char* name = core.getParameterName(i);
        std::string n(name ? name : "");
        if (n == "Echo_Rate" || n == "FeedBack" || n == "Reverb_Gain" ||
            n.find("Head") != std::string::npos) {
            core.setParameterValueNormalized(i, 0.6);
        }
    }

    if (numIn == 0 || numOut == 0) {
        std::fprintf(stderr, "engine reports no audio channels\n");
        return 1;
    }

    // Allocate non-interleaved buffers.
    std::vector<std::vector<SampleValue>> inStore(numIn, std::vector<SampleValue>(blockSize, 0.0));
    std::vector<std::vector<SampleValue>> outStore(numOut, std::vector<SampleValue>(blockSize, 0.0));
    std::vector<SampleValue*> inPtrs(numIn), outPtrs(numOut);
    for (Index c = 0; c < numIn; ++c) inPtrs[c] = inStore[c].data();
    for (Index c = 0; c < numOut; ++c) outPtrs[c] = outStore[c].data();

    // Run ~1 second of audio. First block carries a unit impulse on all inputs.
    const int numBlocks = (int)std::ceil(sampleRate / blockSize);
    double peakInputEnergy = 0.0;
    double maxTailAbs = 0.0;
    double totalTailEnergy = 0.0;

    for (int b = 0; b < numBlocks; ++b) {
        for (Index c = 0; c < numIn; ++c) {
            std::fill(inStore[c].begin(), inStore[c].end(), 0.0);
            if (b == 0) inStore[c][0] = 1.0; // impulse
        }
        for (Index c = 0; c < numOut; ++c)
            std::fill(outStore[c].begin(), outStore[c].end(), 0.0);

        core.process(inPtrs.data(), numIn, outPtrs.data(), numOut, blockSize);

        for (Index c = 0; c < numOut; ++c) {
            for (Index s = 0; s < blockSize; ++s) {
                const double v = std::abs((double)outStore[c][s]);
                if (b == 0 && s < 8) peakInputEnergy = std::max(peakInputEnergy, v);
                // Tail = everything well after the initial impulse.
                if (b > 2) {
                    maxTailAbs = std::max(maxTailAbs, v);
                    totalTailEnergy += v * v;
                }
            }
        }
    }

    std::printf("\nProcessed %d blocks (%.2f s of audio)\n", numBlocks,
                (numBlocks * (double)blockSize) / sampleRate);
    std::printf("  initial impulse response peak = %.6f\n", peakInputEnergy);
    std::printf("  echo tail peak (after impulse) = %.6f\n", maxTailAbs);
    std::printf("  echo tail energy               = %.6f\n", totalTailEnergy);

    if (!(maxTailAbs > 1e-6) || !std::isfinite(totalTailEnergy)) {
        std::fprintf(stderr,
                     "\nFAIL: no finite echo tail produced by the effect\n");
        return 1;
    }

    std::printf("\nPASS: Space Echo produced a sustained echo/feedback tail.\n");
    return 0;
}
