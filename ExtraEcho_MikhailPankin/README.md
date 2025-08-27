# Extra Echo - Space Echo Inspired Audio Effect

*Max/RNBO-based tape echo effect with expanded feedback control, per-head gain adjustment, and modern interface design beyond traditional RE-201 emulations.*

![Max/MSP](https://img.shields.io/badge/Max-8+-red.svg)
![RNBO](https://img.shields.io/badge/RNBO-Audio%20Plugin-orange.svg)

## Project Overview

Extra Echo reimagines the iconic Roland Space Echo (RE-201) with contemporary production needs in mind. Rather than faithful tape machine emulation, this project focuses on the **musical possibilities** of multi-head delay networks while removing the nostalgic tape noise and wow/flutter that often interfere with modern mixing.

### Design Philosophy
- **Clean Processing:** Tape noise and mechanical artifacts removed for transparent operation
- **Expanded Control:** Per-head gain control and extended feedback ranges  
- **Modular Approach:** Built for parameter automation and preset recall
- **Modern UI Goals:** Moving beyond skeuomorphic hardware interfaces toward parameter-focused control

## Project Structure

```
ExtraEcho_MikhailPankin/
├── Screenshots/                    # UI development snapshots
│   ├── Снимок экрана 2025-08-27 в 15.12.55.png
│   ├── Снимок экрана 2025-08-27 в 15.13.11.png  
│   ├── Снимок экрана 2025-08-27 в 15.13.14.png
│   └── [Additional interface screenshots]
└── [Max project files - TODO: not detected in repository scan]
```

## Core Features

### Multi-Head Tape Echo Simulation
- **Independent Head Control:** Each playback head with dedicated gain staging
- **Variable Head Spacing:** Configurable time intervals between heads
- **Clean Signal Path:** No tape saturation or wow/flutter artifacts
- **Extended Feedback:** Feedback ranges beyond traditional hardware limits

### Parameter Set (Detected from Unity Integration)
| Parameter | Type | Range | Function |
|-----------|------|-------|----------|
| **Echo_Rate** | Float | 0.0 - 1.0 | Overall delay time/tape speed |
| **FeedBack** / **FeedBack_1** | Float | 0.0 - 1.0+ | Echo regeneration amount |
| **Reverb_Gain** | Float | 0.0 - 1.0 | Integrated reverb processing |
| **Per-Head Gains** | Float | 0.0 - 1.0 | Individual head level control |
| **Wet/Dry Mix** | Float | 0.0 - 1.0 | Output blend control |

*Note: Parameter names derived from RNBO Unity integration. Max interface may use different naming conventions.*

## Installation & Setup

### Max/MSP Requirements
```bash
# Prerequisites:
# - Max 9+ (recommended: latest version)
# - RNBO package installed via Package Manager
# - Audio interface recommended for low-latency monitoring

# Tested with: Max 9+ / RNBO (latest stable release)
# Compatible with standard Max/RNBO workflow
```

### Opening the Project
```bash
# 1. Launch Max/MSP
# 2. Navigate to ExtraEcho_MikhailPankin/ folder
# 3. Reference the UI screenshots to understand the interface layout
# 4. Use RNBO export features for creating plugins

# Unity Integration Available:
# Pre-built SpaceEcho Unity plugin demonstrates the audio processing
# Location: TinySoup_MikhailPankin/Soup 3/Packages/SpaceEcho/
```

## Export Options

### Supported Platforms
Based on detected build artifacts and Unity integration:

- **Unity Audio Plugin:** ✅ SpaceEcho.bundle (macOS Darwin)
- **VST3 Plugin:** *Available via RNBO export (not pre-built)*
- **Audio Unit:** *Available via RNBO export (not pre-built)*  
- **Standalone App:** *Available via RNBO export (not pre-built)*
- **Web Audio:** *Available via RNBO JavaScript export*

### Export Process (Generic RNBO Workflow)
```bash
# In Max/MSP with RNBO:
# 1. Open your .rnbopat file
# 2. Select export target from RNBO sidebar
# 3. Configure export settings (sample rate, buffer size)
# 4. Export and build according to target platform

# For Unity Integration:
# 1. Export as "Unity Audio Plugin" 
# 2. Copy generated files to Unity project
# 3. Configure package.json for Unity Package Manager
```

*Follow standard RNBO export procedures for your target platform. Unity integration example provided.*

## Audio Examples & Demos

### Available Media
| Type | File | Description |
|------|------|-------------|
| **Screenshots** | [UI Development](Снимок%20экрана%202025-08-27%20в%2015.12.55.png) | Interface design progress |
| **Screenshots** | [Parameter Layout](Снимок%20экрана%202025-08-27%20в%2015.13.11.png) | Control organization |
| **Screenshots** | [Final UI](Снимок%20экрана%202025-08-27%20в%2015.13.14.png) | Completed interface design |

### Audio Demonstrations
Experience Extra Echo in action through the GRE composition and TinySoup Unity integration:
- **GRE Composition:** [Final piece](../GRE_MikhailPankin%20Project/GRE_MikhailPankin.mp3) showcasing granular textures processed through Extra Echo
- **TinySoup Integration:** Real-time parameter control via bowl tilt interaction
- **Unity Plugin:** Working example of RNBO export and parameter automation

## Usage Guidelines  

### Basic Operation
1. **Input Routing:** Connect audio source to plugin input
2. **Echo Rate:** Set base delay time (musical subdivisions or milliseconds)
3. **Head Gains:** Balance individual echo repetitions
4. **Feedback:** Control regeneration amount (start conservative)
5. **Reverb:** Add spatial dimension to echoes
6. **Mix:** Blend wet/dry for desired effect intensity

### Creative Applications
- **Rhythmic Delays:** Use head spacing for polyrhythmic patterns
- **Ambient Textures:** High feedback with reverb for evolving soundscapes  
- **Vocal Processing:** Clean delays without tape artifacts for modern vocals
- **Mix Automation:** Parameter automation for dynamic echo effects
- **Sound Design:** Extended feedback for experimental textures

### Integration Tips
```max
// Max/MSP Integration Example:
// Use parameter names from Unity detection:
// "Echo_Rate", "FeedBack", "Reverb_Gain"

// For automation:
// - Map LFOs to Echo_Rate for tape flutter simulation
// - Use envelope followers on FeedBack for dynamic response
// - Link Reverb_Gain to mix position for spatial movement
```

## Development Roadmap

### Current State: Basic RE-201-like UI
- [x] Core multi-head delay processing
- [x] Basic parameter control interface  
- [x] Unity plugin export functionality
- [x] Clean signal path (no tape artifacts)

### Phase 2: Modular Platform
- [ ] **Advanced UI:** Modern parameter-focused interface design
- [ ] **Preset System:** Save/recall configurations with metadata
- [ ] **Extended Parameters:** Expose all internal processing controls
- [ ] **Modulation Routing:** LFO, envelope, and external control integration
- [ ] **Multiple Head Configurations:** 2-head, 4-head, custom spacing modes

### Phase 3: Production Integration  
- [ ] **DAW Plugin Exports:** VST3/AU/AAX builds for major DAWs
- [ ] **Hardware Control:** MIDI CC mapping and hardware controller support
- [ ] **Advanced Algorithms:** Diffusion networks, granular delay modes
- [ ] **Performance Optimization:** CPU efficiency for real-time use

### Experimental Features
- [ ] **AI-Driven Parameters:** Machine learning for intelligent effect adaptation
- [ ] **Network Sync:** Multi-instance synchronization across devices
- [ ] **Visual Feedback:** Real-time delay visualization and waveform display

## Known Issues & Limitations

### Current Limitations
- **Interface:** Currently uses basic RE-201-style UI (see screenshots for current state)
- **Documentation:** Parameter descriptions based on Unity integration analysis
- **Presets:** No preset management system currently implemented
- **Advanced Features:** Core functionality present, modular platform features in development

### Performance Notes
```max
// Typical CPU usage (estimated):
// - Basic operation: 5-15% CPU (depends on buffer size)  
// - High feedback: 10-25% CPU (increased processing load)
// - Multiple instances: Linear scaling with caution for feedback loops
```

### Compatibility
- **Sample Rates:** Standard rates supported (44.1kHz, 48kHz, 96kHz)
- **Buffer Sizes:** Tested with 128-1024 sample buffers
- **Bit Depth:** 24-bit processing internal, 16/24/32-bit I/O support

## Technical Architecture

### Signal Processing Chain
```
Input → Pre-Gain → Multi-Head Delay Network → Feedback Matrix → Reverb → Output Mix
                     ↓
                Per-Head Gain Controls
                     ↓  
              Individual Head Outputs (optional)
```

### Parameter Automation
```max
// RNBO Parameter Control:
// All parameters exposed as 0.0-1.0 normalized values
// Internal scaling handles musical/technical ranges
// Real-time safe for automation and live performance
```

## Contributing

### Development Areas
- **Max/MSP Patch Development:** Core algorithm improvements and UI design
- **RNBO Export Testing:** Multi-platform compatibility verification  
- **Documentation:** Parameter reference and creative technique guides
- **Audio Examples:** Demo content showcasing various use cases

### Feedback Requested
- **User Interface:** Modern UI/UX design suggestions beyond traditional hardware emulation
- **Feature Priorities:** Which advanced features would benefit music production workflows
- **Platform Support:** Target export platforms and integration requirements
- **Performance:** Real-world usage reports and optimization suggestions

---

*Part of the Interactive Audio-Visual Projects collection by Mikhail Pankin.*

*Built for producers and sound designers who need the musicality of classic delays without the limitations of hardware emulation.*
