//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Copyright (c) 2014-2015, Lawrence Livermore National Security, LLC.
// 
// Produced at the Lawrence Livermore National Laboratory
// 
// LLNL-CODE-666778
// 
// All rights reserved.
// 
// This file is part of Conduit. 
// 
// For details, see: http://llnl.github.io/conduit/.
// 
// Please also read conduit/LICENSE
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
// * Redistributions of source code must retain the above copyright notice, 
//   this list of conditions and the disclaimer below.
// 
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the disclaimer (as noted below) in the
//   documentation and/or other materials provided with the distribution.
// 
// * Neither the name of the LLNS/LLNL nor the names of its contributors may
//   be used to endorse or promote products derived from this software without
//   specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL LAWRENCE LIVERMORE NATIONAL SECURITY,
// LLC, THE U.S. DEPARTMENT OF ENERGY OR CONTRIBUTORS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
// DAMAGES  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
// IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.
// 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


//-----------------------------------------------------------------------------
///
/// file: Node.hpp
///
//-----------------------------------------------------------------------------

#ifndef CONDUIT_NODE_HPP
#define CONDUIT_NODE_HPP

//-----------------------------------------------------------------------------
// -- standard lib includes -- 
//-----------------------------------------------------------------------------
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

//-----------------------------------------------------------------------------
// -- conduit includes -- 
//-----------------------------------------------------------------------------
#include "Core.hpp"
#include "Error.hpp"
#include "Endianness.hpp"
#include "DataType.hpp"
#include "DataArray.hpp"
#include "Schema.hpp"
#include "Generator.hpp"
#include "NodeIterator.hpp"

//-----------------------------------------------------------------------------
// -- begin conduit:: --
//-----------------------------------------------------------------------------
namespace conduit
{

//-----------------------------------------------------------------------------
// -- forward declarations required for conduit::Node --
//-----------------------------------------------------------------------------
class Generator;
class NodeIterator;

//-----------------------------------------------------------------------------
// -- begin conduit::Node --
//-----------------------------------------------------------------------------
///
/// class: conduit::Node
///
/// description:
///  Node is the primary class in conduit.
///
//-----------------------------------------------------------------------------
class CONDUIT_API Node
{

//=============================================================================
//-----------------------------------------------------------------------------
//
// -- public methods -- 
//
//-----------------------------------------------------------------------------
//=============================================================================
public:
    
//-----------------------------------------------------------------------------
// -- friends of Node --
//-----------------------------------------------------------------------------
    /// Note on use of `friend`: 
    ///  NodeIterator needs access to Node internals to create
    ///   an efficient iterator
    friend class NodeIterator;
    friend class Generator;

//-----------------------------------------------------------------------------
//
// -- begin declaration of Node construction and destruction --
//
//-----------------------------------------------------------------------------
///@name Construction and Destruction
///@{
//-----------------------------------------------------------------------------
/// description:
///  Standard construction and destruction methods.
///
/// notes:
///  TODO:
///  Constructors currently use a mix of copy and pointer (external) semantics
///
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// -- basic constructor and destruction -- 
//-----------------------------------------------------------------------------
    Node();
    Node(const Node &node);
    ~Node();

    // returns any node to the empty state
    void reset();
    
//-----------------------------------------------------------------------------
// -- constructors for generic types --
//-----------------------------------------------------------------------------
    explicit Node(const DataType &dtype);
    explicit Node(const Schema &schema);

    /// in these methods the `external` param controls if we use copy or
    /// external semantics.
    Node(const Generator &gen,
         bool external);

    Node(const std::string &json_schema,
         void *data,
         bool external);
   
    Node(const Schema &schema,
         void *data,
         bool external);

    Node(const DataType &dtype,
         void *data,
         bool external);

//-----------------------------------------------------------------------------
///@}
//-----------------------------------------------------------------------------
//
// -- end declaration of Node construction and destruction --
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//
// -- begin declaration of Node generate methods --
//
//-----------------------------------------------------------------------------
///@name Generation from JSON Schemas
///@{
//-----------------------------------------------------------------------------
/// description:
///  These methods use a Generator to parse a json schema into a Node hierarchy.
///
/// * The variants without a void * data parameter will allocate memory for the
///   Node hierarchy and populate with inline values from the json schema (if
///   they are provided).
/// * The `external' variants build a Node hierarchy that points to the input
///   data, they do not copy the data into the Node hierarchy.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// -- direct use of a generator --
//-----------------------------------------------------------------------------
    void generate(const Generator &gen);

    void generate_external(const Generator &gen);

//-----------------------------------------------------------------------------
// -- json schema only --
//-----------------------------------------------------------------------------
    void generate(const std::string &json_schema);

    void generate(const std::string &json_schema,
                  const std::string &protocol);


//-----------------------------------------------------------------------------
// -- json schema coupled with in-core data -- 
//-----------------------------------------------------------------------------
    void generate(const std::string &json_schema,
                  void *data);

    void generate(const std::string &json_schema,
                  const std::string &protocol,
                  void *data);

    void generate_external(const std::string &json_schema,
                           void *data);

    void generate_external(const std::string &json_schema,
                           const std::string &protocol,
                           void *data);

//-----------------------------------------------------------------------------
///@}
//-----------------------------------------------------------------------------
//
// -- end declaration of Node generate methods --
//
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//
// -- begin declaration of Node basic i/o methods --
//
//-----------------------------------------------------------------------------
///@name Binary and Memory-Mapped I/O
///@{
//-----------------------------------------------------------------------------
/// description:
///
//-----------------------------------------------------------------------------
    void load(const std::string &stream_path,
              const std::string &protocol="conduit_pair");

    void load(const std::string &stream_path,
              const Schema &schema);

    void save(const std::string &stream_path,
              const std::string &protocol="conduit_pair") const;

    void mmap(const std::string &stream_path);

    void mmap(const std::string &stream_path,
              const Schema &schema);



//-----------------------------------------------------------------------------
///@}
//-----------------------------------------------------------------------------
//
// -- end declaration of Node basic i/o methods --
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//
// -- begin declaration of Node set methods --
//
//-----------------------------------------------------------------------------
///@name Node::set(...)
///@{
//-----------------------------------------------------------------------------
/// description:
///   set(...) methods follow copy semantics. 
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// -- set for generic types --
//-----------------------------------------------------------------------------
    void set_node(const Node &data);
    void set(const Node &data);
    
    void set_dtype(const DataType &dtype);
    void set(const DataType &dtype);

    void set_schema(const Schema &schema);    
    void set(const Schema &schema);

    void set_data_using_schema(const Schema &schema, void *data);
    void set(const Schema &schema, void *data);

    void set_data_using_dtype(const DataType &dtype, void *data);
    void set(const DataType &dtype, void *data);

//-----------------------------------------------------------------------------
// -- set for bitwidth style scalar types ---
//-----------------------------------------------------------------------------
    // signed integer scalar types
    void set_int8(int8 data);
    void set(int8 data);

    void set_int16(int16 data);
    void set(int16 data);
    
    void set_int32(int32 data);
    void set(int32 data);
    
    void set_int64(int64 data);
    void set(int64 data);

    // unsigned integer scalar types
    void set_uint8(uint8 data);
    void set(uint8 data);
    
    void set_uint16(uint16 data);
    void set(uint16 data);

    void set_uint32(uint32 data);
    void set(uint32 data);
    
    void set_uint64(uint64 data);
    void set(uint64 data);

    // floating point scalar types
    void set_float32(float32 data);
    void set(float32 data);
    
    void set_float64(float64 data);
    void set(float64 data);

//-----------------------------------------------------------------------------
// -- set for conduit::DataArray types ---
//-----------------------------------------------------------------------------
    // signed integer array types via conduit::DataArray
    void set_int8_array(const int8_array  &data);
    void set(const int8_array  &data);
    
    void set_int16_array(const int16_array &data);
    void set(const int16_array &data);
    
    void set_int32_array(const int32_array &data);
    void set(const int32_array &data);
    
    void set_int64_array(const int64_array &data);
    void set(const int64_array &data);

    // unsigned integer array types via conduit::DataArray
    void set_uint8_array(const uint8_array  &data);
    void set(const uint8_array  &data);
    
    void set_uint16_array(const uint16_array &data);
    void set(const uint16_array &data);
    
    void set_uint32_array(const uint32_array &data);
    void set(const uint32_array &data);
    
    void set_uint64_array(const uint64_array &data);
    void set(const uint64_array &data);

    // floating point array types via conduit::DataArray
    void set_float32_array(const float32_array &data);
    void set(const float32_array &data);
    
    void set_float64_array(const float64_array &data);
    void set(const float64_array &data);

//-----------------------------------------------------------------------------
// -- set for string types -- 
//-----------------------------------------------------------------------------
    // char8_str use cases
    void set_string(const std::string &data);
    void set(const std::string &data);
    // special explicit case for string to avoid any overloading ambiguity
    void set_char8_str(const char *data);

//-----------------------------------------------------------------------------
// -- set for bitwidth style std::vector types ---
//  TODO IMP: move std::vector cases
//-----------------------------------------------------------------------------
    //-------------------------------------------------------------------------
    // signed integer array types via std::vector
    //-------------------------------------------------------------------------
    void set_int8_vector(const std::vector<int8>   &data);
    void set(const std::vector<int8>   &data);
    
    //-------------------------------------------------------------------------
    void set_int16_vector(const std::vector<int16>  &data);
    void set(const std::vector<int16>  &data);

    //-------------------------------------------------------------------------
    void set_int32_vector(const std::vector<int32>  &data);    
    void set(const std::vector<int32>  &data);

    //-------------------------------------------------------------------------
    void set_int64_vector(const std::vector<int64>  &data);
    void set(const std::vector<int64>  &data);

    //-------------------------------------------------------------------------
    // unsigned integer array types via std::vector
    //-------------------------------------------------------------------------
    void set_uint8_vector(const std::vector<uint8>   &data);
    void set(const std::vector<uint8>   &data);
    
    //-------------------------------------------------------------------------
    void set_uint16_vector(const std::vector<uint16>  &data);
    void set(const std::vector<uint16>  &data);

    //-------------------------------------------------------------------------
    void set_uint32_vector(const std::vector<uint32>  &data);
    void set(const std::vector<uint32>  &data);
    
    //-------------------------------------------------------------------------
    void set_uint64_vector(const std::vector<uint64>  &data);
    void set(const std::vector<uint64>  &data);

    //-------------------------------------------------------------------------
    // floating point array types via std::vector
    //-------------------------------------------------------------------------
    void set_float32_vector(const std::vector<float32> &data);
    void set(const std::vector<float32> &data);

