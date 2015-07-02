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
    typedef float FFloat;
    typedef double FDouble;
    typedef std::string FString;
    typedef struct{double x; double y;} FPoint2D;
    typedef struct{double x; double y; double z;} FPoint3D;

    struct FVertex3D
    {
        FVertex3D(FFloat _x=0, FFloat _y=0, FFloat _z=0) { x=_x; y=_y; z=_z; };
        FFloat x;
        FFloat y;
        FFloat z;
    };

    typedef struct{double x; double y; double z;} FNormal3D;
    typedef struct{ double x; double y; double z; double w;} FVector3D;

    struct FColorRGB
    {
        FColorRGB(float _r=1.0, float _g=1.0, float _b=1.0, float _a=1.0):r(_r),g(_g),b(_b){};
        float r;
        float g;
        float b;
        float a;
    };

    struct FColorRGBA
    {
        FColorRGBA(float _r=1.0, float _g=1.0, float _b=1.0, float _a=1.0):r(_r),g(_g),b(_b),a(_a){};
        float r;
        float g;
        float b;
        float a;
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
        FFacePoint(uint _v=0, uint _vt=0, uint _vn=0): v(_v), vt(_vt), vn(_vn) {};
        uint v;
        uint vt;
        uint vn;
    };

    //typedef struct{std::vector<FFacePoint> f; } FFace;
    typedef std::vector<FFacePoint> FFace;
    typedef double FMatrix[4][4];

    // Arrays
    typedef std::vector<FBool> FBoolArray;
    typedef std::vector<FInt> FIntArray;
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
        FIntArray i;
        FColorRGBAArray c;

        inline void add_face(const FFace face) { f.push_back(face); };
        inline void build_gl() {
            i.clear();
            c.clear();
            uint id=0;
            int fcount=0; // this is a temp value to test selection
            std::for_each(f.begin(), f.end(), [this,&id,&fcount](FFace _face){
                while(id+1 < _face.size()) {
                    if(fcount==3) {
                        c.push_back(FColorRGBA(1.0,0.0,0.0,1.0));
                        c.push_back(FColorRGBA(1.0,0.0,0.0,1.0));
                        c.push_back(FColorRGBA(1.0,0.0,0.0,1.0));
                    } else {
                        c.push_back(FColorRGBA());
                        c.push_back(FColorRGBA());
                        c.push_back(FColorRGBA());
                    }
                    i.push_back(_face.at(id++).v);
                    i.push_back(_face.at(id++).v);
                    if(id+1 < _face.size()) {
                        i.push_back(_face.at(id).v);
                    } else {
                       i.push_back(_face.at(0).v);
                    }
                }
                fcount++;
                id=0;
            });
        };
        // remove all the vertex, normals, tex coords and faces from the mesh
        inline void clear() { v.clear(); st.clear(); vn.clear(); i.clear(); };
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
