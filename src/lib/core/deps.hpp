// =====================================================================================
// 
//       Filename:  deps.hpp
// 
//    Description:  contains all the dependencies for feather
// 
//        Version:  1.0
//        Created:  06/11/2014 05:03:07 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#ifndef DEPS_HPP
#define DEPS_HPP

// C
#include <dlfcn.h>
#include <stdio.h>
#include <math.h>

// C++
#include <cstddef>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <assert.h>
#include <algorithm>
#include <memory>
#include <utility>

// OpenGL
#include <GL/gl.h>
#include <GL/glext.h>
//#include <GL/glut.h>
#include <GL/freeglut.h>
//#include <GLFW/glfw3.h>

// boost
#include <boost/assert.hpp>
#include <boost/foreach.hpp>
#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/config/warning_disable.hpp>
#include <boost/config.hpp>
#include <boost/system/error_code.hpp>
#include <boost/filesystem.hpp>

// boost::fusion
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/fusion/sequence.hpp>
#include <boost/fusion/include/sequence.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/container/vector/vector_fwd.hpp>
#include <boost/fusion/include/vector_fwd.hpp>
#include <boost/fusion/algorithm/transformation/push_front.hpp>
#include <boost/fusion/include/push_front.hpp>
#include <boost/fusion/algorithm/transformation/push_back.hpp>
#include <boost/fusion/include/push_back.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/container/generation/make_vector.hpp>
#include <boost/fusion/include/make_vector.hpp>

// boost::bgl
#include <boost/graph/dag_shortest_paths.hpp>
#include <boost/graph/adjacency_list.hpp>
#include "boost/graph/visitors.hpp"
#include "boost/graph/breadth_first_search.hpp"
#include "boost/graph/depth_first_search.hpp"

// boost::tuple
#include <boost/tuple/tuple.hpp>

// boost::spirit
#include <boost/spirit/include/lex.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix.hpp>

// boost::variant
#include <boost/variant/recursive_variant.hpp>

#endif
