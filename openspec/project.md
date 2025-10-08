# Project Context

## Purpose
LabRecorder is the default recording application for the Lab Streaming Layer (LSL) ecosystem. It enables synchronized recording of multiple data streams from various devices and software on a lab network into a single XDF (Extensible Data Format) file, with precise time synchronization between all streams. This is critical for multi-modal data acquisition in neuroscience, psychology, and human-computer interaction research.

Key goals:
- Record all LSL streams on the network (or a selective subset) with time synchronization
- Support both GUI and command-line interfaces for different use cases
- Enable remote control for automated experiment workflows
- Maintain compatibility with BIDS (Brain Imaging Data Structure) naming conventions
- Provide robust error recovery and stream reconnection capabilities

## Tech Stack
- **C++17**: Core language for performance-critical recording operations
- **Qt 5/6**: Cross-platform GUI framework (Qt Widgets, Qt Network, Qt DBus)
- **Lab Streaming Layer (LSL)**: Real-time data streaming and synchronization library
- **CMake**: Build system with cross-platform support
- **XDF Format**: Open file format for synchronized multi-stream data storage
- **Boost** (optional): For compressed XDF file support (XDFZ)
- **Platform Support**: Windows, macOS, Linux (Ubuntu/Debian)

## Project Conventions

### Code Style
- C++17 standard with modern C++ practices
- Header files use `.h` extension, implementation files use `.cpp`
- Include guards use `#ifndef FILENAME_H` pattern
- Class names use PascalCase (e.g., `MainWindow`, `StreamItem`)
- Member variables use camelCase with trailing underscore for private members (e.g., `file_`, `offsets_enabled_`)
- Constants use snake_case (e.g., `boundary_interval`, `max_headers_wait`)
- Prefer `std::unique_ptr` and `std::shared_ptr` over raw pointers
- Use `noexcept` specifier where appropriate

### Architecture Patterns
- **Multi-threaded Recording Architecture**: Separate threads for each stream, boundary markers, and offset collection
- **Phase-based Recording**: Three coordinated phases (Headers → Streaming → Footers) to maintain file chunk ordering
- **RAII Pattern**: Resource management through constructors/destructors
- **Observer Pattern**: Qt signals/slots for UI event handling
- **Factory Pattern**: Stream inlet creation based on stream info
- **Template Metaprogramming**: Type-specific transfer loops for different data types

Key Components:
- `MainWindow`: Qt-based GUI controller
- `recording`: Core recording engine managing multiple threads
- `XDFWriter`: Thread-safe file writer for XDF format
- `tcpinterface`: Remote control socket interface

### Testing Strategy
- Unit tests for XDF writer functionality (`test_xdf_writer.cpp`)
- Platform-specific testing for endianness and IEEE 754 compliance
- Manual testing for multi-stream recording scenarios
- CI/CD pipeline for automated builds across platforms

### Git Workflow
- Feature branches with descriptive names (e.g., `feature/toggleable-console-window`)
- Main development on `master` branch
- GitHub releases for versioned binaries
- Semantic versioning (currently at v1.16.4)
- PR-based workflow with code review

## Domain Context

### Lab Streaming Layer (LSL)
LSL is a system for unified collection of measurement time series in research experiments. Key concepts:
- **Streams**: Named data sources with metadata (type, channel count, sampling rate)
- **Inlets/Outlets**: Consumer/producer endpoints for streams
- **Time Synchronization**: Network clock synchronization for sub-millisecond precision
- **Stream Resolution**: Dynamic discovery of available streams on the network

### XDF File Format
- Extensible Data Format designed for LSL
- Chunk-based structure with different chunk types:
  - FileHeader: Overall file metadata
  - StreamHeader: Per-stream configuration
  - Samples: Actual data with timestamps  
  - ClockOffset: Time synchronization information
  - Boundary: Recovery markers
  - StreamFooter: Per-stream summary

### BIDS Compatibility
Support for Brain Imaging Data Structure naming conventions:
- Participant labels (`%p`)
- Session labels (`%s`)
- Task/block labels (`%b`)
- Acquisition labels (`%a`)
- Run indices (`%r`)
- Modality types (eeg, ieeg, meg, beh)

## Important Constraints

### Technical Constraints
- Must handle network disconnections gracefully (6-minute buffer for reconnection)
- File chunks must be written in correct order for valid XDF files
- Real-time performance requirements for high-frequency data streams
- Cross-platform compatibility requirements
- Thread safety for concurrent stream recording

### Performance Constraints
- Chunk interval: 500ms for data polling
- Boundary markers: Every 10 seconds
- Offset measurements: Every 5 seconds
- Maximum wait times for various operations to prevent hangs

### Compatibility Constraints
- Must support both Qt5 and Qt6
- Windows requires Visual C++ Runtime Redistributable
- Different dependency management per platform (homebrew for macOS, apt for Linux)
- Must maintain backwards compatibility with existing XDF readers

## External Dependencies

### Required Dependencies
- **liblsl**: Lab Streaming Layer library (core dependency)
- **Qt Framework**: UI and networking functionality
- **C++ Standard Library**: Threading, I/O, containers
- **Platform-specific runtime libraries**

### Optional Dependencies
- **Boost.Iostreams**: For XDFZ (compressed XDF) support
- **Python/MATLAB**: For testing and data import (external tools)

### Build Tools
- **CMake** (>= 3.12): Build configuration
- **Compiler**: MSVC (Windows), GCC/Clang (Linux), Clang (macOS)
- **Platform SDKs**: Windows SDK, macOS SDK
- **Qt deployment tools**: windeployqt, macdeployqt

### Network Services
- TCP port 22345 (default) for remote control interface
- LSL multicast/unicast for stream discovery
- Local network access for inter-device communication