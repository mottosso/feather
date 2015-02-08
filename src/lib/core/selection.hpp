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


    // Selection State
    struct SelectionState {
        SelectionState(int _uid, int _field=0) : uid(_uid), field(_field) { };
        int uid;
        int field;
    };


    // Selection Manager
    class SelectionManager {
        public:
            SelectionManager(){};
            ~SelectionManager(){};
            void clear() {};
            int count() { return m_aStates.size(); };
            void add_state(int _uid, int _field) { m_aStates.push_back(SelectionState(_uid,_field)); };
            SelectionState& get_state(int _i) { return m_aStates.at(_i); };
        private:
            std::vector<SelectionState> m_aStates;
    };

    // Singleton
    typedef Singleton<SelectionManager> SelectionManagerSingleton;

} // namespace feather

#endif
