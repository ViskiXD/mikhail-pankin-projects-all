# Interactive Audio-Visual Projects by Mikhail Pankin

*Three experimental projects exploring the intersection of physical interaction, spatial audio processing, and creative performance tools.*

![MIT License](https://img.shields.io/badge/license-MIT-blue.svg)
![Unity 6000.0.50f1](https://img.shields.io/badge/Unity-6000.0.50f1-black.svg)
![RNBO](https://img.shields.io/badge/RNBO-Audio%20Plugin-orange.svg)

## Table of Contents

- [What's Inside](#whats-inside)
- [Signal Flow Overview](#signal-flow-overview)
- [Quick Demos](#quick-demos)
- [Installation & Setup](#installation--setup)
- [Controls & Interaction](#controls--interaction)
- [Tech Stack & Files](#tech-stack--files)
- [Design Notes](#design-notes-why-this-matters)
- [Roadmap](#roadmap)
- [How to Contribute / Exhibit](#how-to-contribute--exhibit)
- [License & Credits](#license--credits)

## What's Inside

### 🥣 [Tiny Soup](TinySoup_MikhailPankin/)
Unity interactive installation featuring a floating bowl controlled via keyboard or DualSense controller. Spawn planets that collide and trigger pitched Buchla tones, all processed through real-time Space Echo effects with 4 switchable ambient tracks.

### 🎚️ [Extra Echo](ExtraEcho_MikhailPankin/) 
Max/RNBO-based Space Echo inspired audio effect with tape noise removed, expanded feedback controls, and per-head gain. Built as a modular platform for deeper parameter control beyond traditional RE-201 emulations.

### 🎵 [GRE](GRE_MikhailPankin%20Project/)
Granular composition demonstrating the creative feedback loop: source fragments processed through Arturia Pigments granular synthesis, then polished using Extra Echo—proving how custom tools feed back into musical creation.

## Signal Flow Overview

### Tiny Soup Interactive Chain
```
Controller Input (Keyboard/DualSense) 
    ↓
Bowl Tilt Physics (±25° max)
    ↓
Planet Spawning & Collision Detection
    ↓
Buchla Tone Triggering (9 pitched samples)
    ↓
Space Echo Processing (Echo Rate/Feedback/Reverb → Tilt)
    ↓
Audio Mixer Output + Background Music
```

### Extra Echo Processing Chain
```
Audio Input
    ↓
Multi-Head Tape Echo Simulation
    ├── Head 1 Gain Control
    ├── Head 2 Gain Control  
    └── Head 3 Gain Control
    ↓
Feedback Network (expanded from RE-201)
    ↓
Integrated Reverb Processing
    ↓
Wet/Dry Mix → Output
```

## Quick Demos

### Media Overview
| Project | Screenshots | Audio | Video |
|---------|-------------|-------|-------|
| **Tiny Soup** | *(Unity project - no screenshots in repo)* | [Buchla Samples](TinySoup_MikhailPankin/Soup%203/Assets/Music/) | [Demo Video](TinySoup_MikhailPankin/Запись%20экрана%202025-08-27%20в%2015.22.21-Apple%20Devices%20HD%20(Most%20Compatible).m4v) |
| **Extra Echo** | ![Screenshot 1](ExtraEcho_MikhailPankin/Снимок%20экрана%202025-08-27%20в%2015.12.55.png) ![Screenshot 2](ExtraEcho_MikhailPankin/Снимок%20экрана%202025-08-27%20в%2015.13.11.png) | *(Max/RNBO Project)* | - |
| **GRE** | ![Screenshot 1](GRE_MikhailPankin%20Project/Снимок%20экрана%202025-08-27%20в%2015.01.37.png) ![Screenshot 2](GRE_MikhailPankin%20Project/Снимок%20экрана%202025-08-27%20в%2015.14.34.png) | [Final Composition](GRE_MikhailPankin%20Project/GRE_MikhailPankin.mp3) | - |

<details>
<summary>📂 Background Music Tracks (Tiny Soup)</summary>

- [Track 1](TinySoup_MikhailPankin/Soup%203/Assets/Music/Track%201.wav)
- [Track 2](TinySoup_MikhailPankin/Soup%203/Assets/Music/Track%202.wav) 
- [Track 3](TinySoup_MikhailPankin/Soup%203/Assets/Music/Track%203.wav)
- [Track 4](TinySoup_MikhailPankin/Soup%203/Assets/Music/Track%204.wav)
- [Buchla Samples 1-9](TinySoup_MikhailPankin/Soup%203/Assets/Music/) (Untitled 1-9-Buchla Easel V.wav)
</details>

## Installation & Setup

### Tiny Soup (Unity 6000.0.50f1)
```bash
# 1. Open Unity Hub and select "Open Project"
# 2. Navigate to: TinySoup_MikhailPankin/Soup 3/
# 3. Unity will automatically import packages and build libraries
# 4. Open scene: Assets/Scenes/Main Scene.unity
# 5. Enter Play Mode

# Input Requirements:
# - Keyboard (WASD + Q for track switching)
# - Sony DualSense Controller (optional, for gyro tilt)
```

**Controls:**
- `W/A/S/D` → Bowl tilt (forward/left/back/right)
- `Space` → Spawn random planet
- `Q` → Switch background music track
- `R` (context menu) → Reset bowl and simulation
- **DualSense:** Right stick for tilt, R2/L2 for spawn/remove, R1 for next track

### Extra Echo (Max/RNBO)
```bash
# Dependencies: Max 9+ with RNBO package
# Version tested: Max 9+ / RNBO (latest)

# 1. Open Max/MSP
# 2. Navigate to ExtraEcho_MikhailPankin/ folder
# 3. Open the main project file (refer to project screenshots for UI)
# 4. Use RNBO export features for plugin creation
```

**Export Options:** 
- VST3/AU plugin export via RNBO export sidebar
- Standalone application export
- Unity Audio Plugin (SpaceEcho.bundle included for macOS)

### GRE Composition
```bash
# Audition the final composition:
open "GRE_MikhailPankin Project/GRE_MikhailPankin.mp3"

# The composition demonstrates the complete workflow from 
# granular synthesis to final processing with Extra Echo
```

## Controls & Interaction

### Tiny Soup Interactive Parameters
| Control | Function | Range/Notes |
|---------|----------|-------------|
| **Bowl Tilt** | WASD keys or DualSense stick | ±25° maximum angle |
| **Planet Spawn** | Spacebar or R2 trigger | Physics-enabled collision objects |
| **Music Track** | Q key or R1 shoulder | 4 ambient tracks with crossfade |
| **Echo Mapping** | Automatic tilt → effect | Rate/Feedback/Reverb scale with tilt angle |

**Real-time Audio Parameters:**
- `Echo_Rate`: 0.0 → 0.8 (mapped to tilt magnitude)
- `FeedBack`: 0.0 → 0.7 (mapped to tilt magnitude)  
- `Reverb_Gain`: 0.0 → 0.5 (mapped to tilt magnitude)

### Extra Echo Core Parameters
| Parameter | Type | Function |
|-----------|------|----------|
| **Multi-Head Gains** | Float (0-1) | Individual control per tape head |
| **Feedback Amount** | Float (0-1) | Extended beyond traditional RE-201 range |
| **Echo Rate/Time** | Float | Tape speed simulation |
| **Reverb Integration** | Float (0-1) | Built-in spatial processing |
| **Wet/Dry Mix** | Float (0-1) | Output blend control |

*Note: Parameter names detected from RNBO Unity integration. Actual Max interface may differ.*

## Tech Stack & Files

### Unity Project (Tiny Soup)
- **Unity Version:** 6000.0.50f1
- **Key Scripts:**
  - `BowlTiltController.cs` → Physics and input handling
  - `DualSenseControllerInput.cs` → Controller integration  
  - `SpaceEchoTiltController.cs` → Real-time effect parameter mapping
  - `PlanetAudio.cs` → Collision sound triggering
  - `MusicManager.cs` → Background track management

### RNBO Audio Integration
- **RNBO Types Package:** v0.0.2
- **SpaceEcho Plugin:** Unity-compatible native audio plugin
- **Generated Code:** `SpaceEchoHelper.cs` for parameter control
- **Native Library:** `SpaceEcho.bundle` (macOS Darwin)

### Project Directory Structure
```
mikhail-pankin-projects/
├── TinySoup_MikhailPankin/          # Unity installation + RNBO integration
│   ├── Soup 3/                     # Main Unity project
│   ├── C++export/                  # RNBO C++ source export
│   ├── rnbo.unity.audioplugin-main/ # RNBO Unity plugin framework
│   └── Plugins/                    # Audio plugin source files
├── ExtraEcho_MikhailPankin/         # Max/RNBO project + screenshots
└── GRE_MikhailPankin Project/       # Composition files + media
```

## Design Notes (Why This Matters)

• **Playful Interaction:** Physical gesture (bowl tilting) directly controls abstract audio parameters, creating intuitive sonic exploration beyond traditional knob-based interfaces.

• **User-Driven Emergence:** Planet collision timing is unpredictable, generating unique rhythmic patterns that emerge from physics rather than programmed sequences.

• **Prototypes → Instruments:** Extra Echo demonstrates how experimental audio tools can evolve into polished creative instruments, filling gaps left by traditional emulations.

• **Modern UI/UX Goals:** Moving beyond skeuomorphic tape machine interfaces toward modular, parameter-focused control that matches contemporary production workflows (FabFilter Pro-Q3, UAD Console, Arturia V Collection).

• **Cultural Ripple Effects:** Custom tool development creates feedback loops—artists build tools that influence their music, which influences future tool development, expanding the sonic palette beyond commercial limitations.

• **Real-time Performance:** Bowl tilt → echo parameters creates performative potential, turning the installation into a playable instrument rather than static demonstration.

• **Cross-Platform Thinking:** RNBO export enables the same audio processing to work in Unity, Max, and as traditional audio plugins, demonstrating platform-agnostic audio development.

## Roadmap

### Tiny Soup v2
- [ ] Input preset system (save/load tilt-to-parameter mappings)
- [ ] Visual polish: particle effects for planet collisions
- [ ] Performance optimizations for large planet counts
- [ ] Additional controller support (Xbox, generic HID)

### Extra Echo → Modular Platform  
- [ ] Expose all internal parameters via Max UI
- [ ] Preset management system
- [ ] Multiple tape head configurations (2-head, 4-head modes)
- [ ] Integration with popular DAWs via plugin export
- [ ] Advanced modulation routing (LFO, envelope followers)

### GRE Composition Series
- [ ] Complete liner notes documenting signal chain
- [ ] Release on streaming platforms  
- [ ] Additional compositions exploring Extra Echo variations
- [ ] Performance documentation (live coding sessions)

## How to Contribute / Exhibit

### Development Contributions
- **Issues & PRs:** Open issues for bugs or feature requests
- **Code Style:** Follow Unity C# conventions and Max/RNBO best practices
- **Testing:** Include performance notes for hardware-specific features (DualSense, audio latency)

### Exhibition Requests
- **Hardware Requirements:** 
  - Unity-capable machine (Windows/macOS)
  - Sony DualSense controller (for full interaction)
  - Audio interface + speakers/headphones
  - Optional: Large display for public installation

- **Contact:** Submit exhibition proposals via GitHub issues with venue details and technical rider requirements.

### Performance Setup
- **Minimum Specs:** Unity 6000.0.50f1, 4GB RAM, integrated audio
- **Recommended:** Dedicated GPU, low-latency audio interface, studio monitors
- **Controller Testing:** DualSense features may vary by platform—test beforehand

## License & Credits

### License
MIT License - see [LICENSE](LICENSE) file for details.

### Credits
- **Buchla Recordings:** All Buchla Easel V samples recorded by Mikhail Pankin
- **Unity Assets:** iPoly3D Low Poly Planets Pack, Space Skybox Pack, Tableware assets
- **RNBO Framework:** Cycling '74 RNBO Unity Audio Plugin framework
- **Audio Tools:** Arturia Pigments granular synthesis (GRE composition)

### Acknowledgments
Special thanks to the Max/MSP and Unity communities for cross-platform audio development resources, and to contemporary tool builders pushing beyond traditional audio software paradigms.

---

*Built with curiosity for interactive sound design, experimental interfaces, and the feedback loops between tools and music.*