    //-------------------------------------------------------------------------
    void set_float64_vector(const std::vector<float64> &data);
    void set(const std::vector<float64> &data);



//-----------------------------------------------------------------------------
// -- set via bitwidth style pointers (scalar and array types) -- 
//-----------------------------------------------------------------------------
    //-------------------------------------------------------------------------
    // signed integer pointer cases
    //-------------------------------------------------------------------------
    void set_int8_ptr(int8  *data,
                      index_t num_elements = 1,
                      index_t offset = 0,
                      index_t stride = sizeof(conduit::int8),
                      index_t element_bytes = sizeof(conduit::int8),
                      index_t endianness = Endianness::DEFAULT_ID);

    void set(int8  *data,
             index_t num_elements = 1,
             index_t offset = 0,
             index_t stride = sizeof(conduit::int8),
             index_t element_bytes = sizeof(conduit::int8),
             index_t endianness = Endianness::DEFAULT_ID);

    //-------------------------------------------------------------------------
    void set_int16_ptr(int16 *data, 
                       index_t num_elements = 1,
                       index_t offset = 0,
                       index_t stride = sizeof(conduit::int16),
                       index_t element_bytes = sizeof(conduit::int16),
                       index_t endianness = Endianness::DEFAULT_ID);

    void set(int16 *data, 
             index_t num_elements = 1,
             index_t offset = 0,
             index_t stride = sizeof(conduit::int16),
             index_t element_bytes = sizeof(conduit::int16),
             index_t endianness = Endianness::DEFAULT_ID);
    
    //-------------------------------------------------------------------------
    void set_int32_ptr(int32 *data,
                       index_t num_elements = 1,
                       index_t offset = 0,
                       index_t stride = sizeof(conduit::int32),
                       index_t element_bytes = sizeof(conduit::int32),
                       index_t endianness = Endianness::DEFAULT_ID);
    
    void set(int32 *data,
             index_t num_elements = 1,
             index_t offset = 0,
             index_t stride = sizeof(conduit::int32),
             index_t element_bytes = sizeof(conduit::int32),
             index_t endianness = Endianness::DEFAULT_ID);


    //-------------------------------------------------------------------------
    void set_int64_ptr(int64 *data,
                       index_t num_elements = 1,
                       index_t offset = 0,
                       index_t stride = sizeof(conduit::int64),
                       index_t element_bytes = sizeof(conduit::int64),
                       index_t endianness = Endianness::DEFAULT_ID);

    void set(int64 *data,
             index_t num_elements = 1,
             index_t offset = 0,
             index_t stride = sizeof(conduit::int64),
             index_t element_bytes = sizeof(conduit::int64),
             index_t endianness = Endianness::DEFAULT_ID);

    //-------------------------------------------------------------------------
    // unsigned integer pointer cases
    //-------------------------------------------------------------------------
    void set_uint8_ptr(uint8  *data,
                       index_t num_elements = 1,
                       index_t offset = 0,
                       index_t stride = sizeof(conduit::uint8),
                       index_t element_bytes = sizeof(conduit::uint8),
                       index_t endianness = Endianness::DEFAULT_ID);

    void set(uint8  *data,
             index_t num_elements = 1,
             index_t offset = 0,
             index_t stride = sizeof(conduit::uint8),
             index_t element_bytes = sizeof(conduit::uint8),
             index_t endianness = Endianness::DEFAULT_ID);

    //-------------------------------------------------------------------------
    void set_uint16_ptr(uint16 *data,
                       index_t num_elements = 1,
                       index_t offset = 0,
                       index_t stride = sizeof(conduit::uint16),
                       index_t element_bytes = sizeof(conduit::uint16),
                       index_t endianness = Endianness::DEFAULT_ID);

    void set(uint16 *data,
             index_t num_elements = 1,
             index_t offset = 0,
             index_t stride = sizeof(conduit::uint16),
             index_t element_bytes = sizeof(conduit::uint16),
             index_t endianness = Endianness::DEFAULT_ID);

    //-------------------------------------------------------------------------
    void set_uint32_ptr(uint32 *data, 
                        index_t num_elements = 1,
                        index_t offset = 0,
                        index_t stride = sizeof(conduit::uint32),
                        index_t element_bytes = sizeof(conduit::uint32),
                        index_t endianness = Endianness::DEFAULT_ID);

    void set(uint32 *data, 
             index_t num_elements = 1,
             index_t offset = 0,
             index_t stride = sizeof(conduit::uint32),
             index_t element_bytes = sizeof(conduit::uint32),
             index_t endianness = Endianness::DEFAULT_ID);

    //-------------------------------------------------------------------------
    void set_uint64_ptr(uint64 *data,
                        index_t num_elements = 1,
                        index_t offset = 0,
                        index_t stride = sizeof(conduit::uint64),
                        index_t element_bytes = sizeof(conduit::uint64),
                        index_t endianness = Endianness::DEFAULT_ID);

    void set(uint64 *data,
             index_t num_elements = 1,
             index_t offset = 0,
             index_t stride = sizeof(conduit::uint64),
             index_t element_bytes = sizeof(conduit::uint64),
             index_t endianness = Endianness::DEFAULT_ID);

    //-------------------------------------------------------------------------
    // floating point pointer cases
    //-------------------------------------------------------------------------
    void set_float32_ptr(float32 *data,
                         index_t num_elements = 1,
                         index_t offset = 0,
                         index_t stride = sizeof(conduit::float32),
                         index_t element_bytes = sizeof(conduit::float32),
                         index_t endianness = Endianness::DEFAULT_ID);

    void set(float32 *data,
             index_t num_elements = 1,
             index_t offset = 0,
             index_t stride = sizeof(conduit::float32),
             index_t element_bytes = sizeof(conduit::float32),
             index_t endianness = Endianness::DEFAULT_ID);

    //-------------------------------------------------------------------------
    void set_float64_ptr(float64 *data, 
                         index_t num_elements = 1,
                         index_t offset = 0,
                         index_t stride = sizeof(conduit::float64),
                         index_t element_bytes = sizeof(conduit::float64),
                         index_t endianness = Endianness::DEFAULT_ID);

    void set(float64 *data, 
             index_t num_elements = 1,
             index_t offset = 0,
             index_t stride = sizeof(conduit::float64),
             index_t element_bytes = sizeof(conduit::float64),
             index_t endianness = Endianness::DEFAULT_ID);

//-----------------------------------------------------------------------------
///@}
//-----------------------------------------------------------------------------
//
// -- end declaration of Node set methods --
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//
// -- begin declaration of Node set_path methods --
//
//-----------------------------------------------------------------------------
///@name Node::set_path(...)
///@{
//-----------------------------------------------------------------------------
/// description:
///   set_path(...) methods methods follow copy semantics and allow you to use
///    an explicit path for the destination.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// -- set_path for generic types --
//-----------------------------------------------------------------------------
    void set_path_node(const std::string &path,
                       const Node& data);
    void set_path(const std::string &path,
                  const Node& data);

    //-------------------------------------------------------------------------
    void set_path_dtype(const std::string &path,
                        const DataType& dtype);

    void set_path(const std::string &path,
                  const DataType& dtype);

    //-------------------------------------------------------------------------
    void set_path_schema(const std::string &path,
                         const Schema &schema);

    void set_path(const std::string &path,
                  const Schema &schema);

    //-------------------------------------------------------------------------
    void set_path_data_using_schema(const std::string &path,
                                    const Schema &schema,
                                    void *data);              

    void set_path(const std::string &path,
                  const Schema &schema,
                  void *data);

    //-------------------------------------------------------------------------
    void set_path_data_using_dtype(const std::string &path,
                                   const DataType &dtype,
                                   void *data);

    void set_path(const std::string &path,
                  const DataType &dtype,
                  void *data);

//-----------------------------------------------------------------------------
// -- set_path for bitwidth style scalar types ---
//-----------------------------------------------------------------------------
    //-------------------------------------------------------------------------
    // signed integer scalar types
    //-------------------------------------------------------------------------
    void set_path_int8(const std::string &path, int8 data);
    void set_path(const std::string &path, int8 data);

    //-------------------------------------------------------------------------     
    void set_path_int16(const std::string &path, int16 data);
    void set_path(const std::string &path, int16 data);

    //-------------------------------------------------------------------------
    void set_path_int32(const std::string &path, int32 data);
    void set_path(const std::string &path, int32 data);

    //-------------------------------------------------------------------------
    void set_path_int64(const std::string &path, int64 data);
    void set_path(const std::string &path, int64 data);

    //-------------------------------------------------------------------------
    // unsigned integer scalar types 
    //-------------------------------------------------------------------------
    void set_path_uint8(const std::string &path, uint8 data);
    void set_path(const std::string &path, uint8 data);

    //-------------------------------------------------------------------------
    void set_path_uint16(const std::string &path, uint16 data);
    void set_path(const std::string &path, uint16 data);

    //-------------------------------------------------------------------------
    void set_path_uint32(const std::string &path, uint32 data);
    void set_path(const std::string &path, uint32 data);

    //-------------------------------------------------------------------------
    void set_path_uint64(const std::string &path, uint64 data);
    void set_path(const std::string &path, uint64 data);

    //-------------------------------------------------------------------------
    // floating point scalar types
    //-------------------------------------------------------------------------
    void set_path_float32(const std::string &path, float32 data);
    void set_path(const std::string &path, float32 data);

    //-------------------------------------------------------------------------
    void set_path_float64(const std::string &path, float64 data);
    void set_path(const std::string &path, float64 data);

//-----------------------------------------------------------------------------
// -- set_path for conduit::DataArray types ---
//-----------------------------------------------------------------------------
    //-------------------------------------------------------------------------
    // signed integer array types via conduit::DataArray
    //-------------------------------------------------------------------------
    void set_path_int8_array(const std::string &path,
                          const int8_array  &data);

    void set_path(const std::string &path, const int8_array  &data);

    //-------------------------------------------------------------------------
    void set_path_int16_array(const std::string &path,
                           const int16_array &data);

    void set_path(const std::string &path, const int16_array &data);

    //-------------------------------------------------------------------------
    void set_path_int32_array(const std::string &path,
                        const int32_array &data);

    void set_path(const std::string &path, const int32_array &data);

    //-------------------------------------------------------------------------
    void set_path_int64_array(const std::string &path,
                           const int64_array &data);

    void set_path(const std::string &path, const int64_array &data);

    //-------------------------------------------------------------------------
    // unsigned integer array types via conduit::DataArray
    //-------------------------------------------------------------------------
    void set_path_uint8_array(const std::string &path,
                           const uint8_array  &data);

    void set_path(const std::string &path, const uint8_array  &data);

    //-------------------------------------------------------------------------
    void set_path_uint16_array(const std::string &path,
                            const uint16_array &data);

    void set_path(const std::string &path, const uint16_array &data);

    //-------------------------------------------------------------------------
    void set_path_uint32_array(const std::string &path,
                            const uint32_array &data);

    void set_path(const std::string &path, const uint32_array &data);

    //-------------------------------------------------------------------------
    void set_path_uint64_array(const std::string &path,
                            const uint64_array &data);

    void set_path(const std::string &path, const uint64_array &data);

    //-------------------------------------------------------------------------
    // floating point array types via conduit::DataArray
    //-------------------------------------------------------------------------
    void set_path_float32_array(const std::string &path,
                             const float32_array &data);

