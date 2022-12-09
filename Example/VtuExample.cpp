#include <iostream>
#include <string>

#include "kvs/UnstructuredVolumeObject"

#include "Exporter/UnstructuredVolumeObjectExporter.h"
#include "FileFormat/KVSML/KvsmlUnstructuredVolumeObject.h"
#include "FileFormat/NumeralSequenceFiles.h"
#include "FileFormat/Pfl.h"
#include "FileFormat/UnstructuredPfi.h"
#include "FileFormat/VTK/VtkXmlUnstructuredGrid.h"
#include "Importer/VtkImporter.h"

void Vtu2Kvsml( const char* directory, const char* base, const char* src )
{
    std::cout << "reading " << src << " ..." << std::endl;
    cvt::VtkXmlUnstructuredGrid input_vtu( src );

    cvt::Pfl pfl;

    for ( auto vtu : input_vtu.eachCellTypes() )
    {
        int time_step = 0;
        int last_time_step = 0;
        int sub_volume_id = 1;
        int sub_volume_count = 1;

        cvt::VtkImporter<cvt::VtkXmlUnstructuredGrid> importer( &vtu );

        kvs::UnstructuredVolumeObject* object = &importer;
        std::cout << "#nodes: " << object->numberOfNodes() << std::endl;
        std::cout << "#cells: " << object->numberOfCells() << std::endl;
        std::cout << "cellType: " << object->cellType() << std::endl;

        std::cout << "writing to " << directory << std::endl;
        auto local_base = std::string( base ) + "_" + std::to_string( object->cellType() );

        cvt::UnstructuredVolumeObjectExporter exporter( &importer );
        exporter.setWritingDataTypeToExternalBinary();
        exporter.writeForPbvr( directory, local_base, time_step, sub_volume_id, sub_volume_count );
        // or
        // exporter.write( "<directory>/<local_base>_00000_0000001_0000001.kvsml" );

        cvt::UnstructuredPfi pfi( object->veclen(), last_time_step, sub_volume_count );
        pfi.registerObject( &exporter, time_step, sub_volume_id );
        pfi.write( directory, local_base );
        // or
        // pfi.write( "<directory>/<local_base>.pfi" );

        pfl.registerPfi( directory, local_base );
    }

    pfl.write( directory, base );
    // or
    // pfl.write( "<directory/<base>.pfi" );
}

void SeriesVtu2Kvsml( const char* directory, const char* base, const char* src )
{
    std::cout << "reading " << src << " ..." << std::endl;

    std::unordered_map<int, cvt::UnstructuredPfi> pfi_map;

    cvt::NumeralSequenceFiles<cvt::VtkXmlUnstructuredGrid> time_series( src );
    int last_time_step = time_series.numberOfFiles() - 1;
    int time_step = 0;
    int sub_volume_id = 1;
    int sub_volume_count = 1;

    for ( auto whole_vtu : time_series.eachTimeSteps() )
    {
        for ( auto vtu : whole_vtu.eachCellTypes() )
        {
            cvt::VtkImporter<cvt::VtkXmlUnstructuredGrid> importer( &vtu );

            kvs::UnstructuredVolumeObject* object = &importer;
            std::cout << "#nodes: " << object->numberOfNodes() << std::endl;
            std::cout << "#cells: " << object->numberOfCells() << std::endl;
            std::cout << "cellType: " << object->cellType() << std::endl;

            std::cout << "writing to " << directory << std::endl;
            auto local_base = std::string( base ) + "_" + std::to_string( object->cellType() );

            cvt::UnstructuredVolumeObjectExporter exporter( &importer );
            exporter.setWritingDataTypeToExternalBinary();
            exporter.writeForPbvr( directory, local_base, time_step, sub_volume_id,
                                   sub_volume_count );
            // or
            // exporter.write( "<directory>/<local_base>_<time_step>_0000001_0000001.kvsml" );

            if ( time_step == 0 )
            {
                pfi_map.emplace(
                    static_cast<int>( object->cellType() ),
                    cvt::UnstructuredPfi( object->veclen(), last_time_step, sub_volume_count ) );
            }
            pfi_map.at( static_cast<int>( object->cellType() ) )
                .registerObject( &exporter, time_step, sub_volume_id );
        }

        ++time_step;
    }

    cvt::Pfl pfl;
    for ( auto& e : pfi_map )
    {
        std::string local_base = std::string( base ) + "_" + std::to_string( e.first );
        e.second.write( directory, local_base );
        // or
        // e.write( "<directory>/<local_base>.pfi" );

        pfl.registerPfi( directory, local_base );
    }
    pfl.write( directory, base );
    // or
    // pfl.write( "<directory>/<base>.pfl" );
}
