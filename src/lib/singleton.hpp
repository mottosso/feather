// =====================================================================================
// 
//       Filename:  singleton.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/15/2014 05:26:37 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
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
