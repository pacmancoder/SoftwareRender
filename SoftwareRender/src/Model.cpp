#include "Model.h"

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
Model::Model(const char* filename)
{
  //Открываем файл
  std::ifstream in;
  in.open(filename, std::ifstream::in);
  std::string line;
  while (!in.eof()) {
    std::getline(in, line); // читаем строку
    // создаём поток, читающий из конкретнйо строки
    std::istringstream lineStream(line.c_str());
    char dummy; // пустышка, для отсекания лишнего
    if (!line.compare(0, 2, "v ")) {
      lineStream >> dummy;
      vec3f v;
      for (int i = 0; i < 3; i++) 
        lineStream >> v[i];
      verts.push_back(v);
    } else if (!line.compare(0, 3, "vn ")) {
      lineStream >> dummy >> dummy;
      vec3f n;
      for (int i = 0; i < 3; i++) 
        lineStream >> n[i];
      normals.push_back(n);
    } else if (!line.compare(0, 3, "vt ")) {
      lineStream >> dummy >> dummy;
      vec2f uv;
      for (int i = 0; i < 2; i++) 
        lineStream >> uv[i];
      uvs.push_back(uv);
    } else if (!line.compare(0, 2, "f ")) {
      std::vector<VertexInfo> face;
      VertexInfo tmp;
      lineStream >> dummy;
      while (lineStream >> tmp.vi >> dummy >> tmp.uvi >> dummy >> tmp.ni) {
        // в *.obj индексы начинаются с 1
        tmp.vi--; tmp.uvi--; tmp.ni--;
        face.push_back(tmp);
      }
      faces.push_back(face);
    }
  }
}

Model::~Model()
{
}

std::vector<VertexInfo>& Model::face(int idx)
{
  return faces[idx];
}

vec3f Model::vert(int face, int n)
{
  return verts[faces[face][n].vi];
}

int Model::facesCount()
{
  return faces.size();
}

int Model::vertsCount()
{
  return verts.size();
}