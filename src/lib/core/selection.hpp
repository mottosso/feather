// =====================================================================================
// 
//       Filename:  selection.hpp
// 
//    Description:  Holds the current selection state.
// 
//        Version:  1.0
//        Created:  09/06/2014 06:06:06 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#ifndef SELECTION_HPP
#define SELECTION_HPP
#include "singleton.hpp"

namespace feather
{

    /*
     * Here is how selection works in Feather.
     * The user will select items by the viewports opengl widget.
     * The Node and Component info are stored in a SelectionState and there
     * can be more then one SelectionState.
     * SelectionStates are managed by the SelectionManager that will add,
     * remove, and modify the SelectionStates.
     */


    // Selection Group
    struct SelectionGroup {
        int start_indic;
        int end_indic;
    };


    // Selection State
    class SelectionState {
        public:
            SelectionState(){};
            ~SelectionState() {};
            void clear() {};
            int count() { return m_SelectionGroups.size(); }; 
        private:
            int m_Node;
            int m_Component;
            std::vector<SelectionGroup> m_SelectionGroups;
    };


    // Selection Manager
    class SelectionManager {
        public:
            SelectionManager(){};
            ~SelectionManager(){};
            void clear() {};
            int count() { return m_SelectionStates.size(); };
        private:
            std::vector<SelectionState> m_SelectionStates;
    };

    // Singleton
    typedef Singleton<SelectionManager> SelectionManagerSingleton;

} // namespace feather

#endif
