# Tiny Soup - Interactive Bowl Physics Installation

*Unity-based interactive installation where bowl tilting spawns planets, triggers Buchla tones, and modulates Space Echo parameters in real-time.*

![Unity 6000.0.50f1](https://img.shields.io/badge/Unity-6000.0.50f1-black.svg)
![RNBO Audio](https://img.shields.io/badge/RNBO-Audio%20Processing-orange.svg)

## Quick Start

### Prerequisites
- **Unity 6000.0.50f1** (exact version required)
- **Input:** Keyboard + optional Sony DualSense controller
- **Audio:** Built-in audio or dedicated interface recommended

### Setup Steps
```bash
# 1. Open Unity Hub
# 2. Add project from disk: "Soup 3/" folder
# 3. Let Unity import packages and compile RNBO plugins
# 4. Open: Assets/Scenes/Main Scene.unity
# 5. Press Play and start tilting!
```

### First Time Run
- Scene loads with floating bowl in space environment
- Press `Space` to spawn your first planet
- Use `WASD` to tilt the bowl and watch physics interact
- Listen as collisions trigger pitched Buchla tones
- Notice how tilt angle modulates the Space Echo effect

## Controls & Input Mapping

### Keyboard Controls
| Key | Function | Notes |
|-----|----------|-------|
| `W` | Tilt bowl forward | Max ±25° angle |
| `S` | Tilt bowl backward | Smooth interpolation |
| `A` | Tilt bowl left | Physics affects planet motion |
| `D` | Tilt bowl right | Real-time echo parameter mapping |
| `Space` | Spawn random planet | Physics-enabled collision object |
| `Q` | Next background track | 4 ambient tracks with crossfade |
| `R` (Context Menu) | Reset simulation | Clears planets, resets bowl position |

### DualSense Controller (PlayStation 5)
| Input | Function | Implementation Notes |
|-------|----------|---------------------|
| **Right Stick** | Bowl tilt control | Fallback for gyro (Unity desktop limitation) |
| **R2 Trigger** | Spawn planet | Pressure sensitive |
| **L2 Trigger** | Remove one planet | Reverse spawning |
| **R1 Shoulder** | Next music track | Same as Q key |
| **Gyro/Accelerometer** | *Not implemented* | Unity doesn't expose DualSense gyro on desktop |

## Audio System

### Buchla Samples & Collision Detection
- **Sample Pool:** 9 pitched Buchla Easel V recordings (`Untitled 1-9-Buchla Easel V.wav`)
- **Trigger Logic:** Planet-to-planet collision detection
- **Cooldown:** 0.15s minimum between collision sounds (prevents rapid retriggering)
- **Spatial Audio:** 3D positioned audio sources with logarithmic rolloff
- **Velocity Threshold:** Minimum collision speed required for sound trigger

### Space Echo Real-Time Parameter Mapping
The bowl tilt angle directly controls Space Echo parameters through the RNBO integration:

```csharp
// Tilt magnitude calculation
float tiltMagnitude = Vector2(tilt.x, tilt.z).magnitude / maxTiltAngle;

// Parameter mapping (0.0 to 1.0 normalized)
Echo_Rate    → tiltMagnitude * 0.8    // Tape speed simulation  
FeedBack     → tiltMagnitude * 0.7    // Echo repeat amount
Reverb_Gain  → tiltMagnitude * 0.5    // Spatial reverb blend
```

### Background Music System
- **4 Ambient Tracks:** Looping background music (`Track 1-4.wav`)
- **Crossfade Duration:** 2 seconds between track switches  
- **Volume Control:** Per-track volume adjustment
- **Persistence:** Music continues across scene reloads

## Performance & Optimization

### Recommended Specs
- **Unity Version:** 6000.0.50f1 (tested)
- **RAM:** 4GB minimum, 8GB+ recommended for complex scenes
- **Audio:** Dedicated audio interface for low-latency performance
- **Display:** Any resolution (scales to fit)

### Performance Tips
```csharp
// Planet count affects performance
// Recommended limits:
// - Desktop: 50+ planets (physics-limited)
// - Mobile: 20-30 planets  
// - VR: 15-20 planets (framerate critical)
```

### Known Performance Considerations
- **Physics Simulation:** More planets = higher CPU usage
- **Audio Processing:** RNBO effects add DSP load
- **Spatial Audio:** 3D audio sources scale with planet count
- **Memory:** Large audio files loaded at startup

## Architecture & Code Structure

### Core Scripts
```
Assets/Scripts/
├── BowlTiltController.cs        # Main tilt physics & input
├── Input/
│   └── DualSenseControllerInput.cs # PlayStation 5 controller support
├── Audio/
│   ├── MusicManager.cs          # Background track management
│   ├── PlanetAudio.cs          # Collision sound triggering  
│   ├── SpaceEchoTiltController.cs # Real-time effect parameter mapping
│   └── RNBOAudioFilter.cs      # RNBO integration wrapper
└── [Additional simulation scripts]
```

### Key Components Interaction
1. **BowlTiltController** reads input and applies physics
2. **SpaceEchoTiltController** reads tilt state and maps to audio parameters
3. **PlanetAudio** handles collision detection and sound triggering
4. **MusicManager** provides ambient background independent of interaction

### RNBO Integration Details
- **Package:** `com.cycling74.spaceecho` (v0.0.1)
- **Native Plugin:** `SpaceEcho.bundle` (macOS) or equivalent platform library
- **Parameter Access:** Direct C# binding to RNBO parameter system
- **Real-time Control:** Frame-rate audio parameter updates

## Troubleshooting

### Common Issues

#### RNBO Plugin Not Loading
```bash
# Symptoms: No echo effect, parameter mapping fails
# Solutions:
1. Verify Unity version matches exactly (6000.0.50f1)
2. Check console for native plugin load errors
3. Ensure platform-specific plugin exists (SpaceEcho.bundle for macOS)
4. Try re-importing RNBO packages via Package Manager
```

#### DualSense Controller Not Detected  
```bash
# Symptoms: Keyboard works, controller doesn't respond
# Solutions:
1. Enable "New Input System" in Player Settings
2. Install "Input System" package via Package Manager  
3. Connect controller before starting Unity
4. Check Windows: Install DS4Windows or official Sony drivers
```

#### Audio Dropouts or Clicks
```bash
# Symptoms: Stuttering audio, especially during heavy interaction
# Solutions:
1. Increase audio buffer size in Project Settings > Audio
2. Close other audio applications
3. Use dedicated audio interface if available
4. Reduce planet count if performance-limited
```

#### Missing Audio Files
```bash
# Symptoms: Silence during collisions or track switching
# Verify audio files are present in project:
Assets/Music/Track [1-4].wav
Assets/Music/Untitled [1-9]-Buchla Easel V.wav
# Re-import audio files if necessary
```

## Development Notes

### Extending Controls
To add new input mappings, modify `DualSenseControllerInput.cs`:
```csharp
// Example: Adding triangle button for special function
bool triangle = gp.triangleButton.isPressed;
if (triangle && !triangleWasPressed) {
    // Your custom function here
}
triangleWasPressed = triangle;
```

### Adding Audio Parameters
To map additional RNBO parameters, extend `SpaceEchoTiltController.cs`:
```csharp
// 1. Add parameter index discovery in Start()
wetDryIndex = SpaceEchoHandle.GetFirstParamIndexByName("WetDry");

// 2. Add parameter setting in Update()  
if (wetDryIndex.HasValue) {
    handle.SetParamValueNormalized(wetDryIndex.Value, yourMappingFunction);
}
```

### Custom Planet Types
Create new planet prefabs by:
1. Adding `PlanetAudio` component
2. Assigning unique collision sound
3. Setting `AudioMixerGroup` for effect routing
4. Configuring collision detection layer

## Media Files

### Audio Assets
- **Background Music:** `Assets/Music/Track 1-4.wav`
- **Buchla Samples:** `Assets/Music/Untitled 1-9-Buchla Easel V.wav`  
- **Demo Video:** [Installation Demo](../Запись%20экрана%202025-08-27%20в%2015.22.21-Apple%20Devices%20HD%20(Most%20Compatible).m4v)

### Visual Assets
- **Planet Models:** iPoly3D Low Poly Planets Pack (included)
- **Space Environment:** Space Skybox Pack with multiple nebula variations
- **Tableware:** Bowl and kitchen items from Tableware asset pack

## Future Development

### Planned Features
- [ ] **Input Presets:** Save/load custom tilt-to-parameter mappings
- [ ] **Visual Feedback:** Particle effects for collision events
- [ ] **Multi-Controller:** Support multiple DualSense controllers
- [ ] **Recording:** Export audio sessions for later review
- [ ] **VR Support:** Adapt for hand-tracking or VR controllers

### Experimental Ideas
- [ ] **AI Planets:** Machine learning-driven collision behavior
- [ ] **Network Sync:** Multi-user installations with shared bowl state
- [ ] **MIDI Output:** Send tilt data to external hardware/software
- [ ] **Computer Vision:** Replace controller with camera-based gesture recognition

---

*Part of the Interactive Audio-Visual Projects collection by Mikhail Pankin.*
