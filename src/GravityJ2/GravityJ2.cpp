/*
 * -----------------------------------------------------------------------------------
 * Project:     [EBEK]
 * File:        [DynamicModel.h]
 * Author:      Prof.Dr. Onur Tuncer
 * Email:       onur.tuncer@itu.edu.tr
 * Institution: Istanbul Technical University
 *              Faculty of Aeronautics and Astronuatics
 * 
 * Date:        2024
 *
 * Description:
 * [Dynamic model of 6 DoF Fixed Mass FMU]
 *
 * License:
 * [See License.txt in the top level directory for licence and copyright information]
 *
 * -----------------------------------------------------------------------------------
 */

#include <utility>
#include <fmu4cpp/fmu_base.hpp>
#include "GravitationalModels.h"

using namespace fmu4cpp;

class Model : public fmu_base {

public:
    Model(const std::string &instanceName, const std::string &resources)
        : fmu_base(instanceName, resources) {

        // register_variable(
                // real(
                //         "Gain", [this] { return m_Gain; }, [this](double value) { m_Gain = value; })
                //         .setCausality(causality_t::PARAMETER)
                //         .setVariability(variability_t::FIXED));
    
        register_variable(
                real(
                        "eci_rx", [this] { return m_EciRx; }, [this](double value) { m_EciRx = value; })
                        .setCausality(causality_t::INPUT)
                        .setVariability(variability_t::CONTINUOUS));

        register_variable(        
                real(
                        "eci_ry", [this] { return m_EciRy; }, [this](double value) { m_EciRy = value; })
                        .setCausality(causality_t::INPUT)
                        .setVariability(variability_t::CONTINUOUS));

        register_variable(
                real(
                        "eci_rz", [this] { return m_EciRz; }, [this](double value) { m_EciRz = value; })
                        .setCausality(causality_t::INPUT)
                        .setVariability(variability_t::CONTINUOUS));
      
        register_variable(
                real(
                        "eci_gx", [this] { return m_EciGx; })
                        .setCausality(causality_t::OUTPUT)
                        .setVariability(variability_t::CONTINUOUS)
                        .setDependencies({get_real_variable("eci_rx")->index(),
                                          get_real_variable("eci_ry")->index(),
                                          get_real_variable("eci_rz")->index()}));

        register_variable(
                real(
                        "eci_gx", [this] { return m_EciGx; })
                        .setCausality(causality_t::OUTPUT)
                        .setVariability(variability_t::CONTINUOUS)
                        .setDependencies({get_real_variable("eci_rx")->index(),
                                          get_real_variable("eci_ry")->index(),
                                          get_real_variable("eci_rz")->index()}));
        
        register_variable(
                real(
                        "eci_gx", [this] { return m_EciGx; })
                        .setCausality(causality_t::OUTPUT)
                        .setVariability(variability_t::CONTINUOUS)
                        .setDependencies({get_real_variable("eci_rx")->index(),
                                          get_real_variable("eci_ry")->index(),
                                          get_real_variable("eci_rz")->index()}));
     
        Model::reset();
    }

    bool do_step(double currentTime, double dt) override {

        try{
            auto result = J2::calculateGravitationalAcceleration<double>(m_EciRx, m_EciRy, m_EciRz);
            m_EciGx = result[0];
            m_EciGy = result[1];
            m_EciGz = result[2];
            return true;
        }catch(...){
            return false;
        }
    }

    void reset() override {
       m_EciRx = 0.0;
       m_EciRy = 1.0;
       m_EciRz = 0.0;
    }

private:
    double m_EciRx;
    double m_EciRy;
    double m_EciRz;
    double m_EciGx;
    double m_EciGy;
    double m_EciGz;
};

model_info fmu4cpp::get_model_info() {
    model_info info;
    info.modelName = "GravityJ2";
    info.description = "J2 gravity model";
    info.modelIdentifier = FMU4CPP_MODEL_IDENTIFIER;
    return info;
}

std::unique_ptr<fmu_base> fmu4cpp::createInstance(const std::string &instanceName, const std::string &fmuResourceLocation) {
    return std::make_unique<Model>(instanceName, fmuResourceLocation);
}