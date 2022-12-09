/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 */
#ifndef CVT__VTK_UNSTRUCTURED_FILE_FORMAT_H_INCLUDE
#define CVT__VTK_UNSTRUCTURED_FILE_FORMAT_H_INCLUDE
#include "FileFormat/VtkFileFormat.h"

#include <unordered_set>

#include <vtkExtractCellsByType.h>

namespace cvt
{
namespace detail
{
template <typename BaseClass>
class CellTypeIterator
{
    using VtkDataPointerType = vtkSmartPointer<typename BaseClass::VtkDataType>;

private:
    using InternalIterator = std::unordered_set<int>::const_iterator;

public:
    CellTypeIterator( InternalIterator itr, VtkDataPointerType vtk_data ) noexcept:
        iterator( itr ), extractor( vtkSmartPointer<vtkExtractCellsByType>::New() )
    {
        data = vtk_data;
        extractor->SetInputData( data );
    }

public:
    BaseClass operator*()
    {
        extractor->RemoveAllCellTypes();
        extractor->AddCellType( *iterator );
        extractor->Update();

        return BaseClass(
            dynamic_cast<typename BaseClass::VtkDataType*>( extractor->GetOutput() ) );
    }
    CellTypeIterator<BaseClass> operator++()
    {
        ++iterator;
        return *this;
    }
    CellTypeIterator<BaseClass> operator++( int )
    {
        auto old = *this;
        ++iterator;
        return old;
    }
    bool operator==( const CellTypeIterator<BaseClass>& other )
    {
        return iterator == other.iterator;
    }
    bool operator==( const CellTypeIterator<BaseClass>& other ) const
    {
        return iterator == other.iterator;
    }
    bool operator!=( const CellTypeIterator<BaseClass>& other )
    {
        return iterator != other.iterator;
    }
    bool operator!=( const CellTypeIterator<BaseClass>& other ) const
    {
        return iterator != other.iterator;
    }

private:
    InternalIterator iterator;
    VtkDataPointerType data;
    vtkSmartPointer<vtkExtractCellsByType> extractor;
};

template <typename BaseClass>
class CellTypeContainer
{
public:
    using VtkDataPointerType = vtkSmartPointer<typename BaseClass::VtkDataType>;

public:
    CellTypeContainer( const std::unordered_set<int>& types, VtkDataPointerType d ):
        cell_types( types ), data( d )
    {
    }

public:
    cvt::detail::CellTypeIterator<BaseClass> begin()
    {
        return cvt::detail::CellTypeIterator<BaseClass>( cell_types.cbegin(), data );
    }
    cvt::detail::CellTypeIterator<BaseClass> begin() const
    {
        return cvt::detail::CellTypeIterator<BaseClass>( cell_types.begin(), data );
    }
    cvt::detail::CellTypeIterator<BaseClass> end()
    {
        return cvt::detail::CellTypeIterator<BaseClass>( cell_types.cend(), data );
    }
    cvt::detail::CellTypeIterator<BaseClass> end() const
    {
        return cvt::detail::CellTypeIterator<BaseClass>( cell_types.end(), data );
    }

private:
    const std::unordered_set<int>& cell_types;
    VtkDataPointerType data;
};
} // namespace detail
} // namespace cvt

namespace cvt
{

/**
 * A file IO for vtkUnstructuredGrid.
 */
template <typename VtkDataType, typename VtkReaderType, typename VtkWriterType>
class VtkUnstructuredFileFormat
    : public cvt::VtkFileFormat<VtkDataType, VtkReaderType, VtkWriterType>
{
public:
    /**
     * A base class type.
     */
    using BaseClass = cvt::VtkFileFormat<VtkDataType, VtkReaderType, VtkWriterType>;

public:
    /**
     * Construct an empty IO object.
     */
    VtkUnstructuredFileFormat() noexcept: BaseClass() {}
    /**
     * Construct an IO object.
     *
     * \param filename A file name.
     */
    VtkUnstructuredFileFormat( const std::string& filename ): BaseClass( filename )
    {
        InitializeCellTypes();
    }
    /**
     * Construct an IO object.
     *
     * \param filename A file name.
     */
    VtkUnstructuredFileFormat( std::string&& filename ): BaseClass( filename )
    {
        InitializeCellTypes();
    }
    /**
     * Construct an IO object.
     *
     * \param [in] vtk_data A VTK data.
     */
    VtkUnstructuredFileFormat( VtkDataType* data ): BaseClass( data ) { InitializeCellTypes(); }

public:
    /**
     * Get an interface to iterate by a cell type in a for loop.
     *
     * e.g.
     *
     *     SomeVtkUnstructuredFileFormat file_format;
     *     for (SomeVtkUnstructuredFileFormat single_cell_type_file_format :
     *          file_format.eachCellTypes()) {
     *         // ...
     *     }
     *
     * \return An interface to iterate by a cell type.
     */
    cvt::detail::CellTypeContainer<
        VtkUnstructuredFileFormat<VtkDataType, VtkReaderType, VtkWriterType>>
    eachCellTypes()
    {
        return cvt::detail::CellTypeContainer<
            VtkUnstructuredFileFormat<VtkDataType, VtkReaderType, VtkWriterType>>(
            cell_types, BaseClass::get() );
    }
    /**
     * Get an interface to iterate by a cell type in a for loop.
     *
     * e.g.
     *
     *     SomeVtkUnstructuredFileFormat file_format;
     *     for (SomeVtkUnstructuredFileFormat single_cell_type_file_format :
     *          file_format.eachCellTypes()) {
     *         // ...
     *     }
     *
     * \return An interface to iterate by a cell type.
     */
    cvt::detail::CellTypeContainer<
        VtkUnstructuredFileFormat<VtkDataType, VtkReaderType, VtkWriterType>>
    eachCellTypes() const
    {
        return cvt::detail::CellTypeContainer<
            VtkUnstructuredFileFormat<VtkDataType, VtkReaderType, VtkWriterType>>(
            cell_types, BaseClass::get() );
    }

private:
    void InitializeCellTypes()
    {
        auto data = this->get();

        if ( data->GetNumberOfPoints() > 0 )
        {
            for ( vtkIdType i = 0; i < data->GetNumberOfCells(); ++i )
            {
                auto cell = data->GetCell( i );
                cell_types.insert( cell->GetCellType() );
            }
        }
    }

private:
    std::unordered_set<int> cell_types;
};
} // namespace cvt

#endif // CVT__VTK_UNSTRUCTURED_FILE_FORMAT_H_INCLUDE