/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 */
#ifndef CVT_VTK_IMPORT_H_INCLUDE
#define CVT_VTK_IMPORT_H_INCLUDE

#include "kvs/LineObject"
#include "kvs/PointObject"
#include "kvs/PolygonObject"
#include "kvs/StructuredVolumeObject"
#include "kvs/UnstructuredVolumeObject"

#include <vtkImageData.h>
#include <vtkPolyData.h>
#include <vtkRectilinearGrid.h>
#include <vtkSmartPointer.h>
#include <vtkStructuredGrid.h>
#include <vtkUnstructuredGrid.h>

namespace cvt
{
namespace detail
{

/**
 * Import a KVS polygon object from a VTK PolyData.
 *
 * \param [inout] polygon_object A KVS polygon object.
 * \param [in] data A VTK PolyData.
 */
void ImportPolygonObject( kvs::PolygonObject* polygon_object, vtkSmartPointer<vtkPolyData> data );
/**
 * Import a KVS polygon object from a VTK UnstructuredGrid.
 *
 * \param [inout] polygon_object A KVS polygon object.
 * \param [in] data A VTK UnstructuredGrid.
 */
void ImportPolygonObject( kvs::PolygonObject* polygon_object,
                          vtkSmartPointer<vtkUnstructuredGrid> data );
/**
 * Import a KVS rectilinear object from a VTK RectilinearGrid.
 *
 * \param [inout] rectilinear_object A KVS rectilinear object.
 * \param [in] data A VTK RectilinearGrid.
 */
void ImportRectilinearObject( kvs::StructuredVolumeObject* rectilinear_object,
                              vtkSmartPointer<vtkRectilinearGrid> data );
/**
 * Import a KVS uniform structured volume object from a VTK ImageData.
 *
 * \param [inout] uniform_object A KVS uniform structured volume object.
 * \param [in] data A VTK ImageData.
 */
void ImportUniformStructuredVolumeObject( kvs::StructuredVolumeObject* uniform_object,
                                          vtkSmartPointer<vtkImageData> data );
/**
 * Import a KVS irregular structured volume object from a VTK StructuredGrid.
 *
 * \param [inout] irregular_object A KVS irregular structured volume object.
 * \param [in] data A VTK StructuredGrid.
 */
void ImportIrregularStructuredVolumeObject( kvs::StructuredVolumeObject* irregular_object,
                                            vtkSmartPointer<vtkStructuredGrid> data );
/**
 * Import a KVS unstructured volume object from a VTK UnstructuredGrid.
 *
 * \param [inout] object A KVS unstructured volume object.
 * \param [in] data A VTK UnstructuredGrid.
 */
void ImportUnstructuredVolumeObject( kvs::UnstructuredVolumeObject* object,
                                     vtkSmartPointer<vtkUnstructuredGrid> data );
/**
 * Import a KVS point object from a VTK UnstructuredGrid.
 *
 * \param [inout] object A KVS point object.
 * \param [in] data A VTK UnstructuredGrid.
 */
void ImportPointObject( kvs::PointObject* object, vtkSmartPointer<vtkUnstructuredGrid> data );
/**
 * Import a KVS line object from a VTK UnstructuredGrid.
 *
 * \param [inout] object A KVS line object.
 * \param [in] data A VTK UnstructuredGrid.
 */
void ImportLineObject( kvs::LineObject* object, vtkSmartPointer<vtkUnstructuredGrid> data );
} // namespace detail
} // namespace cvt

