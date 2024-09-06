/*
 * -----------------------------------------------------------------------------------
 * Project:     [EBEK]
 * File:        [3DoFFixedMassRotatingEllipsoidEarth.cpp]
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
#include "EarthCenteredFrames.h"
#include "DynamicModel.h"
#include "ode_row6a.h"

using namespace fmu4cpp;

class Model : public fmu_base {

public:
    Model(const std::string &instanceName, const std::string &resources)
        : fmu_base(instanceName, resources) {

        register_variable(
                real(
                        "mass", [this] { return m_Mass; }, [this](double value) { m_Mass = value; })
                        .setCausality(causality_t::PARAMETER)
                        .setVariability(variability_t::FIXED));

        register_variable(
                real(
                        "neu_Origin_Latitude", [this] { return m_NeuOriginLatitude; }, [this](double value) { m_NeuOriginLatitude = value; })
                        .setCausality(causality_t::PARAMETER)
                        .setVariability(variability_t::FIXED));

        register_variable(
                real(
                        "neu_Origin_Longitude", [this] { return m_NeuOriginLongitude; }, [this](double value) { m_NeuOriginLongitude = value; })
                        .setCausality(causality_t::PARAMETER)
                        .setVariability(variability_t::FIXED));

        register_variable(
                real(
                        "neu_Origin_Altitude", [this] { return m_NeuOriginAltitude; }, [this](double value) { m_NeuOriginAltitude = value; })
                        .setCausality(causality_t::PARAMETER)
                        .setVariability(variability_t::FIXED));

        register_variable(
                real(
                        "eci_Rx", [this] { return m_EciRx; }, [this](double value) { m_EciRx = value; })
                        .setCausality(causality_t::OUTPUT)
                        .setVariability(variability_t::CONTINUOUS)
                        .setDependencies({get_real_variable("mass")->index(),
                                          get_real_variable("neu_Origin_Latitude")->index(),
                                          get_real_variable("neu_Origin_Longitute")->index(),
                                          get_real_variable("neu_Origin_Altitude")->index(),
                                          get_real_variable("eci_Vx")->index(),
                                          get_real_variable("ecef_Rx")->index(),
                                          get_real_variable("ecef_Ry")->index(),
                                          get_real_variable("ecef_Rz")->index()}));

        register_variable(
                real(
                        "eci_Ry", [this] { return m_EciRy; }, [this](double value) { m_EciRy = value; })
                        .setCausality(causality_t::OUTPUT)
                        .setVariability(variability_t::CONTINUOUS)
                        .setDependencies({get_real_variable("mass")->index(),
                                          get_real_variable("neu_Origin_Latitude")->index(),
                                          get_real_variable("neu_Origin_Longitute")->index(),
                                          get_real_variable("neu_Origin_Altitude")->index(),
                                          get_real_variable("eci_Vy")->index(),
                                          get_real_variable("ecef_Rx")->index(),
                                          get_real_variable("ecef_Ry")->index(),
                                          get_real_variable("ecef_Rz")->index()}));
  
        register_variable(
                real(
                        "eci_Rz", [this] { return m_EciRz; }, [this](double value) { m_EciRz = value; })
                        .setCausality(causality_t::OUTPUT)
                        .setVariability(variability_t::CONTINUOUS)
                        .setDependencies({get_real_variable("mass")->index(),
                                          get_real_variable("neu_Origin_Latitude")->index(),
                                          get_real_variable("neu_Origin_Longitute")->index(),
                                          get_real_variable("neu_Origin_Altitude")->index(),
                                          get_real_variable("eci_Vz")->index(),
                                          get_real_variable("ecef_Rx")->index(),
                                          get_real_variable("ecef_Ry")->index(),
                                          get_real_variable("ecef_Rz")->index()}));

        
        register_variable(
                real(
                        "eci_Vx", [this] { return m_EciRx; }, [this](double value) { m_EciVx = value; })
                        .setCausality(causality_t::OUTPUT)
                        .setVariability(variability_t::CONTINUOUS)
                        .setDependencies({get_real_variable("mass")->index(),
                                          get_real_variable("neu_Origin_Latitude")->index(),
                                          get_real_variable("neu_Origin_Longitute")->index(),
                                          get_real_variable("neu_Origin_Altitude")->index(),
                                          get_real_variable("ecef_Vx")->index(),
                                          get_real_variable("ecef_Vy")->index(),
                                          get_real_variable("ecef_Vz")->index()}));

        register_variable(
                real(
                        "eci_Vy", [this] { return m_EciRy; }, [this](double value) { m_EciVy = value; })
                        .setCausality(causality_t::OUTPUT)
                        .setVariability(variability_t::CONTINUOUS)
                        .setDependencies({get_real_variable("mass")->index(),
                                          get_real_variable("neu_Origin_Latitude")->index(),
                                          get_real_variable("neu_Origin_Longitute")->index(),
                                          get_real_variable("neu_Origin_Altitude")->index(),
                                          get_real_variable("ecef_Vx")->index(),
                                          get_real_variable("ecef_Vy")->index(),
                                          get_real_variable("ecef_Vz")->index()}));
  
        register_variable(
                real(
                        "eci_Vz", [this] { return m_EciRz; }, [this](double value) { m_EciVz = value; })
                        .setCausality(causality_t::OUTPUT)
                        .setVariability(variability_t::CONTINUOUS)
                        .setDependencies({get_real_variable("mass")->index(),
                                          get_real_variable("neu_Origin_Latitude")->index(),
                                          get_real_variable("neu_Origin_Longitute")->index(),
                                          get_real_variable("neu_Origin_Altitude")->index(),
                                          get_real_variable("ecef_Vx")->index(),
                                          get_real_variable("ecef_Vy")->index(),
                                          get_real_variable("ecef_Vz")->index()}));
        
        register_variable(
                real(
                        "ecef_Rx", [this] { return m_EciRx; }, [this](double value) { m_EcefRx = value; })
                        .setCausality(causality_t::OUTPUT)
                        .setVariability(variability_t::CONTINUOUS)
                        .setDependencies({get_real_variable("mass")->index(),
                                          get_real_variable("neu_Origin_Latitude")->index(),
                                          get_real_variable("neu_Origin_Longitute")->index(),
                                          get_real_variable("neu_Origin_Altitude")->index(),
                                          get_real_variable("ecif_Rx")->index(),
                                          get_real_variable("ecif_Ry")->index(),
                                          get_real_variable("ecif_Rz")->index()}));

        register_variable(
                real(
                        "ecef_Ry", [this] { return m_EciRy; }, [this](double value) { m_EcefRy = value; })
                        .setCausality(causality_t::OUTPUT)
                        .setVariability(variability_t::CONTINUOUS)
                        .setDependencies({get_real_variable("mass")->index(),
                                          get_real_variable("neu_Origin_Latitude")->index(),
                                          get_real_variable("neu_Origin_Longitute")->index(),
                                          get_real_variable("neu_Origin_Altitude")->index(),
                                          get_real_variable("eci_Rx")->index(),
                                          get_real_variable("eci_Ry")->index(),
                                          get_real_variable("eci_Rz")->index()}));
  
        register_variable(
                real(
                        "ecef_Rz", [this] { return m_EciRz; }, [this](double value) { m_EcefRz = value; })
                        .setCausality(causality_t::OUTPUT)
                        .setVariability(variability_t::CONTINUOUS)
                        .setDependencies({get_real_variable("mass")->index(),
                                          get_real_variable("neu_Origin_Latitude")->index(),
                                          get_real_variable("neu_Origin_Longitute")->index(),
                                          get_real_variable("neu_Origin_Altitude")->index(),
                                          get_real_variable("eci_Rx")->index(),
                                          get_real_variable("eci_Ry")->index(),
                                          get_real_variable("eci_Rz")->index()}));
     
        register_variable(
                real(
                        "ecef_Vx", [this] { return m_EciRx; }, [this](double value) { m_EcefVx = value; })
                        .setCausality(causality_t::OUTPUT)
                        .setVariability(variability_t::CONTINUOUS)
                        .setDependencies({get_real_variable("mass")->index(),
                                          get_real_variable("neu_Origin_Latitude")->index(),
                                          get_real_variable("neu_Origin_Longitute")->index(),
                                          get_real_variable("neu_Origin_Altitude")->index(),
                                          get_real_variable("eci_Vx")->index(),
                                          get_real_variable("eci_Vy")->index(),
                                          get_real_variable("eci_Vz")->index()}));

        register_variable(
                real(
                        "ecef_Vy", [this] { return m_EciRy; }, [this](double value) { m_EcefVy = value; })
                        .setCausality(causality_t::OUTPUT)
                        .setVariability(variability_t::CONTINUOUS)
                        .setDependencies({get_real_variable("mass")->index(),
                                          get_real_variable("neu_Origin_Latitude")->index(),
                                          get_real_variable("neu_Origin_Longitute")->index(),
                                          get_real_variable("neu_Origin_Altitude")->index(),
                                          get_real_variable("eci_Vx")->index(),
                                          get_real_variable("eci_Vy")->index(),
                                          get_real_variable("eci_Vz")->index()}));
  
        register_variable(
                real(
                        "ecef_Vz", [this] { return m_EciRz; }, [this](double value) { m_EcefVz = value; })
                        .setCausality(causality_t::OUTPUT)
                        .setVariability(variability_t::CONTINUOUS)
                        .setDependencies({get_real_variable("mass")->index(),
                                          get_real_variable("neu_Origin_Latitude")->index(),
                                          get_real_variable("neu_Origin_Longitute")->index(),
                                          get_real_variable("neu_Origin_Altitude")->index(),
                                          get_real_variable("eci_Vx")->index(),
                                          get_real_variable("eci_Vy")->index(),
                                          get_real_variable("eci_Vz")->index()}));
            
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
       m_Mass = 1.0; //kg

       // Set the location on the surface of earth 
       // where the prime meridian intersects the equator
       m_NeuOriginLatitude = 0.0;
       m_NeuOriginLongitude = 0.0;
       m_NeuOriginAltitude = 0.0;


    
    }

private:
    DynamicModel<OdeROW6A> m_DynamicSystem;
    // /********Inertial properties**********************************/
    // double m_Mass;
    // /*************************************************************/

    double m_NeuOriginLatitude;   // in WGS-84 geodetic coordinates
    double m_NeuOriginLongitude;
    double m_NeuOriginAltitude;    

    /*****State variables to be integrated by the dynamic model*/
    double m_EciRx;
    double m_EciRy;
    double m_EciRz;

    double m_EciVx;
    double m_EciVy;
    double m_EciVz;
    /************************************************************/

    /********Helper coordinate frames****************************/
    double m_EcefRx;
    double m_EcefRy;
    double m_EcefRz;

    double m_EcefVx;
    double m_EcefVy;
    double m_EcefVz;
    /**************************************************************/
 
};

model_info fmu4cpp::get_model_info() {
    model_info info;
    info.modelName = "3DoFFixedMassRotatingEllipsoidEarth";
    info.description = "3DoF Fixed Mass with Rotating Ellipsoid Earth";
    info.modelIdentifier = FMU4CPP_MODEL_IDENTIFIER;
    return info;
}

std::unique_ptr<fmu_base> fmu4cpp::createInstance(const std::string &instanceName, const std::string &fmuResourceLocation) {
    return std::make_unique<Model>(instanceName, fmuResourceLocation);
}