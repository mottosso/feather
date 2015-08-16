/***********************************************************************
 *
 * Filename: layer.hpp
 *
 * Description: layers allow to manage nodes into grounds.
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

#ifndef LAYER_HPP
#define LAYER_HPP

#include "deps.hpp"

namespace feather
{

    class Layers
    {
        public:
            Layers(){};
            ~Layers(){ clear(); };

            inline void add(FLayer l) { m_apLayers.push_back(l); };
            inline bool remove(int id) { return false; }; // TODO
            inline void move(int sid, int tid) {
                /*
                std::vector<FLayer> layers;
                FLayer l = m_apLayers.at(sid);
                for(int i=0; i < m_apLayers.size(); i++){
                    if(tid==i)
                        layers.push_back(l);
                    else if(sid==i){}
                    else
                        layers.push_back(m_apLayers.at(i));
                }
                m_apLayers.clear();
                m_apLayers = layers;
                //m_apLayers.at(sid);
                */
                if(sid < tid){
                    m_apLayers.insert(m_apLayers.begin()+(tid+1),std::move(m_apLayers.at(sid)));
                    m_apLayers.erase(m_apLayers.begin()+sid);
                } else {
                    m_apLayers.insert(m_apLayers.begin()+(sid+1),std::move(m_apLayers.at(tid)));
                    m_apLayers.erase(m_apLayers.begin()+tid);
                }
            };
            inline int count() { return m_apLayers.size(); };
            inline void clear() { m_apLayers.clear(); };
            inline bool layer(int id, FLayer& l) { if(count() > id){ l=m_apLayers.at(id); return true; } return false; };
            inline void print() { std::for_each(m_apLayers.begin(),m_apLayers.end(),[](FLayer l){ std::cout << "name: " << l.name << std::endl; }); };

        private:   
            std::vector<FLayer> m_apLayers;
    };

    static Layers layers;

} // namespace feather

#endif
