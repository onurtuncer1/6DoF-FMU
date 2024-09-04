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

#include <fmu4cpp/fmu_base.hpp>
#include "EarthCenteredFrames.h"

using namespace fmu4cpp;

class Model : public fmu_base {

public:
    Model(const std::string &instanceName, const std::string &resources)
        : fmu_base(instanceName, resources) {

        register_variable(
                real(
                        "ec", [this] { return m_Tim; }, [this](double value) { m_ = value; })
                        .setCausality(causality_t::INPUT)
                        .setVariability(variability_t::CONTINUOUS));
    
        register_variable(
                real(
                        "ecef_rx", [this] { return m_EcefRx; }, [this](double value) { m_EcefRx = value; })
                        .setCausality(causality_t::INPUT)
                        .setVariability(variability_t::CONTINUOUS));

        register_variable(
                real(
                        "ecef_rx", [this] { return m_EcefRx; }, [this](double value) { m_EcefRx = value; })
                        .setCausality(causality_t::INPUT)
                        .setVariability(variability_t::CONTINUOUS));

        register_variable(
                real(
                        "ecef_rx", [this] { return m_EcefRx; }, [this](double value) { m_EcefRx = value; })
                        .setCausality(causality_t::INPUT)
                        .setVariability(variability_t::CONTINUOUS));

        
        register_variable(
                real(
                        "ecef_rx", [this] { return m_EcefRx; }, [this](double value) { m_EcefRx = value; })
                        .setCausality(causality_t::INPUT)
                        .setVariability(variability_t::CONTINUOUS));

        register_variable(
                real(
                        "ecef_rx", [this] { return m_EcefRx; }, [this](double value) { m_EcefRx = value; })
                        .setCausality(causality_t::INPUT)
                        .setVariability(variability_t::CONTINUOUS));

        register_variable(
                real(
                        "ecef_rx", [this] { return m_EcefRx; }, [this](double value) { m_EcefRx = value; })
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
        
         try{
            
            return true;
        }catch(...){
            return false;
        } 
    }

    void reset() override {
      m_EcefRx = 0;
    }

private:
    double m_EcefRx;
    double m_EcefRy;
    double m_EcefRz;
    double m_EcefVx;
    double m_EcefVy;
    double m_EcefVz;
    double m_TimeSinceEpoch;
    double m_EciRx;
    double m_EciRy;
    double m_EciRz;
    double m_EciVx;
    double m_EciVy;
    double m_EciVz;
};

model_info fmu4cpp::get_model_info() {
    model_info info;
    info.modelName = "ECEF2ECI";
    info.description = "Convert position and velocity from ECEF to ECI frame";
    info.modelIdentifier = FMU4CPP_MODEL_IDENTIFIER;
    return info;
}

std::unique_ptr<fmu_base> fmu4cpp::createInstance(const std::string &instanceName, const std::string &fmuResourceLocation) {
    return std::make_unique<Model>(instanceName, fmuResourceLocation);
}