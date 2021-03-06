/*
 * Copyright 2017 Justas Masiulis
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#if CARBON_GENERATE_MACROS || 0
#include <fstream>

int main()
{
    std::ofstream out("generated_macros.hpp");

    out << "#pragma once\n"
        << "/// AUTOGENERATED FILE PLEASE DO NOT MODIFY\n"
        << "\n\n";

    // generate [1, 32] serialization macros
    for (int i = 1; i < 33; ++i) {
        out << "#define CRBN_DETAIL_SERIALIZABLE_" << i << "(C";
        for (int j = 0; j < i; ++j)
            out << ",_" << j;
        out << ") ::carbon::serializer<";
        for (int j = 0; j < i; ++j) {
            out << "::carbon::m_<"
                << "decltype(&C::_" << j << ")"
                << ",&C::_" << j << '>';
            if (j != i - 1)
                out << ",";
        }
        out << ">;\n";
    }

    out << "\n\n";

    for (int i = 1; i < 33; ++i) {
        out << "#define CRBN_DETAIL_NAMED_SERIALIZABLE_" << i << "(C";
        for (int j = 0; j < i; ++j)
            out << ",_" << j;
        out << ") ::carbon::serializer<";
        for (int j = 0; j < i; ++j) {
            out << "::carbon::named_<CRBN_STR(#_" << j << ")"
                << ",decltype(&C::_" << j << ")"
                << ",&C::_" << j << '>';
            if (j != i - 1)
                out << ",";
        }
        out << ">;\n";
    }
}

#endif
