/***********************************************************************
 *
 * Filename: singleton.hpp
 *
 * Description: Used for a single instance of an object.
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

#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include "deps.hpp"

namespace feather 
{

        template <class T>
            class Singleton
            {
                public:
                    static T* Instance() {
                        if(!m_pInstance) m_pInstance = new T;
                        assert(m_pInstance !=NULL);
                        return m_pInstance;
                    }

                protected:
                    Singleton();
                    ~Singleton();

                private:
                    Singleton(Singleton const&);
                    Singleton& operator=(Singleton const&);
                    static T* m_pInstance;
            };

        template <class T> T* Singleton<T>::m_pInstance=NULL;

}; // namespace feather 

#endif
