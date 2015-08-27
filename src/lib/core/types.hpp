/***********************************************************************
 *
 * Filename: types.hpp
 *
 * Description: Holds all the feather types.
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

#ifndef TYPES_HPP
#define TYPES_HPP

#include "deps.hpp"
#include "field.hpp"
#include "node.hpp"
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLShader>

namespace feather
{
    typedef bool FBool;
    typedef int FInt;
    typedef unsigned int FUInt;
    typedef float FFloat;
    typedef double FDouble;
    typedef std::string FString;
    typedef struct{double x; double y;} FPoint2D;
    typedef struct{double x; double y; double z;} FPoint3D;

    struct FVertex3D
    {
        FVertex3D(FFloat _x=0, FFloat _y=0, FFloat _z=0) { x=_x; y=_y; z=_z; };
        FDouble x;
        FDouble y;
        FDouble z;
    };

    typedef struct{double x; double y; double z;} FNormal3D;
    typedef struct{ double x; double y; double z; double w;} FVector3D;

    struct FColorRGB
    {
        FColorRGB(FFloat _r=1.0, FFloat _g=1.0, FFloat _b=1.0, FFloat _a=1.0):r(_r),g(_g),b(_b){};
        inline FInt int_red() { return 255 * r; };
        inline FInt int_green() { return 255 * g; };
        inline FInt int_blue() { return 255 * b; };
        inline void set_red(FInt _r) { r = _r / 255.0; };
        inline void set_green(FInt _g) { r = _g / 255.0; };
        inline void set_blue(FInt _b) { r = _b / 255.0; };
        FFloat r;
        FFloat g;
        FFloat b;
        FFloat a;
    };

    struct FColorRGBA
    {
        FColorRGBA(FFloat _r=1.0, FFloat _g=1.0, FFloat _b=1.0, FFloat _a=1.0):r(_r),g(_g),b(_b),a(_a){};
        FFloat r;
        FFloat g;
        FFloat b;
        FFloat a;
    };

    struct FTransform
    {
        FVertex3D translate;
        FVector3D rotate;
        FVector3D scale;
    };

    struct FTextureCoord
    {
        FTextureCoord(FDouble _s=0, FDouble _t=0) { s=_s; t=_t; };
        FDouble s;
        FDouble t;
    };

    struct FFacePoint
    {
        FFacePoint(FUInt _v=0, FUInt _vt=0, FUInt _vn=0): v(_v), vt(_vt), vn(_vn) {};
        FUInt v;
        FUInt vt;
        FUInt vn;
    };

    //typedef struct{std::vector<FFacePoint> f; } FFace;
    typedef std::vector<FFacePoint> FFace;
    typedef double FMatrix[4][4];

    // Arrays
    typedef std::vector<FBool> FBoolArray;
    typedef std::vector<FInt> FIntArray;
    typedef std::vector<FUInt> FUIntArray;
    typedef std::vector<FDouble> FDoubleArray;
    typedef std::vector<FString> FStringArray;
    typedef std::vector<FVertex3D> FVertex3DArray;
    typedef std::vector<FVertex3D> FVertex3DArray;
    typedef std::vector<FColorRGB> FColorRGBArray;
    typedef std::vector<FColorRGBA> FColorRGBAArray;
    typedef std::vector<FTextureCoord> FTextureCoordArray;
    typedef std::vector<FNormal3D> FNormal3DArray;
    typedef std::vector<FFace> FFaceArray;

    struct FStatus
    {
        FBool pass;
        FString message;        
    };

    
    // Layer Properties
    struct FLayer
    {
        FLayer(std::string _n="", FColorRGB _c=FColorRGB(), bool _v=true, bool _l=true, std::vector<uint> _u=std::vector<uint>()): name(_n),color(_c),visible(_v),locked(_l),uids(_u) {};
        std::string name;
        FColorRGB color;
        bool visible;
        bool locked;
        std::vector<uint> uids;            
    };



    // Mesh Components

    typedef struct {
        FInt s;
        FFaceArray f;
    } FSmoothingGroup;

    typedef struct {
        FString g;
        FString usemtl;
        std::vector<FSmoothingGroup> sg;
    } FFaceGroup;

    struct FMesh
    {
        FVertex3DArray v;
        FTextureCoordArray st;
        FVertex3DArray vn;
        FFaceArray f;
        // gl
        FVertex3DArray glv;
        FVertex3DArray glvn;
        FIntArray gli; // for tris
        FColorRGBAArray glc;
        // gl face edges
        FIntArray glec; // edge count
        FIntArray glei; // edge indics
 
        inline void add_face(const FFace face) { f.push_back(face); };

        inline void assign_v(const FVertex3DArray& _v) { v.assign(_v.begin(),_v.end()); };
        inline void assign_st(const FTextureCoordArray& _st) { st.assign(_st.begin(),_st.end()); };
        inline void assign_vn(const FVertex3DArray& _vn) { vn.assign(_vn.begin(),_vn.end()); };
        inline void assign_f(const FFaceArray& _f) { f.assign(_f.begin(),_f.end()); };

        inline void build_gl() {
            glv.clear();
            glvn.clear();
            gli.clear();
            glc.clear();
            uint id=0;
            int fcount=0; // this is a temp value to test selection
            std::for_each(f.begin(), f.end(), [this,&id,&fcount](FFace _face){

                for_each(_face.begin(),_face.end(),[this](FFacePoint _fp){ glei.push_back(_fp.v); });

                while(id+2 <= _face.size()) {
                    if(fcount==3) {
                        glc.push_back(FColorRGBA(1.0,0.0,0.0,1.0));
                        glc.push_back(FColorRGBA(1.0,0.0,0.0,1.0));
                        glc.push_back(FColorRGBA(1.0,0.0,0.0,1.0));
                    } else {
                        glc.push_back(FColorRGBA());
                        glc.push_back(FColorRGBA());
                        glc.push_back(FColorRGBA());
                    }

                    std::cout << "v" << id << ":" << _face.at(id).v << ",";
                    //glv.push_back(v.at(_face.at(id).v));
                    //glvn.push_back(vn.at(_face.at(id).vn));
                    gli.push_back(_face.at(id).v);
 
                    std::cout << "v" << id+1 << ":" << _face.at(id+1).v << ",";
                    //glv.push_back(v.at(_face.at(id+1).v));
                    //glvn.push_back(vn.at(_face.at(id+1).vn));
                    gli.push_back(_face.at(id+1).v);

                    if(id+2 < _face.size()) {
                        std::cout << "v" << id+2 << ":" << _face.at(id+2).v << ",";
                        //glv.push_back(v.at(_face.at(id+2).v));
                        //glvn.push_back(vn.at(_face.at(id+2).vn));
                        gli.push_back(_face.at(id+2).v);
                    } else {
                        std::cout << "v" << 0 << ":" << _face.at(0).v << ",";
                        //glv.push_back(v.at(_face.at(0).v));
                        //glvn.push_back(vn.at(_face.at(0).vn));
                        gli.push_back(_face.at(0).v);
                    }

                    id=id+2;
                }
                std::cout << "\n";
                fcount++;
                id=0;
            });
        };
        // remove all the vertex, normals, tex coords and faces from the mesh
        inline void clear() { v.clear(); st.clear(); vn.clear(); glv.clear(); glvn.clear(); gli.clear(); };
        // cut the face along two edges
        inline bool split_face(const uint face, const uint v1, const uint v2) {
            // verify the face and edges
            if(face >= f.size()) {
                if(v1 >= f.at(face).size() || v2 >= f.at(face).size() || v1==v2 || v1==v2+1 || v1==v2-1)
                    return false;
            }
            
            // get the id of the fp of the face
            FFace f1;
            FFace f2;
            bool sf=false; // true if on face two
            std::for_each(f.at(face).begin(), f.at(face).end(), [&v1,&v2,&f1,&f2,&sf](FFacePoint fp){
                (!sf) ? f1.push_back(fp) : f2.push_back(fp);
                if(fp.v==v1 || fp.v==v2) {
                    if(!sf) {
                        f2.push_back(fp);        
                        sf=true;
                    } else {
                        f1.push_back(fp);
                        sf=false;
                    } 
                }
            } );
            
            // replace the old face and add the new one right after it.
            std::vector<FFace> sface;
            sface.push_back(f1);
            sface.push_back(f2);
            auto it = f.begin();
            // set the iterator to the point where the faces need to be inserted
            it=it+face; // set the iterator to the face that needs to be replaced
            // remove the old face
            f.erase(it);
            // add the two new faces in it's place
            f.insert(it,sface.begin(),sface.end());

            return true;
        };
    };

    // SceneGraph Types

    struct FNode;

    struct FConnection;

    typedef struct {} DataObject;

    typedef struct {} FAttributeArray;

    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, FNode, FConnection> FSceneGraph;

    typedef FSceneGraph::vertex_descriptor FNodeDescriptor;

    typedef std::pair<FSceneGraph::edge_descriptor, bool> FFieldConnection;

    struct PluginNodeFields;
 
    struct FNode
    {
        FNode(node::Type t=node::Null) : type(t),parent(NULL) {};
        int uid; // unique id number
        int node; // node type enum
        field::Fields fields; // this holds the field data
        std::string name;
        node::Type type; // this is the node group type
        DataObject* parent; // ??still used??
        FAttributeArray* attrs; // ??still used??
        // GL
        int glVertex;
        int glColor;
        int glMatrix;
        int glNormal;
        int glView; // 0=face, 1=edge, 2=point
        int glLightPosition;
        int glShaderDiffuse;
    };

    typedef std::vector<FNode*> FNodeArray;

    struct FConnection
    {
        FConnection() {};
        field::Type t1; // source type
        FNodeDescriptor n1; // source node 
        int f1; // source field
        field::Type t2; // target type
        FNodeDescriptor n2; // target node 
        int f2; // target field
        field::FieldBase* sfield; // source field
        field::FieldBase* tfield; // target field
        //field::Connection::Type conn_type;
        //FField* pfield; // parent field
        //FNode* pnode; // parent node
        //int field;
    };

    struct FGlInfo
    {
        int uid;
        std::vector<FVector3D>* mesh;
        FTransform position;
        QMatrix4x4* view;
        QOpenGLShader* vertShader;
        QOpenGLShader* fragShader;
        QOpenGLShaderProgram* program;
    };

} // namespace feather

#endif