    void set_path(const std::string &path, const float32_array &data);

    //-------------------------------------------------------------------------
    void set_path_float64_array(const std::string &path,
                             const float64_array &data);

    void set_path(const std::string &path, const float64_array &data);

//-----------------------------------------------------------------------------
// -- set_path for string types -- 
//-----------------------------------------------------------------------------
    //-------------------------------------------------------------------------
    // char8_str use cases
    //-------------------------------------------------------------------------
    void set_path_string(const std::string &path,
                         const std::string &data);

    void set_path(const std::string &path,
                  const std::string &data);

    //-------------------------------------------------------------------------
    // special explicit case for string to avoid any overloading ambiguity
    //-------------------------------------------------------------------------
    void set_path_char8_str(const std::string &path,
                            const char* data);


//-----------------------------------------------------------------------------
// -- set_path for bitwidth style std::vector types ---
//-----------------------------------------------------------------------------
    //-------------------------------------------------------------------------
    // signed integer array types via std::vector
    //-------------------------------------------------------------------------
    void set_path_int8_vector(const std::string &path,
                              const std::vector<int8> &data);

    void set_path(const std::string &path, const std::vector<int8> &data);

    //-------------------------------------------------------------------------
    void set_path_int16_vector(const std::string &path,
                               const std::vector<int16> &data);

    void set_path(const std::string &path, const std::vector<int16> &data);

    //-------------------------------------------------------------------------
    void set_path_int32_vector(const std::string &path,
                               const std::vector<int32> &data);

    void set_path(const std::string &path, const std::vector<int32> &data);

    //-------------------------------------------------------------------------
    void set_path_int64_vector(const std::string &path,
                               const std::vector<int64> &data);

    void set_path(const std::string &path, const std::vector<int64> &data);

    //-------------------------------------------------------------------------     
    // unsigned integer array types via std::vector
    //-------------------------------------------------------------------------
    void set_path_uint8_vector(const std::string &path,
                               const std::vector<uint8> &data);

    void set_path(const std::string &path, const std::vector<uint8> &data);

    //-------------------------------------------------------------------------
    void set_path_uint16_vector(const std::string &path,
                                const std::vector<uint16> &data);

    void set_path(const std::string &path, const std::vector<uint16> &data);

    //-------------------------------------------------------------------------
    void set_path_uint32_vector(const std::string &path,
                                const std::vector<uint32> &data);
    void set_path(const std::string &path, const std::vector<uint32> &data);

    //-------------------------------------------------------------------------
    void set_path_uint64_vector(const std::string &path,
                                const std::vector<uint64> &data);

    void set_path(const std::string &path, const std::vector<uint64> &data);

    //-------------------------------------------------------------------------
    // floating point array types via std::vector
    //-------------------------------------------------------------------------
    void set_path_float32_vector(const std::string &path,
                                 const std::vector<float32> &data);

    void set_path(const std::string &path, const std::vector<float32> &data);


    //-------------------------------------------------------------------------
    void set_path_float64_vector(const std::string &path,
                                 const std::vector<float64> &data);

    void set_path(const std::string &path, const std::vector<float64> &data);

//-----------------------------------------------------------------------------
// -- set_path via bitwidth style pointers (scalar and array types) -- 
//----------------------------------------------------------------------------- 
    //-------------------------------------------------------------------------
    // signed integer pointer cases
    //-------------------------------------------------------------------------
    void set_path_int8_ptr(const std::string &path,int8  *data,
                           index_t num_elements = 1,
                           index_t offset = 0,
                           index_t stride = sizeof(conduit::int8),
                           index_t element_bytes = sizeof(conduit::int8),
                           index_t endianness = Endianness::DEFAULT_ID);

    void set_path(const std::string &path,int8  *data,
                  index_t num_elements = 1,
                  index_t offset = 0,
                  index_t stride = sizeof(conduit::int8),
                  index_t element_bytes = sizeof(conduit::int8),
                  index_t endianness = Endianness::DEFAULT_ID);

    //-------------------------------------------------------------------------
    void set_path_int16_ptr(const std::string &path,
                            int16 *data, 
                            index_t num_elements = 1,
                            index_t offset = 0,
                            index_t stride = sizeof(conduit::int16),
                            index_t element_bytes = sizeof(conduit::int16),
                            index_t endianness = Endianness::DEFAULT_ID);

    void set_path(const std::string &path,
                  int16 *data, 
                  index_t num_elements = 1,
                  index_t offset = 0,
                  index_t stride = sizeof(conduit::int16),
                  index_t element_bytes = sizeof(conduit::int16),
                  index_t endianness = Endianness::DEFAULT_ID);

    //-------------------------------------------------------------------------
    void set_path_int32_ptr(const std::string &path,
                            int32 *data,
                            index_t num_elements = 1,
                            index_t offset = 0,
                            index_t stride = sizeof(conduit::int32),
                            index_t element_bytes = sizeof(conduit::int32),
                            index_t endianness = Endianness::DEFAULT_ID);

    void set_path(const std::string &path,
                  int32 *data,
                  index_t num_elements = 1,
                  index_t offset = 0,
                  index_t stride = sizeof(conduit::int32),
                  index_t element_bytes = sizeof(conduit::int32),
                  index_t endianness = Endianness::DEFAULT_ID);

    //-------------------------------------------------------------------------
    void set_path_int64_ptr(const std::string &path,
                            int64 *data,
                            index_t num_elements = 1,
                            index_t offset = 0,
                            index_t stride = sizeof(conduit::int64),
                            index_t element_bytes = sizeof(conduit::int64),
                            index_t endianness = Endianness::DEFAULT_ID);

    void set_path(const std::string &path,
               int64 *data,
               index_t num_elements = 1,
               index_t offset = 0,
               index_t stride = sizeof(conduit::int64),
               index_t element_bytes = sizeof(conduit::int64),
               index_t endianness = Endianness::DEFAULT_ID);

    //-------------------------------------------------------------------------
    // unsigned integer pointer cases
    //-------------------------------------------------------------------------
    void set_path_uint8_ptr(const std::string &path,
                            uint8  *data,
                            index_t num_elements = 1,
                            index_t offset = 0,
                            index_t stride = sizeof(conduit::uint8),
                            index_t element_bytes = sizeof(conduit::uint8),
                            index_t endianness = Endianness::DEFAULT_ID);

    void set_path(const std::string &path,
                  uint8  *data,
                  index_t num_elements = 1,
                  index_t offset = 0,
                  index_t stride = sizeof(conduit::uint8),
                  index_t element_bytes = sizeof(conduit::uint8),
                  index_t endianness = Endianness::DEFAULT_ID);

    //-------------------------------------------------------------------------
    void set_path_uint16_ptr(const std::string &path,
                             uint16 *data,
                             index_t num_elements = 1,
                             index_t offset = 0,
                             index_t stride = sizeof(conduit::uint16),
                             index_t element_bytes = sizeof(conduit::uint16),
                             index_t endianness = Endianness::DEFAULT_ID);

    void set_path(const std::string &path,
                  uint16 *data,
                  index_t num_elements = 1,
                  index_t offset = 0,
                  index_t stride = sizeof(conduit::uint16),
                  index_t element_bytes = sizeof(conduit::uint16),
                  index_t endianness = Endianness::DEFAULT_ID);

    //-------------------------------------------------------------------------
    void set_path_uint32_ptr(const std::string &path,
                             uint32 *data, 
                             index_t num_elements = 1,
                             index_t offset = 0,
                             index_t stride = sizeof(conduit::uint32),
                             index_t element_bytes = sizeof(conduit::uint32),
                             index_t endianness = Endianness::DEFAULT_ID);

    void set_path(const std::string &path,
                  uint32 *data, 
                  index_t num_elements = 1,
                  index_t offset = 0,
                  index_t stride = sizeof(conduit::uint32),
                  index_t element_bytes = sizeof(conduit::uint32),
                  index_t endianness = Endianness::DEFAULT_ID);
    
    //-------------------------------------------------------------------------
    void set_path_uint64_ptr(const std::string &path,
                             uint64 *data,
                             index_t num_elements = 1,
                             index_t offset = 0,
                             index_t stride = sizeof(conduit::uint64),
                             index_t element_bytes = sizeof(conduit::uint64),
                             index_t endianness = Endianness::DEFAULT_ID);
    
    void set_path(const std::string &path,
                  uint64 *data,
                  index_t num_elements = 1,
                  index_t offset = 0,
                  index_t stride = sizeof(conduit::uint64),
                  index_t element_bytes = sizeof(conduit::uint64),
                  index_t endianness = Endianness::DEFAULT_ID);

    //-------------------------------------------------------------------------
    // floating point integer pointer cases
    //-------------------------------------------------------------------------
    void set_path_float32_ptr(const std::string &path,
                              float32 *data,
                              index_t num_elements = 1,
                              index_t offset = 0,
                              index_t stride = sizeof(conduit::float32),
                              index_t element_bytes = sizeof(conduit::float32),
                              index_t endianness = Endianness::DEFAULT_ID);

    void set_path(const std::string &path,
                  float32 *data,
                  index_t num_elements = 1,
                  index_t offset = 0,
                  index_t stride = sizeof(conduit::float32),
                  index_t element_bytes = sizeof(conduit::float32),
                  index_t endianness = Endianness::DEFAULT_ID);

    //-------------------------------------------------------------------------
    void set_path_float64_ptr(const std::string &path,
                              float64 *data, 
                              index_t num_elements = 1,
                              index_t offset = 0,
                              index_t stride = sizeof(conduit::float64),
                              index_t element_bytes = sizeof(conduit::float64),
                              index_t endianness = Endianness::DEFAULT_ID);

    void set_path(const std::string &path,
                  float64 *data, 
                  index_t num_elements = 1,
                  index_t offset = 0,
                  index_t stride = sizeof(conduit::float64),
                  index_t element_bytes = sizeof(conduit::float64),
                  index_t endianness = Endianness::DEFAULT_ID);


//-----------------------------------------------------------------------------
///@}                      
//-----------------------------------------------------------------------------
//
// -- end declaration of Node set_path methods --
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//
// -- begin declaration of Node set_external methods --
//
//-----------------------------------------------------------------------------
///@name Node::set_external(...)
///@{
//-----------------------------------------------------------------------------
/// description:
///   set_external(...) methods methods follow pointer semantics.
///   (they do not copy data into the node, but point to the data passed)
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// -- set external for generic types --
//-----------------------------------------------------------------------------              
    //-------------------------------------------------------------------------
    void set_external_node(Node &n);
    void set_external(Node &n);

    //-------------------------------------------------------------------------
    void set_external_data_using_schema(const Schema &schema,
                                        void *data);

    void set_external(const Schema &schema,
                      void *data);

    //-------------------------------------------------------------------------
    void set_external_data_using_dtype(const DataType &dtype,
                                       void *data);

