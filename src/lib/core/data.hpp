/***********************************************************************
 *
 * Filename: data.hpp
 *
 * Description: Used to hold node values.
 *
 * Copyright (C) 2015 Richard Layman, rlayman2000@yahoo.com 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ***********************************************************************/

#ifndef DATA_HPP
#define DATA_HPP

namespace feather
{

    /*
     * Each node has a DataBlock that it stores it's data inside.
     * This data is mapped to it's matching node by it's id number
     * whiched is mapped to the node's number.
     * This makes it possible for node functions to work with the
     * data.
     */

    struct DataBlock {
        int id;
        FTransform transform;
        FVertex3DArray v;
        FNormal3DArray vn;
        FTextureCoordArray st;
        FFaceArray faces;
    };

    class DataManager {
        public:
            DataManager() {};
            ~DataManager() {};
            void clear() {};
            int count() { return m_aBlocks.size(); };
        private:
            std::vector<DataBlock> m_aBlocks;
    };

} // namespace feather

#endif
