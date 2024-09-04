/*
 * -----------------------------------------------------------------------------------
 * Project:     [EBEK]
 * File:        [AtmosphereUS1976.cpp]
 * Author:      Prof.Dr. Onur Tuncer
 * Email:       onur.tuncer@itu.edu.tr
 * Institution: Istanbul Technical University
 *              Faculty of Aeronautics and Astronuatics
 * 
 * Date:        2024
 *
 * Description:
 * [US1976 Atmospheric Model]
 *
 * License:
 * [See License.txt in the top level directory for licence and copyright information]
 *
 * -----------------------------------------------------------------------------------
 */

#include <fmu4cpp/fmu_base.hpp>
#include "AtmosphericModels.h"

using namespace fmu4cpp;

class Model : public fmu_base {

public:
    Model(const std::string &instanceName, const std::string &resources)
        : fmu_base(instanceName, resources) {

        register_variable(
                real(
                        "Altitude", [this] { return m_Altitude; }, [this](double value) { m_Altitude = value; })
                        .setCausality(causality_t::INPUT)
                        .setVariability(variability_t::CONTINUOUS));
      
        register_variable(
                real(
                        "Pressure", [this] { return m_Pressure; })
                        .setCausality(causality_t::OUTPUT)
                        .setVariability(variability_t::CONTINUOUS)
                        .setDependencies({get_real_variable("Altitude")->index()}));

        register_variable(
                real(
                        "Temperature", [this] { return m_Temperature; })
                        .setCausality(causality_t::OUTPUT)
                        .setVariability(variability_t::CONTINUOUS)
                        .setDependencies({get_real_variable("Altitude")->index()}));

        register_variable(
                real(
                        "Density", [this] { return m_Density; })
                        .setCausality(causality_t::OUTPUT)
                        .setVariability(variability_t::CONTINUOUS)
                        .setDependencies({get_real_variable("Altitude")->index()}));
     
        Model::reset();
    }

    bool do_step(double currentTime, double dt) override {

        try{
            m_Temperature = US1976::Temperature(m_Altitude);
            m_Pressure    = US1976::Pressure(m_Altitude);
            m_Density     = US1976::Density(m_Altitude);
            return true;
        }catch(...){
            return false;
        } 
    }

    void reset() override {
       m_Altitude = 0.0;
       m_Temperature = 0.0;
       m_Pressure = 0.0;
       m_Density = 0.0;
    }

private:
    double m_Altitude;
    double m_Temperature;
    double m_Pressure;
    double m_Density;
};

model_info fmu4cpp::get_model_info() {
    model_info info;
    info.modelName = "AtmosphereUS1976";
    info.description = "US1976 atmospheric model";
    info.modelIdentifier = FMU4CPP_MODEL_IDENTIFIER;
    return info;
}

std::unique_ptr<fmu_base> fmu4cpp::createInstance(const std::string &instanceName, const std::string &fmuResourceLocation) {
    return std::make_unique<Model>(instanceName, fmuResourceLocation);
}