    void set_external(const DataType &dtype,
                      void *data);

//-----------------------------------------------------------------------------
// -- set_external via bitwidth style pointers (scalar and array types) -- 
//-----------------------------------------------------------------------------
    //-------------------------------------------------------------------------
    // signed integer pointer cases
    //-------------------------------------------------------------------------
    void set_external_int8_ptr(int8  *data,
                               index_t num_elements = 1,
                               index_t offset = 0,
                               index_t stride = sizeof(conduit::int8),
                               index_t element_bytes = sizeof(conduit::int8),
                               index_t endianness = Endianness::DEFAULT_ID);

    void set_external(int8  *data,
                      index_t num_elements = 1,
                      index_t offset = 0,
                      index_t stride = sizeof(conduit::int8),
                      index_t element_bytes = sizeof(conduit::int8),
                      index_t endianness = Endianness::DEFAULT_ID);
    
    //-------------------------------------------------------------------------
    void set_external_int16_ptr(int16 *data, 
                                index_t num_elements = 1,
                                index_t offset = 0,
                                index_t stride = sizeof(conduit::int16),
                                index_t element_bytes = sizeof(conduit::int16),
                                index_t endianness = Endianness::DEFAULT_ID);

    void set_external(int16 *data, 
                      index_t num_elements = 1,
                      index_t offset = 0,
                      index_t stride = sizeof(conduit::int16),
                      index_t element_bytes = sizeof(conduit::int16),
                      index_t endianness = Endianness::DEFAULT_ID);
    
    //-------------------------------------------------------------------------
    void set_external_int32_ptr(int32 *data,
                                index_t num_elements = 1,
                                index_t offset = 0,
                                index_t stride = sizeof(conduit::int32),
                                index_t element_bytes = sizeof(conduit::int32),
                                index_t endianness = Endianness::DEFAULT_ID);

    void set_external(int32 *data,
                      index_t num_elements = 1,
                      index_t offset = 0,
                      index_t stride = sizeof(conduit::int32),
                      index_t element_bytes = sizeof(conduit::int32),
                      index_t endianness = Endianness::DEFAULT_ID);
    
    //-------------------------------------------------------------------------
    void set_external_int64_ptr(int64 *data,
                                index_t num_elements = 1,
                                index_t offset = 0,
                                index_t stride = sizeof(conduit::int64),
                                index_t element_bytes = sizeof(conduit::int64),
                                index_t endianness = Endianness::DEFAULT_ID);

    void set_external(int64 *data,
                      index_t num_elements = 1,
                      index_t offset = 0,
                      index_t stride = sizeof(conduit::int64),
                      index_t element_bytes = sizeof(conduit::int64),
                      index_t endianness = Endianness::DEFAULT_ID);

    //-------------------------------------------------------------------------
    // unsigned integer pointer cases
    //-------------------------------------------------------------------------
    void set_external_uint8_ptr(uint8  *data,
                                index_t num_elements = 1,
                                index_t offset = 0,
                                index_t stride = sizeof(conduit::uint8),
                                index_t element_bytes = sizeof(conduit::uint8),
                                index_t endianness = Endianness::DEFAULT_ID);

    void set_external(uint8  *data,
                      index_t num_elements = 1,
                      index_t offset = 0,
                      index_t stride = sizeof(conduit::uint8),
                      index_t element_bytes = sizeof(conduit::uint8),
                      index_t endianness = Endianness::DEFAULT_ID);

    //-------------------------------------------------------------------------
    void set_external_uint16_ptr(uint16 *data,
                                 index_t num_elements = 1,
                                 index_t offset = 0,
                                 index_t stride = sizeof(conduit::uint16),
                                 index_t element_bytes = sizeof(conduit::uint16),
                                 index_t endianness = Endianness::DEFAULT_ID);

    void set_external(uint16 *data,
                      index_t num_elements = 1,
                      index_t offset = 0,
                      index_t stride = sizeof(conduit::uint16),
                      index_t element_bytes = sizeof(conduit::uint16),
                      index_t endianness = Endianness::DEFAULT_ID);

    //-------------------------------------------------------------------------
    void set_external_uint32_ptr(uint32 *data, 
                                 index_t num_elements = 1,
                                 index_t offset = 0,
                                 index_t stride = sizeof(conduit::uint32),
                                 index_t element_bytes = sizeof(conduit::uint32),
                                 index_t endianness = Endianness::DEFAULT_ID);

    void set_external(uint32 *data, 
                      index_t num_elements = 1,
                      index_t offset = 0,
                      index_t stride = sizeof(conduit::uint32),
                      index_t element_bytes = sizeof(conduit::uint32),
                      index_t endianness = Endianness::DEFAULT_ID);
                      
    //-------------------------------------------------------------------------
    void set_external_uint64_ptr(uint64 *data,
                                 index_t num_elements = 1,
                                 index_t offset = 0,
                                 index_t stride = sizeof(conduit::uint64),
                                 index_t element_bytes = sizeof(conduit::uint64),
                                 index_t endianness = Endianness::DEFAULT_ID);

    void set_external(uint64 *data,
                      index_t num_elements = 1,
                      index_t offset = 0,
                      index_t stride = sizeof(conduit::uint64),
                      index_t element_bytes = sizeof(conduit::uint64),
                      index_t endianness = Endianness::DEFAULT_ID);

    //-------------------------------------------------------------------------
    // floating point pointer cases
    //-------------------------------------------------------------------------
    void set_external_float32_ptr(float32 *data,
                                  index_t num_elements = 1,
                                  index_t offset = 0,
                                  index_t stride = sizeof(conduit::float32),
                                  index_t element_bytes = sizeof(conduit::float32),
                                  index_t endianness = Endianness::DEFAULT_ID);

    void set_external(float32 *data,
                      index_t num_elements = 1,
                      index_t offset = 0,
                      index_t stride = sizeof(conduit::float32),
                      index_t element_bytes = sizeof(conduit::float32),
                      index_t endianness = Endianness::DEFAULT_ID);

    //-------------------------------------------------------------------------
    void set_external_float64_ptr(float64 *data, 
                                  index_t num_elements = 1,
                                  index_t offset = 0,
                                  index_t stride = sizeof(conduit::float64),
                                  index_t element_bytes = sizeof(conduit::float64),
                                  index_t endianness = Endianness::DEFAULT_ID);

    void set_external(float64 *data, 
                      index_t num_elements = 1,
                      index_t offset = 0,
                      index_t stride = sizeof(conduit::float64),
                      index_t element_bytes = sizeof(conduit::float64),
                      index_t endianness = Endianness::DEFAULT_ID);

//-----------------------------------------------------------------------------
// -- set_external for conduit::DataArray types ---
//-----------------------------------------------------------------------------

    //-------------------------------------------------------------------------
    // signed integer array types via conduit::DataArray
    //-------------------------------------------------------------------------
    void set_external_int8_array(const int8_array &data);
    void set_external(const int8_array &data);
    
    //-------------------------------------------------------------------------
    void set_external_int16_array(const int16_array &data);
    void set_external(const int16_array &data);
    
    //-------------------------------------------------------------------------
    void set_external_int32_array(const int32_array &data);
    void set_external(const int32_array &data);
    
    //-------------------------------------------------------------------------
    void set_external_int64_array(const int64_array &data);
    void set_external(const int64_array &data);

    //-------------------------------------------------------------------------
    // unsigned integer array types via conduit::DataArray
    //-------------------------------------------------------------------------
    void set_external_uint8_array(const uint8_array  &data);
    void set_external(const uint8_array  &data);

    //-------------------------------------------------------------------------
    void set_external_uint16_array(const uint16_array &data);
    void set_external(const uint16_array &data);

    //-------------------------------------------------------------------------
    void set_external_uint32_array(const uint32_array &data);
    void set_external(const uint32_array &data);
    
    //-------------------------------------------------------------------------
    void set_external_uint64_array(const uint64_array &data);
    void set_external(const uint64_array &data);

    //-------------------------------------------------------------------------
    // floating point array types via conduit::DataArray
    //-------------------------------------------------------------------------
    void set_external_float32_array(const float32_array &data);
    void set_external(const float32_array &data);

    //-------------------------------------------------------------------------
    void set_external_float64_array(const float64_array &data);
    void set_external(const float64_array &data);

//-----------------------------------------------------------------------------
// -- set_external for string types ---
//-----------------------------------------------------------------------------
    void set_external_char8_str(char *data);

//-----------------------------------------------------------------------------
// -- set_external for bitwidth style std::vector types ---
//----------------------------------------------------------------------------- 

    //-------------------------------------------------------------------------
    // signed integer array types via std::vector
    //-------------------------------------------------------------------------
    void set_external_int8_vector(std::vector<int8> &data);
    void set_external(std::vector<int8> &data);

    //-------------------------------------------------------------------------
    void set_external_int16_vector(std::vector<int16> &data);
    void set_external(std::vector<int16> &data);

    //-------------------------------------------------------------------------
    void set_external_int32_vector(std::vector<int32> &data);
    void set_external(std::vector<int32> &data);
    
    //-------------------------------------------------------------------------
    void set_external_int64_vector(std::vector<int64> &data);
    void set_external(std::vector<int64> &data);

    //-------------------------------------------------------------------------
    // unsigned integer array types via std::vector
    //-------------------------------------------------------------------------
    void set_external_uint8_vector(std::vector<uint8> &data);
    void set_external(std::vector<uint8> &data);
    
    //-------------------------------------------------------------------------
    void set_external_uint16_vector(std::vector<uint16> &data);
    void set_external(std::vector<uint16> &data);
    
    //-------------------------------------------------------------------------
    void set_external_uint32_vector(std::vector<uint32> &data);
    void set_external(std::vector<uint32> &data);
    
    //-------------------------------------------------------------------------
    void set_external_uint64_vector(std::vector<uint64> &data);
    void set_external(std::vector<uint64> &data);

    //-------------------------------------------------------------------------
    // floating point array types via std::vector
    //-------------------------------------------------------------------------
    void set_external_float32_vector(std::vector<float32> &data);
    void set_external(std::vector<float32> &data);

    //-------------------------------------------------------------------------
    void set_external_float64_vector(std::vector<float64> &data);
    void set_external(std::vector<float64> &data);


//-----------------------------------------------------------------------------
///@}                      
//-----------------------------------------------------------------------------
//
// -- end  declaration of Node set_external methods --
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//
// -- begin declaration of Node set_path_external methods --
//
//-----------------------------------------------------------------------------
///@name Node::set_path_external(...)
///@{
//-----------------------------------------------------------------------------
/// description:
///   set_path_external(...) methods allow the node to point to external
///   memory, and allow you to use an explicit path for the destination node.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// -- set path external for generic types --
//-----------------------------------------------------------------------------

    //-------------------------------------------------------------------------    
    void    set_path_external_node(const std::string &path,
                                   Node &node);

    void    set_path_external(const std::string &path,
                              Node &node);

    //-------------------------------------------------------------------------
    void    set_path_external_data_using_schema(const std::string &path,
                                                const Schema &schema,
                                                void *data);
    
