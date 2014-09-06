// =====================================================================================
// 
//       Filename:  data.hpp
// 
//    Description:  This holds the actual data of a node.
// 
//        Version:  1.0
//        Created:  09/06/2014 07:06:53 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
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
