/***********************************************************************
 *
 * Filename: selection.hpp
 *
 * Description: Manages selection of nodes in the scenegraph.
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

#ifndef SELECTION_HPP
#define SELECTION_HPP
#include "singleton.hpp"

namespace feather
{

    namespace selection {

        enum Type { Node, Field, Component };

        // Selection State
        struct SelectionState {
            SelectionState(Type _type, int _uid, int _nid, int _fid=0) : type(_type), uid(_uid), nid(_nid), fid(_fid) { };

            Type type;
            int uid;
            int nid;
            int fid;
        };

        // Selection Manager
        class SelectionManager {
            public:
                SelectionManager(){};
                ~SelectionManager(){};
                void clear() { m_aStates.clear(); };
                uint count() { return m_aStates.size(); };
                void add_state(Type _type, int _uid, int _nid, int _fid=0) {
                    // don't add the state if the uid is already selected
                    bool found=false;
                    std::for_each(m_aStates.begin(), m_aStates.end(), [_uid,&found](SelectionState s){if(s.uid==_uid){found=true;}});
                    if(!found)
                        m_aStates.push_back(SelectionState(_type,_uid,_nid,_fid));
                };
                SelectionState& get_state(int _i) { return m_aStates.at(_i); };
                int get_uid(int _i) { return m_aStates.at(_i).uid; };
                bool selected(int _uid) {
                    for(SelectionState i: m_aStates){
                        if(i.uid==_uid)
                            return true;
                    }
                    return false;
                };
            private:
                std::vector<SelectionState> m_aStates;
        };

    } // namespace selection


    //static selection::SelectionManager smg;
    // Singleton
    typedef Singleton<selection::SelectionManager> smg;

} // namespace feather

#endif