    void    set_path_external(const std::string &path,
                              const Schema &schema,
                              void *data);

    //-------------------------------------------------------------------------
    void    set_path_external_data_using_dtype(const std::string &path,
                                               const DataType &dtype,
                                               void *data);

    void    set_path_external(const std::string &path,
                              const DataType &dtype,
                              void *data);

//-----------------------------------------------------------------------------
// -- set_path_external via bitwidth style pointers (scalar and array types) -- 
//-----------------------------------------------------------------------------
    //-------------------------------------------------------------------------
    // signed integer pointer cases
    //-------------------------------------------------------------------------
    void set_path_external_int8_ptr(const std::string &path,
                                    int8  *data,
                                    index_t num_elements = 1,
                                    index_t offset = 0,
                                    index_t stride = sizeof(conduit::int8),
                                    index_t element_bytes = sizeof(conduit::int8),
                                    index_t endianness = Endianness::DEFAULT_ID);

    void set_path_external(const std::string &path,
                           int8  *data,
                           index_t num_elements = 1,
                           index_t offset = 0,
                           index_t stride = sizeof(conduit::int8),
                           index_t element_bytes = sizeof(conduit::int8),
                           index_t endianness = Endianness::DEFAULT_ID);

    //-------------------------------------------------------------------------
    void set_path_external_int16_ptr(const std::string &path,
                                     int16 *data, 
                                     index_t num_elements = 1,
                                     index_t offset = 0,
                                     index_t stride = sizeof(conduit::int16),
                                     index_t element_bytes = sizeof(conduit::int16),
                                     index_t endianness = Endianness::DEFAULT_ID);


    void set_path_external(const std::string &path,
                           int16 *data, 
                           index_t num_elements = 1,
                           index_t offset = 0,
                           index_t stride = sizeof(conduit::int16),
                           index_t element_bytes = sizeof(conduit::int16),
                           index_t endianness = Endianness::DEFAULT_ID);
 
    //-------------------------------------------------------------------------
    void set_path_external_int32_ptr(const std::string &path,
                                     int32 *data,
                                     index_t num_elements = 1,
                                     index_t offset = 0,
                                     index_t stride = sizeof(conduit::int32),
                                     index_t element_bytes = sizeof(conduit::int32),
                                     index_t endianness = Endianness::DEFAULT_ID);

    void set_path_external(const std::string &path,
                           int32 *data,
                           index_t num_elements = 1,
                           index_t offset = 0,
                           index_t stride = sizeof(conduit::int32),
                           index_t element_bytes = sizeof(conduit::int32),
                           index_t endianness = Endianness::DEFAULT_ID);

    //-------------------------------------------------------------------------
    void set_path_external_int64_ptr(const std::string &path,
                                     int64 *data,
                                     index_t num_elements = 1,
                                     index_t offset = 0,
                                     index_t stride = sizeof(conduit::int64),
                                     index_t element_bytes = sizeof(conduit::int64),
                                     index_t endianness = Endianness::DEFAULT_ID);

    void set_path_external(const std::string &path,
                           int64 *data,
                           index_t num_elements = 1,
                           index_t offset = 0,
                           index_t stride = sizeof(conduit::int64),
                           index_t element_bytes = sizeof(conduit::int64),
                           index_t endianness = Endianness::DEFAULT_ID);

    //-------------------------------------------------------------------------
    // unsigned integer pointer cases
    //-------------------------------------------------------------------------
    void set_path_external_uint8_ptr(const std::string &path,
                                     uint8  *data,
                                     index_t num_elements = 1,
                                     index_t offset = 0,
                                     index_t stride = sizeof(conduit::uint8),
                                     index_t element_bytes = sizeof(conduit::uint8),
                                     index_t endianness = Endianness::DEFAULT_ID);

    void set_path_external(const std::string &path,
                           uint8  *data,
                           index_t num_elements = 1,
                           index_t offset = 0,
                           index_t stride = sizeof(conduit::uint8),
                           index_t element_bytes = sizeof(conduit::uint8),
                           index_t endianness = Endianness::DEFAULT_ID);

    //-------------------------------------------------------------------------
    void set_path_external_uint16_ptr(const std::string &path,
                                      uint16 *data,
                                      index_t num_elements = 1,
                                      index_t offset = 0,
                                      index_t stride = sizeof(conduit::uint16),
                                      index_t element_bytes = sizeof(conduit::uint16),
                                      index_t endianness = Endianness::DEFAULT_ID);

    void set_path_external(const std::string &path,
                           uint16 *data,
                           index_t num_elements = 1,
                           index_t offset = 0,
                           index_t stride = sizeof(conduit::uint16),
                           index_t element_bytes = sizeof(conduit::uint16),
                           index_t endianness = Endianness::DEFAULT_ID);

    //-------------------------------------------------------------------------
    void set_path_external_uint32_ptr(const std::string &path,
                                      uint32 *data, 
                                      index_t num_elements = 1,
                                      index_t offset = 0,
                                      index_t stride = sizeof(conduit::uint32),
                                      index_t element_bytes = sizeof(conduit::uint32),
                                      index_t endianness = Endianness::DEFAULT_ID);

    void set_path_external(const std::string &path,
                           uint32 *data, 
                           index_t num_elements = 1,
                           index_t offset = 0,
                           index_t stride = sizeof(conduit::uint32),
                           index_t element_bytes = sizeof(conduit::uint32),
                           index_t endianness = Endianness::DEFAULT_ID);

    //-------------------------------------------------------------------------
    void set_path_external_uint64_ptr(const std::string &path,
                                      uint64 *data,
                                      index_t num_elements = 1,
                                      index_t offset = 0,
                                      index_t stride = sizeof(conduit::uint64),
                                      index_t element_bytes = sizeof(conduit::uint64),
                                      index_t endianness = Endianness::DEFAULT_ID);

    void set_path_external(const std::string &path,
                           uint64 *data,
                           index_t num_elements = 1,
                           index_t offset = 0,
                           index_t stride = sizeof(conduit::uint64),
                           index_t element_bytes = sizeof(conduit::uint64),
                           index_t endianness = Endianness::DEFAULT_ID);

    //-------------------------------------------------------------------------
    // floating point pointer cases
    //-------------------------------------------------------------------------
    void set_path_external_float32_ptr(const std::string &path,
                                       float32 *data,
                                       index_t num_elements = 1,
                                       index_t offset = 0,
                                       index_t stride = sizeof(conduit::float32),
                                       index_t element_bytes = sizeof(conduit::float32),
                                       index_t endianness = Endianness::DEFAULT_ID);

    void set_path_external(const std::string &path,
                           float32 *data,
                           index_t num_elements = 1,
                           index_t offset = 0,
                           index_t stride = sizeof(conduit::float32),
                           index_t element_bytes = sizeof(conduit::float32),
                           index_t endianness = Endianness::DEFAULT_ID);

    //-------------------------------------------------------------------------
    void set_path_external_float64_ptr(const std::string &path,
                                       float64 *data, 
                                       index_t num_elements = 1,
                                       index_t offset = 0,
                                       index_t stride = sizeof(conduit::float64),
                                       index_t element_bytes = sizeof(conduit::float64),
                                       index_t endianness = Endianness::DEFAULT_ID);

    void set_path_external(const std::string &path,
                           float64 *data, 
                           index_t num_elements = 1,
                           index_t offset = 0,
                           index_t stride = sizeof(conduit::float64),
                           index_t element_bytes = sizeof(conduit::float64),
                           index_t endianness = Endianness::DEFAULT_ID);


//-----------------------------------------------------------------------------
// -- set_path_external for conduit::DataArray types ---
//-----------------------------------------------------------------------------

    //-------------------------------------------------------------------------
    // signed integer array types via conduit::DataArray
    //-------------------------------------------------------------------------
    void set_path_external_int8_array(const std::string &path,
                                      const int8_array &data);

    void set_path_external(const std::string &path,
                           const int8_array  &data);

    //-------------------------------------------------------------------------
    void set_path_external_int16_array(const std::string &path,
                                       const int16_array &data);

    void set_path_external(const std::string &path,
                           const int16_array &data);

    //-------------------------------------------------------------------------
    void set_path_external_int32_array(const std::string &path,
                                       const int32_array &data);

    void set_path_external(const std::string &path,
                           const int32_array &data);

    //-------------------------------------------------------------------------
    void set_path_external_int64_array(const std::string &path,
                                       const int64_array &data);

    void set_path_external(const std::string &path,
                           const int64_array &data);

    //-------------------------------------------------------------------------
    // unsigned integer array types via conduit::DataArray
    //-------------------------------------------------------------------------
    void set_path_external_uint8_array(const std::string &path,
                                       const uint8_array &data);

    void set_path_external(const std::string &path,
                           const uint8_array &data);

    //-------------------------------------------------------------------------
    void set_path_external_uint16_array(const std::string &path,
                                        const uint16_array &data);

    void set_path_external(const std::string &path,
                           const uint16_array &data);

    //-------------------------------------------------------------------------
    void set_path_external_uint32_array(const std::string &path,
                                        const uint32_array &data);

    void set_path_external(const std::string &path,
                           const uint32_array &data);

    //-------------------------------------------------------------------------
    void set_path_external_uint64_array(const std::string &path,
                                        const uint64_array &data);

    void set_path_external(const std::string &path,
                           const uint64_array &data);

    //-------------------------------------------------------------------------
    // floating point array types via conduit::DataArray
    //-------------------------------------------------------------------------
    void set_path_external_float32_array(const std::string &path,
                                         const float32_array &data);

    void set_path_external(const std::string &path,
                           const float32_array &data);

    //-------------------------------------------------------------------------
    void set_path_external_float64_array(const std::string &path,
                                         const float64_array &data);

    void set_path_external(const std::string &path,
                          const float64_array &data);

//-----------------------------------------------------------------------------
// -- set_external for string types ---
//-----------------------------------------------------------------------------
    void set_path_external_char8_str(const std::string &path, char *data);

//-----------------------------------------------------------------------------
// -- set_path_external for bitwidth style std::vector types ---
//-----------------------------------------------------------------------------
    
    //-------------------------------------------------------------------------
    // signed integer array types via std::vector
    //-------------------------------------------------------------------------
    void set_path_external_int8_vector(const std::string &path,
                                       std::vector<int8> &data);

    void set_path_external(const std::string &path,
                           std::vector<int8> &data);

    //-------------------------------------------------------------------------
    void set_path_external_int16_vector(const std::string &path,
                                        std::vector<int16> &data);

    void set_path_external(const std::string &path,
                           std::vector<int16> &data);

    //-------------------------------------------------------------------------
    void set_path_external_int32_vector(const std::string &path,
                                        std::vector<int32> &data);

    void set_path_external(const std::string &path,
                           std::vector<int32> &data);

    //-------------------------------------------------------------------------
    void set_path_external_int64_vector(const std::string &path,
                                        std::vector<int64> &data);

