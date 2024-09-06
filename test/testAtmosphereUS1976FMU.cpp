#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <fmu4cpp/fmu_base.hpp>

fmu4cpp::model_info fmu4cpp::get_model_info() {
    fmu4cpp::model_info m;
    m.modelIdentifier = FMU4CPP_MODEL_IDENTIFIER;
    return m;
}

std::unique_ptr<fmu4cpp::fmu_base> fmu4cpp::createInstance(const std::string &instanceName, const std::string &fmuResourceLocation) {
    return std::make_unique<Model>(instanceName, fmuResourceLocation);
}