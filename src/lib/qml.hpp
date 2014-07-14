// =====================================================================================
// 
//       Filename:  qml.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/14/2014 05:41:06 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#ifndef QML_HPP
#define QML_HPP

#include "deps.hpp"
#include "types.hpp"
#include "status.hpp"

namespace feather
{

    namespace qml
    {

        class QmlSceneGraph : public QObject
        {
            Q_OBJECT

            public:
                QmlSceneGraph(QObject* parent=0);
                ~QmlSceneGraph();

                // commands
                Q_INVOKABLE void make_cube();
        };

    } // namespace qml

} // namespace feather

#endif