    void set_path_external(const std::string &path,
                           std::vector<int64> &data);

    //-------------------------------------------------------------------------
    // unsigned integer array types via std::vector
    //-------------------------------------------------------------------------
    void set_path_external_uint8_vector(const std::string &path,
                                        std::vector<uint8> &data);

    void set_path_external(const std::string &path,
                           std::vector<uint8> &data);

    //-------------------------------------------------------------------------
    void set_path_external_uint16_vector(const std::string &path,
                                         std::vector<uint16> &data);

    void set_path_external(const std::string &path,
                           std::vector<uint16> &data);

    //-------------------------------------------------------------------------
    void set_path_external_uint32_vector(const std::string &path,
                                         std::vector<uint32> &data);

    void set_path_external(const std::string &path,
                           std::vector<uint32> &data);

    //-------------------------------------------------------------------------
    void set_path_external_uint64_vector(const std::string &path,
                                         std::vector<uint64> &data);

    void set_path_external(const std::string &path,
                           std::vector<uint64> &data);

    //-------------------------------------------------------------------------
    // floating point array types via std::vector
    //-------------------------------------------------------------------------
    void set_path_external_float32_vector(const std::string &path,
                                          std::vector<float32> &data);

    void set_path_external(const std::string &path,
                           std::vector<float32> &data);

    //-------------------------------------------------------------------------
    void set_path_external_float64_vector(const std::string &path,
                                          std::vector<float64> &data);

    void set_path_external(const std::string &path,
                           std::vector<float64> &data);

//-----------------------------------------------------------------------------
///@}                      
//-----------------------------------------------------------------------------
//
// -- end declaration of Node set_path_external methods --
//
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//
// -- begin declaration of Node assignment operators --
//
//-----------------------------------------------------------------------------
///@name Node Assignment Operators
///@{
//-----------------------------------------------------------------------------
/// description:
/// &operator=(...) methods use set(...) (copy) semantics
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// -- assignment operators for generic types --
//-----------------------------------------------------------------------------
    Node &operator=(const Node &node);
    Node &operator=(const DataType &dtype);
    Node &operator=(const Schema  &schema);

//-----------------------------------------------------------------------------
// --  assignment operators for scalar types ---
//-----------------------------------------------------------------------------
     // signed integer scalar types
    Node &operator=(int8 data);
    Node &operator=(int16 data);
    Node &operator=(int32 data);
    Node &operator=(int64 data);

     // unsigned integer scalar types
    Node &operator=(uint8 data);
    Node &operator=(uint16 data);
    Node &operator=(uint32 data);
    Node &operator=(uint64 data);
    
    // floating point scalar types
    Node &operator=(float32 data);    
    Node &operator=(float64 data);

//-----------------------------------------------------------------------------
// -- assignment operators for std::vector types ---
//-----------------------------------------------------------------------------

    // signed integer array types via std::vector
    Node &operator=(const std::vector<int8>   &data);
    Node &operator=(const std::vector<int16>  &data);
    Node &operator=(const std::vector<int32>  &data);
    Node &operator=(const std::vector<int64>  &data);

    // unsigned integer array types via std::vector
    Node &operator=(const std::vector<uint8>   &data);
    Node &operator=(const std::vector<uint16>  &data);
    Node &operator=(const std::vector<uint32>  &data);
    Node &operator=(const std::vector<uint64>  &data);

    // floating point array types via std::vector
    Node &operator=(const std::vector<float32> &data);
    Node &operator=(const std::vector<float64> &data);

//-----------------------------------------------------------------------------
// -- assignment operators for conduit::DataArray types ---
//-----------------------------------------------------------------------------
    // signed integer array types via conduit::DataArray
    Node &operator=(const int8_array  &data);
    Node &operator=(const int16_array &data);
    Node &operator=(const int32_array &data);
    Node &operator=(const int64_array &data);

    // unsigned integer array ttypes via conduit::DataArray
    Node &operator=(const uint8_array  &data);
    Node &operator=(const uint16_array &data);
    Node &operator=(const uint32_array &data);
    Node &operator=(const uint64_array &data);

    // floating point array types via conduit::DataArray
    Node &operator=(const float32_array &data);
    Node &operator=(const float64_array &data);

//-----------------------------------------------------------------------------
// -- assignment operators for string types -- 
//-----------------------------------------------------------------------------
    // char8_str use cases
    Node &operator=(const char *data);
    Node &operator=(const std::string &data);

//-----------------------------------------------------------------------------
///@}                      
//-----------------------------------------------------------------------------
//
// -- end declaration of Node assignment operators --
//
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//
// -- begin declaration of Node transforms --
//
//-----------------------------------------------------------------------------
///@name Node Transforms
///@{
//-----------------------------------------------------------------------------
/// description:
///  TODO
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// -- serialization methods ---
//-----------------------------------------------------------------------------
    /// serialize to a byte vector
    void        serialize(std::vector<uint8> &data) const;
    /// serialize to a file identified by stream_path
    void        serialize(const std::string &stream_path) const;
    /// serialize to an output stream
    void        serialize(std::ofstream &ofs) const;

//-----------------------------------------------------------------------------
// -- compaction methods ---
//-----------------------------------------------------------------------------
    /// compact this node
    void        compact();

    /// compact into a new node
    void        compact_to(Node &n_dest) const;

    /// compact and return the result
    /// TODO: this is inefficient w/o move semantics, but is very 
    /// convenient for testing and example programs.
    Node        compact_to() const;

//-----------------------------------------------------------------------------
// -- update methods ---
//-----------------------------------------------------------------------------
    /// update() adds children from n_src to current Node (analogous to a 
    /// python dictionary update) 
    ///
    /// NOTE: The input should be const, but the lack of a const fetch prevents
    /// this for now.
    void        update(Node &n_src);
    /// TODO: update_external?


//-----------------------------------------------------------------------------
// -- endian related --
//-----------------------------------------------------------------------------
    void endian_swap(index_t endianness);

    void endian_swap_to_machine_default()
        {endian_swap(Endianness::DEFAULT_ID);}
    
    void endian_swap_to_little()
        {endian_swap(Endianness::LITTLE_ID);}
    
    void endian_swap_to_big()
        {endian_swap(Endianness::BIG_ID);}


//-----------------------------------------------------------------------------
// -- leaf coercion methods ---
//-----------------------------------------------------------------------------
    ///
    /// These methods allow you to coerce a leaf type to another type.
    ///
    
    /// scalar coercion

    /// convert to a signed integer types
    int8             to_int8()   const;
    int16            to_int16()  const;
    int32            to_int32()  const;
    int64            to_int64()  const;
    
    /// convert to a unsigned integer types
    uint8            to_uint8()   const;
    uint16           to_uint16()  const;
    uint32           to_uint32()  const;
    uint64           to_uint64()  const;
    
    /// convert to a floating point type
    float32          to_float32() const;
    float64          to_float64() const;
    
    /// convert to the index type 
    index_t          to_index_t() const;

    /// convert to c signed integer types
    char             to_char()  const;
    short            to_short() const;
    int              to_int()   const;
    long             to_long()  const;

    /// convert to c unsigned integer types
    unsigned char    to_unsigned_char()  const;
    unsigned short   to_unsigned_short() const;
    unsigned int     to_unsigned_int()   const;
    unsigned long    to_unsigned_long()  const;

    /// convert to c floating point types
    float            to_float() const;
    double           to_double() const;

//-----------------------------------------------------------------------------
// -- array conversion methods -- 
// 
/// These methods convert an array to a specific array type.
/// The result is stored in the passed node.
//-----------------------------------------------------------------------------

    /// convert to a signed integer types
    void    to_int8_array(Node &res)  const;
    void    to_int16_array(Node &res) const;
    void    to_int32_array(Node &res) const;    
    void    to_int64_array(Node &res) const;    
    
    /// convert to a unsigned integer types
    void    to_uint8_array(Node &res)  const;
    void    to_uint16_array(Node &res) const;
    void    to_uint32_array(Node &res) const;    
    void    to_uint64_array(Node &res) const;    
    
    /// convert to a floating point type
    void    to_float32_array(Node &res) const;    
    void    to_float64_array(Node &res) const;    
    
    /// convert to c signed integer types
    void    to_char_array(Node &res)  const;
    void    to_short_array(Node &res) const;
    void    to_int_array(Node &res)   const;
    void    to_long_array(Node &res)  const;
    
    /// convert to c unsigned integer types
    void    to_unsigned_char_array(Node &res)  const;
    void    to_unsigned_short_array(Node &res) const;
    void    to_unsigned_int_array(Node &res)   const;
    void    to_unsigned_long_array(Node &res)  const;

    /// convert to c floating point types
    void    to_float_array(Node &res) const;
    void    to_double_array(Node &res) const;


//-----------------------------------------------------------------------------
// -- Node::Value Helper class --
//
// This class allows us to support casting return semantics.
// we can't support these methods directly in conduit::Node  because doing so
// undermines our operator=() overloads. 
//-----------------------------------------------------------------------------
    class Value
    {
        friend class Node;
        public:
            ~Value();
            Value(const Value &rhs);
            // cast operators for signed integers
            
            // we need an explicit case for signed char
            operator signed char() const;
            operator short()       const;
            operator int()         const;
            operator long()        const;
            #ifdef CONDUIT_USE_LONG_LONG
                operator long long()const;
            #endif


            // cast operators for unsigned integers
            operator unsigned char()   const;
            operator unsigned short()  const;
            operator unsigned int()    const;
            operator unsigned long()   const;
            #ifdef CONDUIT_USE_LONG_LONG
                operator unsigned long long()const;
            #endif
            
            // cast operators for floating point types
            operator float()  const;
            operator double() const;
            #ifdef CONDUIT_USE_LONG_DOUBLE
                operator long double()const;
            #endif
            
        
            // -- as pointer -- //

            // as signed int ptr
            operator char*()        const;
            // we need an explicit case for signed char, due to how int8 
            // is implemented
            operator signed char*() const;
            operator short*()       const;
            operator int*()         const;
            operator long*()        const;
            #ifdef CONDUIT_USE_LONG_LONG
                operator long long *()const;
            #endif

            // as unsigned int ptr
            operator unsigned char*()  const;
            operator unsigned short*() const;
            operator unsigned int*()   const;
            operator unsigned long*()  const;
            #ifdef CONDUIT_USE_LONG_LONG
                operator unsigned long long *()const;
            #endif

            
            // as floating point ptr
            operator float*()  const;
            operator double*() const;
            #ifdef CONDUIT_USE_LONG_DOUBLE
                operator long double *()const;
            #endif


            // -- as array -- //

            operator char_array()  const;
            operator short_array() const;
            operator int_array()   const;
            operator long_array()  const;
            #ifdef CONDUIT_USE_LONG_LONG
                operator long_long_array()const;
            #endif
            

