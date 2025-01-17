#pragma once

#include <Core/Block.h>
#include <Core/NamesAndTypes.h>


namespace DB
{

namespace Nested
{
    std::string concatenateName(const std::string & nested_table_name, const std::string & nested_field_name);

    std::pair<std::string, std::string> splitName(const std::string & name);
    std::pair<std::string_view, std::string_view> splitName(const std::string_view & name);

    /// Returns the prefix of the name to the first '.'. Or the name is unchanged if there is no dot.
    std::string extractTableName(const std::string & nested_name);

    /// Replace Array(Tuple(...)) columns to a multiple of Array columns in a form of `column_name.element_name`.
    /// only for named tuples that actually represent Nested structures.
    Block flatten(const Block & block);

    /// Collect Array columns in a form of `column_name.element_name` to single Array(Tuple(...)) column.
    NamesAndTypesList collect(const NamesAndTypesList & names_and_types);

    /// Convert old-style nested (single arrays with same prefix, `n.a`, `n.b`...) to subcolumns of data type Nested.
    NamesAndTypesList convertToSubcolumns(const NamesAndTypesList & names_and_types);

    /// Check that sizes of arrays - elements of nested data structures - are equal.
    void validateArraySizes(const Block & block);

    /// Get all nested tables names from a block.
    std::unordered_set<String> getAllTableNames(const Block & block);
}

}
