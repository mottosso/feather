// =====================================================================================
// 
//       Filename:  ui.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  12/09/2014 02:00:59 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#ifndef UI_HPP
#define UI_HPP

namespace feather
{

    namespace ui
    {

        enum Location {
            Menu,
            Popup,
            FieldEditor
        };

        template <int _Node>
            void layout(std::string& msg) { };

        template <int _Location, int _StartNode, int _EndNode>
            struct get_layout {
                static void exec(int n, std::string& msg) { return get_layout<_Location,_StartNode-1,_EndNode>::exec(n,msg); };
            };

    } // namespace ui

} // namespace feather

#endif