            operator unsigned_char_array()  const;
            operator unsigned_short_array() const;
            operator unsigned_int_array()   const;
            operator unsigned_long_array()  const;
            #ifdef CONDUIT_USE_LONG_LONG
                operator unsigned_long_long_array()const;
            #endif


            operator float_array()  const;
            operator double_array() const;
            #ifdef CONDUIT_USE_LONG_DOUBLE
                operator long_double_array()const;
            #endif


        private:
            // This is private we only want conduit::Node to create a 
            // conduit::Node::Value instance
            Value(Node *node, bool coerse);
            // holds the node with the actually data
            Node    *m_node;
            // coercion flag, note - only scalars types can be coerced 
            bool     m_coerse; 
    };
    

//-----------------------------------------------------------------------------
// -- Node methods that use the Node::Value class as a casting vehicle.
//-----------------------------------------------------------------------------

    Value value()  // works for all leaf types, but no coercion
        { return  Value(this,false); }

    Value to_value()  // only works for scalar leaf types
        { return  Value(this,true); }


//-----------------------------------------------------------------------------
// -- JSON construction methods ---
//-----------------------------------------------------------------------------
    // accepted protocols:
    //   "json"
    //   "conduit"
    //   "base64_json"
    std::string         to_json(const std::string &protocol="json", 
                                index_t indent=2, 
                                index_t depth=0,
                                const std::string &pad=" ",
                                const std::string &eoe="\n") const;

    void                to_json_stream(std::ostream &os,
                                       const std::string &protocol="json",
                                       index_t indent=2, 
                                       index_t depth=0,
                                       const std::string &pad=" ",
                                       const std::string &eoe="\n") const;

    void                to_json_stream(const std::string &stream_path,
                                       const std::string &protocol="json",
                                       index_t indent=2, 
                                       index_t depth=0,
                                       const std::string &pad=" ",
                                       const std::string &eoe="\n") const;



//-----------------------------------------------------------------------------
//
// -- end declaration of Node transforms --
//
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//
// -- begin declaration of Node information methods --
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
///@name Node Information
///@{
//-----------------------------------------------------------------------------
/// description:
///  These methods provide general info about the node hierarchy, and memory 
///  layout.
//-----------------------------------------------------------------------------
    // schema access
    const Schema     &schema() const 
                        { return *m_schema;}   

    const DataType   &dtype() const       
                        { return m_schema->dtype();}

    Schema          *schema_ptr() 
                        {return m_schema;}

    // check if data owned by this node is externally
    // allocated.
    bool             is_data_external() const
                        {return !m_alloced;}
    // check if this node is the root of a tree nodes.
    bool             is_root() const 
                        {return m_parent == NULL;}
    // parent access
    Node            *parent() 
                        {return m_parent;}
    
    //memory space info
    index_t          total_bytes() const 
                        { return m_schema->total_bytes();}
    index_t          total_bytes_compact() const
                        { return m_schema->total_bytes_compact();}

    /// is this node using a compact data layout
    bool             is_compact() const 
                        {return dtype().is_compact();}
    ///
    /// info() creates a node that contains metadata about the current
    /// node's memory properties
    void             info(Node &nres) const;
    /// TODO: this is inefficient w/o move semantics, but is very 
    /// convenient for testing and example programs.
    Node             info() const;

    /// TODO: compare or operator== ?

//-----------------------------------------------------------------------------
// -- stdout print methods ---
//-----------------------------------------------------------------------------
    /// print a simplified json representation of the this node to std out
    void            print() const;

    /// print a detailed json representation of the this node to std out.
    /// json output includes conduit schema constructs
    void            print_detailed() const;

//-----------------------------------------------------------------------------
///@}
//-----------------------------------------------------------------------------
//
// -- end declaration of Node information methods --
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//
// -- begin declaration of Node entry access methods --
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
///@name Node Entry Access Methods
///@{
//-----------------------------------------------------------------------------
/// description:
///  Node traversal (iterators), child access (for list or object types)
//-----------------------------------------------------------------------------
    /// return a iterator that give access to this nodes children
    NodeIterator     children();
    
    /// `fetch' methods do modify map structure if a path doesn't exist
    /// fetch the node at the given path
    Node             &fetch(const std::string &path);
    /// fetch the node at the given index
    Node             &child(index_t idx);

    /// fetch a pointer to the node  at the given path   
    Node             *fetch_ptr(const std::string &path);
    /// fetch a pointer to the node at the given index
    Node             *child_ptr(index_t idx);

    /// access child node via a path (equivalent to fetch via path)
    Node             &operator[](const std::string &path);
    /// access child node via index (equivalent to fetch via index)
    Node             &operator[](index_t idx);

    /// return the number of children (list and object interfaces)
    index_t number_of_children() const;
    
    /// checks if given path exists in the Node hierarchy 
    bool    has_path(const std::string &path) const;
    /// returns the direct child paths for this node
    void    paths(std::vector<std::string> &paths) const;

    /// adds an empty unnamed node to a list (list interface)
    /// TODO `append` is a strange name here, we want this interface
    /// but we may be abusing the common concept folks think of
    //  for the term `append`.
    Node   &append();

    /// remove child at index (list and object interfaces)
    void    remove(index_t idx);
    /// remove child at given path (object interface)
    void    remove(const std::string &path);


    /// helpers to create a list of a homogenous type
    void list_of(const Schema &schema,
                 index_t num_entries);
    
    void list_of_external(void *data,
                          const Schema &schema,
                          index_t num_entries);


//-----------------------------------------------------------------------------
///@}
//-----------------------------------------------------------------------------
//
// -- end declaration of Node entry access methods --
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//
// -- begin declaration of Node value access methods --
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
///@name Node Value Access Methods
///@{
//-----------------------------------------------------------------------------
/// description:
///  Direct access to data at leaf types.
//-----------------------------------------------------------------------------
     
     // signed integer scalars
    int8             as_int8()   const;
    int16            as_int16()  const;
    int32            as_int32()  const;
    int64            as_int64()  const;

    // unsigned integer scalars
    uint8            as_uint8()   const;
    uint16           as_uint16()  const;
    uint32           as_uint32()  const;
    uint64           as_uint64()  const;

    // floating point scalars
    float32          as_float32() const;
    float64          as_float64() const;

    // signed integers via pointers
    int8            *as_int8_ptr();
    int16           *as_int16_ptr();
    int32           *as_int32_ptr();
    int64           *as_int64_ptr();

    // unsigned integers via pointers
    uint8           *as_uint8_ptr();
    uint16          *as_uint16_ptr();
    uint32          *as_uint32_ptr();
    uint64          *as_uint64_ptr();

    // floating point via pointers
    float32         *as_float32_ptr();
    float64         *as_float64_ptr();

    // signed integers via pointers
    const int8      *as_int8_ptr()   const;
    const int16     *as_int16_ptr()  const;
    const int32     *as_int32_ptr()  const;
    const int64     *as_int64_ptr()  const;

    // unsigned integers via pointers
    const uint8     *as_uint8_ptr()  const;
    const uint16    *as_uint16_ptr() const;
    const uint32    *as_uint32_ptr() const;
    const uint64    *as_uint64_ptr() const;

    // floating point via pointers
    const float32   *as_float32_ptr() const;
    const float64   *as_float64_ptr() const;

    // signed integer array types via conduit::DataArray
    int8_array       as_int8_array();
    int16_array      as_int16_array();
    int32_array      as_int32_array();
    int64_array      as_int64_array();

    // unsigned integer array types via conduit::DataArray
    uint8_array      as_uint8_array();
    uint16_array     as_uint16_array();
    uint32_array     as_uint32_array();
    uint64_array     as_uint64_array();

    // floating point array types via conduit::DataArray
    float32_array    as_float32_array();
    float64_array    as_float64_array();

    // signed integer array types via conduit::DataArray (const variants)

    const int8_array       as_int8_array()  const;
    const int16_array      as_int16_array() const;
    const int32_array      as_int32_array() const;
    const int64_array      as_int64_array() const;

    // unsigned integer array types via conduit::DataArray (const variants)
    const uint8_array      as_uint8_array()  const;
    const uint16_array     as_uint16_array() const;
    const uint32_array     as_uint32_array() const;
    const uint64_array     as_uint64_array() const;

    // floating point array value via conduit::DataArray (const variants)
    const float32_array    as_float32_array() const;
    const float64_array    as_float64_array() const;

    // char8_str cases
    char            *as_char8_str();
    const char      *as_char8_str() const;
    std::string      as_string()    const;

    // direct data pointer access 
    void            *data_ptr();
    const void      *data_ptr() const;

    void  *element_ptr(index_t idx)
        {return static_cast<char*>(m_data) + dtype().element_index(idx);};
    const void  *element_ptr(index_t idx) const 
        {return static_cast<char*>(m_data) + dtype().element_index(idx);};

//-----------------------------------------------------------------------------
/// description:
///  Direct access to data at leaf types (native c++ types)
//-----------------------------------------------------------------------------
     
     // signed integer scalars
    char           as_char()  const;
    short          as_short() const;
    int            as_int()   const;
    long           as_long()  const;

    // unsigned integer scalars
    unsigned char    as_unsigned_char()  const;
    unsigned short   as_unsigned_short() const;
    
    unsigned int     as_unsigned_int()   const;
    unsigned long    as_unsigned_long()  const;

    // floating point scalars
    float            as_float() const;
    double           as_double() const;

    // signed integers via pointers
    char            *as_char_ptr();
    short           *as_short_ptr();
    int             *as_int_ptr();
    long            *as_long_ptr();

    // unsigned integers via pointers
    unsigned char   *as_unsigned_char_ptr();
    unsigned short  *as_unsigned_short_ptr();
    unsigned int    *as_unsigned_int_ptr();
    unsigned long   *as_unsigned_long_ptr();

    // floating point via pointers
    float           *as_float_ptr();
    double          *as_double_ptr();

    // signed integers via pointers (const variants)
    const char       *as_char_ptr()  const;
    const short      *as_short_ptr() const;
    const int        *as_int_ptr()   const;
    const long       *as_long_ptr()  const;

    // unsigned integers via pointers (const variants)
    const unsigned char   *as_unsigned_char_ptr()  const;
    const unsigned short  *as_unsigned_short_ptr() const;
    const unsigned int    *as_unsigned_int_ptr()   const;
    const unsigned long   *as_unsigned_long_ptr()  const;

    // floating point via pointers (const variants)
    const float           *as_float_ptr()  const;
    const double          *as_double_ptr() const;

    // signed integer array types via conduit::DataArray
    char_array       as_char_array();
    short_array      as_short_array();
    int_array        as_int_array();
    long_array       as_long_array();

    // unsigned integer array types via conduit::DataArray
    unsigned_char_array    as_unsigned_char_array();
    unsigned_short_array   as_unsigned_short_array();
    unsigned_int_array     as_unsigned_int_array();
    unsigned_long_array    as_unsigned_long_array();

    // floating point array types via conduit::DataArray
    float_array     as_float_array();
    double_array    as_double_array();

