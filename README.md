# 6DoF-FMU

Build FMI (functional mock-up interface) models for co-simulation in modern C++

Models built under this repo are to be used for dynamic 6-DoF modeling of aerospace vehicles.

This repo is built on top of "FMU4CPP" repository for building the FMU models, and uses "libode" repository for incorporating the ODE solver into the FMU.

# FMU4cpp (early prototype)

FMU4cpp is a CMake template repository that allows you to easily create cross-platform FMUs 
compatible with [FMI 2.0](https://fmi-standard.org/downloads/) for Co-simulation using C++.

The framework generates the required `modelDescription.xml` and further packages 
the necessary content into a ready-to-use FMU archive.

### How do I get started?

1. Change the value of the `modelIdentifier` variable in `CMakeLists.txt` to something more appropriate.
2. Edit the content of [model.cpp](src/model.cpp).
3. Build.

An FMU named `<modelIdentifier>.fmu` is now located in your build folder.

#### Cross-compilation

Cross-compilation (64-bit linux/windows) occurs automatically when you push your changes to GitHub. 
Simply rename the produced `model.zip` to `<modelName>.fmu`.

Such easy, such wow.

### Requirements
* C++20 compiler
* CMake >= 3.15