namespace cvt
{
/**
 * Import from a VTK data to a KVS object.
 *
 * \param [inout] object A destination.
 * \param [in] data A source.
 */
template <typename OutputType, typename InputType>
inline void Import( OutputType object, InputType data );

template <>
inline void Import<kvs::PolygonObject*, vtkSmartPointer<vtkPolyData>>(
    kvs::PolygonObject* polygon_object, vtkSmartPointer<vtkPolyData> data )
{
    if ( !polygon_object )
    {
        throw std::runtime_error( "A KVS object was a null pointer." );
        return;
    }
    if ( !data )
    {
        throw std::runtime_error( "A VTK data was a null pointer." );
        return;
    }
    cvt::detail::ImportPolygonObject( polygon_object, data );

    polygon_object->setColorType( kvs::PolygonObject::PolygonColor );
    polygon_object->setColor( kvs::RGBColor( 255, 255, 255 ) );
    polygon_object->setOpacity( 255 );
}

template <>
inline void Import<kvs::StructuredVolumeObject*, vtkSmartPointer<vtkRectilinearGrid>>(
    kvs::StructuredVolumeObject* rectilinear_object, vtkSmartPointer<vtkRectilinearGrid> data )
{
    if ( !rectilinear_object )
    {
        throw std::runtime_error( "A KVS object was a null pointer." );
        return;
    }
    if ( !data )
    {
        throw std::runtime_error( "A VTK data was a null pointer." );
        return;
    }
    cvt::detail::ImportRectilinearObject( rectilinear_object, data );
}

template <>
inline void Import<kvs::StructuredVolumeObject*, vtkSmartPointer<vtkStructuredGrid>>(
    kvs::StructuredVolumeObject* object, vtkSmartPointer<vtkStructuredGrid> data )
{
    if ( !object )
    {
        throw std::runtime_error( "A KVS object was a null pointer." );
        return;
    }
    if ( !data )
    {
        throw std::runtime_error( "A VTK data was a null pointer." );
        return;
    }

    cvt::detail::ImportIrregularStructuredVolumeObject( object, data );
}

template <>
inline void Import<kvs::StructuredVolumeObject*, vtkSmartPointer<vtkImageData>>(
    kvs::StructuredVolumeObject* object, vtkSmartPointer<vtkImageData> data )
{
    if ( !object )
    {
        throw std::runtime_error( "A KVS object was a null pointer." );
        return;
    }
    if ( !data )
    {
        throw std::runtime_error( "A VTK data was a null pointer." );
        return;
    }

    cvt::detail::ImportUniformStructuredVolumeObject( object, data );
}

template <>
inline void Import<kvs::UnstructuredVolumeObject*, vtkSmartPointer<vtkUnstructuredGrid>>(
    kvs::UnstructuredVolumeObject* object, vtkSmartPointer<vtkUnstructuredGrid> data )
{
    if ( !object )
    {
        throw std::runtime_error( "A KVS object was a null pointer." );
        return;
    }
    if ( !data )
    {
        throw std::runtime_error( "A VTK data was a null pointer." );
        return;
    }

    cvt::detail::ImportUnstructuredVolumeObject( object, data );
}

template <>
inline void Import<kvs::LineObject*, vtkSmartPointer<vtkUnstructuredGrid>>(
    kvs::LineObject* object, vtkSmartPointer<vtkUnstructuredGrid> data )
{
    if ( !object )
    {
        throw std::runtime_error( "A KVS object was a null pointer." );
        return;
    }
    if ( !data )
    {
        throw std::runtime_error( "A VTK data was a null pointer." );
        return;
    }

    cvt::detail::ImportLineObject( object, data );
}

template <>
inline void Import<kvs::PointObject*, vtkSmartPointer<vtkUnstructuredGrid>>(
    kvs::PointObject* object, vtkSmartPointer<vtkUnstructuredGrid> data )
{
    if ( !object )
    {
        throw std::runtime_error( "A KVS object was a null pointer." );
        return;
    }
    if ( !data )
    {
        throw std::runtime_error( "A VTK data was a null pointer." );
        return;
    }

    cvt::detail::ImportPointObject( object, data );
}

template <>
inline void Import<kvs::PolygonObject*, vtkSmartPointer<vtkUnstructuredGrid>>(
    kvs::PolygonObject* object, vtkSmartPointer<vtkUnstructuredGrid> data )
{
    if ( !object )
    {
        throw std::runtime_error( "A KVS object was a null pointer." );
        return;
    }
    if ( !data )
    {
        throw std::runtime_error( "A VTK data was a null pointer." );
        return;
    }

    cvt::detail::ImportPolygonObject( object, data );
}
} // namespace cvt

#endif // CVT_VTK_IMPORT_H_INCLUDE