    // signed integer array types via conduit::DataArray (const variants)
    const char_array       as_char_array()  const;
    const short_array      as_short_array() const;
    const int_array        as_int_array()   const;
    const long_array       as_long_array()  const;

    // unsigned integer array types via conduit::DataArray (const variants)
    const unsigned_char_array    as_unsigned_char_array()  const;
    const unsigned_short_array   as_unsigned_short_array() const;
    const unsigned_int_array     as_unsigned_int_array()   const;
    const unsigned_long_array    as_unsigned_long_array()  const;

    // floating point array value via conduit::DataArray (const variants)
    const float_array     as_float_array()  const;
    const double_array    as_double_array() const;

//-----------------------------------------------------------------------------
///@}
//-----------------------------------------------------------------------------
//
// -- end declaration of Node value access methods --
//
//-----------------------------------------------------------------------------


private:
//-----------------------------------------------------------------------------
//
// -- begin declaration of  Private Construction Helpers --
//
//-----------------------------------------------------------------------------
///@name Private Construction Helpers
///@{
//-----------------------------------------------------------------------------
/// description:
/// these methods are used for construction by the Node & Generator classes.
//-----------------------------------------------------------------------------
    void             set_data_ptr(void *data_ptr);
    ///
    /// Note: set_schema_ptr is *only* used in the case were we have 
    /// a schema pointer that is owned by a parent schema. Using it to set a 
    /// pointer that should be owned by a node unleashes chaos.
    ///
    void             set_schema_ptr(Schema *schema_ptr);
    void             append_node_ptr(Node *node)
                        {m_children.push_back(node);}

    void             set_parent(Node *parent) 
                        { m_parent = parent;}


//-----------------------------------------------------------------------------
///@}
//-----------------------------------------------------------------------------
//
// -- end declaration of Private Construction Helpers --
//
//-----------------------------------------------------------------------------


//=============================================================================
//-----------------------------------------------------------------------------
//
// -- private methods and members -- 
//
//-----------------------------------------------------------------------------
//=============================================================================

//-----------------------------------------------------------------------------
// value access related to conditional long long and long double support
//-----------------------------------------------------------------------------
// We provide connivence methods for native c types, but we don't want to
// provide them in the public api for long long and long double. 
// Why? These types are ambiguous, if folks want a 64-bit integer, they should 
// explicitly use conduit::int64, conduit::uint64, etc
// The only place where long long and long double will appear in the public
// interface is in the Node::Value() class, where it is needed for casting magic
// to work for uint64, etc types.
//-----------------------------------------------------------------------------
    ///
    /// These methods allow you to access a leaf as known type
    /// (used in Node::Value())
    
     // signed integer scalars
    #ifdef CONDUIT_USE_LONG_LONG
    long long      as_long_long() const;
    #endif

    // unsigned integer scalars
    #ifdef CONDUIT_USE_LONG_LONG
    unsigned long long  as_unsigned_long_long() const;
    #endif

    // floating point scalars
    #ifdef CONDUIT_USE_LONG_DOUBLE
    long double      as_long_double() const;
    #endif

    // signed integers via pointers
    #ifdef CONDUIT_USE_LONG_LONG
    long long      *as_long_long_ptr() const;
    #endif

    // unsigned integers via pointers
    #ifdef CONDUIT_USE_LONG_LONG
    unsigned long long  *as_unsigned_long_long_ptr() const;
    #endif


    // floating point via pointers
    #ifdef CONDUIT_USE_LONG_DOUBLE
    long double     *as_long_double_ptr();
    #endif

    // signed integers via pointers (const variants)
    #ifdef CONDUIT_USE_LONG_LONG
    const long long  *as_long_long_ptr() const;
    #endif

    // unsigned integers via pointers (const variants)
    #ifdef CONDUIT_USE_LONG_LONG
    const unsigned long long  *as_unsigned_long_long_ptr() const;
    #endif


    // floating point via pointers (const variants)
    #ifdef CONDUIT_USE_LONG_DOUBLE
    const long double     *as_long_double_ptr() const;
    #endif


    // signed integer array types via conduit::DataArray
    #ifdef CONDUIT_USE_LONG_LONG
    long_long_array  as_long_long_array();
    #endif

    // unsigned integer array types via conduit::DataArray
    #ifdef CONDUIT_USE_LONG_LONG
    unsigned_long_long_array  as_unsigned_long_long_array();
    #endif
    

    // floating point array types via conduit::DataArray
    #ifdef CONDUIT_USE_LONG_DOUBLE
    long_double_array  as_long_double_array();
    #endif

    // signed integer array types via conduit::DataArray (const variants)
    #ifdef CONDUIT_USE_LONG_LONG
    const long_long_array  as_long_long_array() const;
    #endif

    // unsigned integer array types via conduit::DataArray (const variants)
    #ifdef CONDUIT_USE_LONG_LONG
    const unsigned_long_long_array  as_unsigned_long_long_array() const;
    #endif

    // floating point array value via conduit::DataArray (const variants)
    #ifdef CONDUIT_USE_LONG_DOUBLE
    const long_double_array  as_long_double_array() const;
    #endif

    ///
    /// These methods allow you to coerce a leaf type to another type.
    /// (used in Node::Value())
    
    /// scalar coercion
    /// convert to c signed integer types
    #ifdef CONDUIT_USE_LONG_LONG
    long long        to_long_long()  const;
    #endif

    /// convert to c unsigned integer types
    #ifdef CONDUIT_USE_LONG_LONG
    unsigned long long to_unsigned_long_long()  const;
    #endif

    
    /// convert to c floating point types
    #ifdef CONDUIT_USE_LONG_DOUBLE
    long double      to_long_double() const;
    #endif

//-----------------------------------------------------------------------------
//
// -- private methods that help with init, memory allocation, and cleanup --
//
//-----------------------------------------------------------------------------
    // setup a node to at as a given type
    void             init(const DataType &dtype);
    // memory allocation and mapping routines
    void             allocate(index_t dsize);
    void             allocate(const DataType &dtype);
    void             mmap(const std::string &stream_path,
                          index_t dsize);
    // release any alloced or memory mapped data
    void             release();
    // clean up everything (used by destructor)
    void             cleanup();

    // set defaults (used by constructors)
    void              init_defaults();
    // setup node to act as a list
    void              init_list();
    // setup node to act as an object
    void              init_object();

//-----------------------------------------------------------------------------
//
// -- private methods that help with hierarchical construction --
//
//-----------------------------------------------------------------------------
    // work horse for complex node hierarchical setup
    static void      walk_schema(Node   *node,
                                 Schema *schema,
                                 void   *data);

    static void      mirror_node(Node   *node,
                                 Schema *schema,
                                 Node   *src);

//-----------------------------------------------------------------------------
//
// -- private methods that help with compaction, serialization, and info  --
//
//-----------------------------------------------------------------------------
    void              compact_to(uint8 *data,
                                 index_t curr_offset) const;
    /// compact helper for leaf types
    void              compact_elements_to(uint8 *data) const;


    void              serialize(uint8 *data,
                                index_t curr_offset) const;

    void              info(Node &res,
                           const std::string &curr_path) const;

//-----------------------------------------------------------------------------
//
// -- private to_json helpers --
//
//-----------------------------------------------------------------------------
    //-------------------------------------------------------------------------
    // the generic to_json methods are used by the specialized cases 
    //-------------------------------------------------------------------------
    std::string         to_json_generic(bool detailed, 
                                        index_t indent=2, 
                                        index_t depth=0,
                                        const std::string &pad=" ",
                                        const std::string &eoe="\n") const;

    void                to_json_generic(const std::string &stream_path,
                                        bool detailed, 
                                        index_t indent=2, 
                                        index_t depth=0,
                                        const std::string &pad=" ",
                                        const std::string &eoe="\n") const;

    void                to_json_generic(std::ostream &os,
                                        bool detailed, 
                                        index_t indent=2, 
                                        index_t depth=0,
                                        const std::string &pad=" ",
                                        const std::string &eoe="\n") const;
   
    //-------------------------------------------------------------------------
    // transforms the node to json without any conduit schema constructs
    //-------------------------------------------------------------------------
    std::string      to_pure_json(index_t indent=2,
                                  index_t depth=0,
                                  const std::string &pad=" ",
                                  const std::string &eoe="\n") const;

    void             to_pure_json(const std::string &stream_path,
                                  index_t indent=2,
                                  index_t depth=0,
                                  const std::string &pad=" ",
                                  const std::string &eoe="\n") const;

    void             to_pure_json(std::ostream &os,
                                  index_t indent=2,
                                  index_t depth=0,
                                  const std::string &pad=" ",
                                  const std::string &eoe="\n") const;

    //-------------------------------------------------------------------------
    // transforms the node to json that contains conduit schema constructs
    //-------------------------------------------------------------------------
    std::string      to_detailed_json(index_t indent=2, 
                                      index_t depth=0,
                                      const std::string &pad=" ",
                                      const std::string &eoe="\n") const;

    void             to_detailed_json(const std::string &stream_path,
                                      index_t indent=2, 
                                      index_t depth=0,
                                      const std::string &pad=" ",
                                      const std::string &eoe="\n") const;

    void             to_detailed_json(std::ostream &os,
                                      index_t indent=2, 
                                      index_t depth=0,
                                      const std::string &pad=" ",
                                      const std::string &eoe="\n") const;
                                             
    //-------------------------------------------------------------------------
    // transforms the node to json with data payload encoded using base64
    //-------------------------------------------------------------------------
    std::string      to_base64_json(index_t indent=2,
                                    index_t depth=0,
                                    const std::string &pad=" ",
                                    const std::string &eoe="\n") const;

    void             to_base64_json(const std::string &stream_path,
                                    index_t indent=2,
                                    index_t depth=0,
                                    const std::string &pad=" ",
                                    const std::string &eoe="\n") const;

    void             to_base64_json(std::ostream &os,
                                    index_t indent=2,
                                    index_t depth=0,
                                    const std::string &pad=" ",
                                    const std::string &eoe="\n") const;


//-----------------------------------------------------------------------------
//
// -- conduit::Node private data members --
//
//-----------------------------------------------------------------------------
    /// pointer to this node's parent (if it exists)
    Node                *m_parent;
    /// pointer to this node's schema
    Schema              *m_schema;
    /// we need to know if *this* node created the schema
    bool                 m_owns_schema;
    
    /// collection of children
    std::vector<Node*>   m_children;

    // TODO: DataContainer?
    // pointer to the node's data
    void     *m_data;
    // size of the allocated or mmaped data point
    index_t   m_data_size;

    // flag that indicates this node allocated m_data
    bool      m_alloced;
    // flag that indicates if m_data is memory-mapped
    bool      m_mmaped;
    // memory-map file descriptor
    int       m_mmap_fd;
};

//-----------------------------------------------------------------------------
// -- end conduit::Node --
//-----------------------------------------------------------------------------

}
//-----------------------------------------------------------------------------
// -- end conduit:: --
//-----------------------------------------------------------------------------

#endif
