# /* ----------------------------------------------------------------------------*
#   Copyright 
#
#   Written by Melina Aero, Istanbul, Turkey
#   Contact onur.tuncer@melina-aero.com
# -------------------------------------------------------------------------------*/

macro(add_fmu)

        set(singleValue NAME)
        cmake_parse_arguments(local "" "${singleValue}" "${multipleValues}" ${ARGN})

        add_library(${local_NAME} SHARED      
                "${local_NAME}/${local_NAME}.cpp"
                "$<TARGET_OBJECTS:fmu4cpp>")
            
        target_include_directories(${local_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/export/include    # includes specific to fmu4cpp
                                                         ${PROJECT_SOURCE_DIR}/vendor/libode/src # for libode
                                                         ${PROJECT_SOURCE_DIR}/include)          # for models

        target_compile_definitions(${local_NAME} PRIVATE FMU4CPP_MODEL_IDENTIFIER="${local_NAME}")

        target_link_libraries(${local_NAME} PRIVATE libode)

        add_custom_command(TARGET ${local_NAME} PRE_BUILD
                                COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/${local_NAME}")
        
      
        set(outputDir "$<1:${CMAKE_BINARY_DIR}/${local_NAME}/binaries/${TARGET_PLATFORM}>")

        if (WIN32)
        set_target_properties(${local_NAME}
                PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY "${outputDir}"
                )
        else ()
        set_target_properties(${local_NAME}
                PROPERTIES
                PREFIX ""
                LIBRARY_OUTPUT_DIRECTORY "${outputDir}"
                )
        endif ()

        # Generate modelDescription.xml
        add_custom_command(TARGET ${local_NAME} POST_BUILD DEPENDS ${local_NAME} descriptionGenerator
                WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/${local_NAME}"
                COMMAND ../export/descriptionGenerator "${outputDir}/$<TARGET_FILE_NAME:${local_NAME}>")
        
        #Zip model description and shared library together
        add_custom_command(TARGET ${local_NAME} POST_BUILD 
                WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/${local_NAME}"
                COMMAND ${CMAKE_COMMAND} -E tar "c" "${local_NAME}.fmu" --format=zip
                "binaries/"
                "modelDescription.xml")
  
endmacro()

foreach(fmu IN LISTS FMU_TARGETS)

     add_fmu(NAME ${fmu})
   
endforeach()