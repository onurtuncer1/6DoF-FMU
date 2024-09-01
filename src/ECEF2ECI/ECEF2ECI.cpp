/*
 * -----------------------------------------------------------------------------------
 * Project:     [EBEK]
 * File:        [ECEF2ECI.cpp]
 * Author:      Prof.Dr. Onur Tuncer
 * Email:       onur.tuncer@itu.edu.tr
 * Institution: Istanbul Technical University
 *              Faculty of Aeronautics and Astronuatics
 * 
 * Date:        2024
 *
 * Description:
 * [Coordinate transformation from ECEF to ECI frame]
 *
 * License:
 * [See License.txt in the top level directory for licence and copyright information]
 *
 * -----------------------------------------------------------------------------------
 */

#include <utility>
#include <fmu4cpp/fmu_base.hpp>
#include "EarthCenteredFrames.h"

using namespace fmu4cpp;

class Model : public fmu_base {

public:
    Model(const std::string &instanceName, const std::string &resources)
        : fmu_base(instanceName, resources) {

        register_variable(
                real(
                        "Gain", [this] { return m_Gain; }, [this](double value) { m_Gain = value; })
                        .setCausality(causality_t::PARAMETER)
                        .setVariability(variability_t::FIXED));
    
        register_variable(
                real(
                        "Input", [this] { return m_Input; }, [this](double value) { m_Input = value; })
                        .setCausality(causality_t::INPUT)
                        .setVariability(variability_t::CONTINUOUS));
      
        register_variable(
                real(
                        "Output", [this] { return m_Output; })
                        .setCausality(causality_t::OUTPUT)
                        .setVariability(variability_t::CONTINUOUS)
                        .setDependencies({get_real_variable("Input")->index(),
                                          get_real_variable("Gain")->index()}));
     
        Model::reset();
    }

    bool do_step(double currentTime, double dt) override {
        m_Output = m_Input * m_Gain;
        return true;
    }

    void reset() override {
       m_Altitude = 0.0;
       m_Temperature = 1.0;
       m_Pressure = 0.0;
       m_Density = 0.0;
    }

private:
    double m_Input;
    double m_Output;
    double m_Gain;
};

model_info fmu4cpp::get_model_info() {
    model_info info;
    info.modelName = "AtmosphereUS1976";
    info.description = "A simple linear gain model";
    info.modelIdentifier = FMU4CPP_MODEL_IDENTIFIER;
    return info;
}

std::unique_ptr<fmu_base> fmu4cpp::createInstance(const std::string &instanceName, const std::string &fmuResourceLocation) {
    return std::make_unique<Model>(instanceName, fmuResourceLocation);
}