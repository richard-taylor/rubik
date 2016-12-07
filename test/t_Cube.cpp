
#include <cassert>
#include <map>
#include <set>
#include "Cube.h"
#include "CubeConstants.h"

enum Orient { XYZ, XZY, YXZ, YZX, ZXY, ZYX };

void sexy_test(Cube::Twist a, Cube::Twist b)
{
    // six sexy moves in a pair of faces returns us to solved
    Cube sexy;
    
    for (int i = 0; i < 6; i++)
    {
        sexy.twist(a);
        sexy.twist(b);
        sexy.twist(a.inverse());
        sexy.twist(b.inverse());
        
        assert(i == 5 ? sexy.solved() : !sexy.solved());
    }
}

int main()
{
    // construct a Cube
    Cube cube;

    // should be less than 15 bytes
    // since we create lots, they need to be as small as practically possible.
    assert(sizeof(cube) < 15);
    
    // should be solved initially
    assert(cube.solved());
    
    // twist about each face
    cube.twist(L);
    cube.twist(R);
    cube.twist(U);
    cube.twist(D);
    cube.twist(F);
    cube.twist(B);
    
    // should be not solved now
    assert(!cube.solved());
    
    // two more cubes
    Cube a_cube;
    Cube b_cube;
    assert(cube != a_cube);
    assert(cube != b_cube);
    
    // should be equal at first
    assert(a_cube == b_cube);
    
    // then different if we make different moves
    a_cube.twist(L);
    b_cube.twist(R);
    assert(a_cube != b_cube);
    
    // if cubes are different then one is less than the other
    assert(((a_cube < b_cube) && !(b_cube < a_cube)) ||
           ((b_cube < a_cube) && !(a_cube < b_cube)));
            
    // copy constructor should be by value not reference
    Cube c_cube = b_cube;
    assert(b_cube == c_cube);
    c_cube.twist(U);
    assert(b_cube != c_cube);
    
    // should be able to make a set of cubes
    std::set<Cube> cube_set;
    cube_set.insert(a_cube);
    cube_set.insert(b_cube);
    cube_set.insert(c_cube);
    assert(cube_set.size() == 3);
    assert(cube_set.find(a_cube) != cube_set.end());
    assert(cube_set.find(b_cube) != cube_set.end());
    assert(cube_set.find(c_cube) != cube_set.end());
    
    // should be able to use a cube as a key in a map
    std::map<Cube, int> count_map;
    count_map[a_cube] = 1;
    count_map[b_cube] = 2;
    count_map[c_cube] = 3;
    assert(count_map[a_cube] == 1);
    assert(count_map[b_cube] == 2);
    assert(count_map[c_cube] == 3);
    
    // check that each twist and its inverse are consistent
    Cube twisty;
        
    twisty.twist(L);  assert(!twisty.solved());
    twisty.twist(Li); assert(twisty.solved());       
    twisty.twist(L2); assert(!twisty.solved());
    twisty.twist(L2); assert(twisty.solved());

    twisty.twist(R);  assert(!twisty.solved());
    twisty.twist(Ri); assert(twisty.solved());       
    twisty.twist(R2); assert(!twisty.solved());
    twisty.twist(R2); assert(twisty.solved());
    
    twisty.twist(U);  assert(!twisty.solved());
    twisty.twist(Ui); assert(twisty.solved());       
    twisty.twist(U2); assert(!twisty.solved());
    twisty.twist(U2); assert(twisty.solved());
    
    twisty.twist(D);  assert(!twisty.solved());
    twisty.twist(Di); assert(twisty.solved());       
    twisty.twist(D2); assert(!twisty.solved());
    twisty.twist(D2); assert(twisty.solved());
    
    twisty.twist(F);  assert(!twisty.solved());
    twisty.twist(Fi); assert(twisty.solved());       
    twisty.twist(F2); assert(!twisty.solved());
    twisty.twist(F2); assert(twisty.solved());
    
    twisty.twist(B);  assert(!twisty.solved());
    twisty.twist(Bi); assert(twisty.solved());       
    twisty.twist(B2); assert(!twisty.solved());
    twisty.twist(B2); assert(twisty.solved());
    
    // check that 6 sexy moves brings us back to solved
    sexy_test(R, U);
    sexy_test(F, U);
    sexy_test(L, U);
    sexy_test(B, U);
    sexy_test(R, D);
    sexy_test(F, D);
    sexy_test(L, D);
    sexy_test(B, D);
    
    // check that we can extract the individual piece positions
    unsigned char corners[8];
    unsigned char edges[12];
    
    Cube extract;
    extract.get_pieces(corners, edges);
    
    // solved pieces
    assert(corners[Cube::RUF] == Cube::RUF << 4);
    assert(corners[Cube::LUF] == Cube::LUF << 4);
    assert(corners[Cube::LUB] == Cube::LUB << 4);
    assert(corners[Cube::RUB] == Cube::RUB << 4);
    assert(corners[Cube::RDF] == Cube::RDF << 4);
    assert(corners[Cube::LDF] == Cube::LDF << 4);
    assert(corners[Cube::LDB] == Cube::LDB << 4);
    assert(corners[Cube::RDB] == Cube::RDB << 4);
    
    assert(edges[Cube::RU] == Cube::RU << 4);
    assert(edges[Cube::UF] == Cube::UF << 4);
    assert(edges[Cube::LU] == Cube::LU << 4);
    assert(edges[Cube::UB] == Cube::UB << 4);
    assert(edges[Cube::RF] == Cube::RF << 4);
    assert(edges[Cube::LF] == Cube::LF << 4);
    assert(edges[Cube::LB] == Cube::LB << 4);
    assert(edges[Cube::RB] == Cube::RB << 4);
    assert(edges[Cube::RD] == Cube::RD << 4);
    assert(edges[Cube::DF] == Cube::DF << 4);
    assert(edges[Cube::LD] == Cube::LD << 4);
    assert(edges[Cube::DB] == Cube::DB << 4);
    
    // extract after a turn
    extract.twist(R);
    extract.get_pieces(corners, edges);
    
    assert(corners[Cube::RUF] == Cube::RUB << 4 | XZY);
    assert(corners[Cube::LUF] == Cube::LUF << 4);
    assert(corners[Cube::LUB] == Cube::LUB << 4);
    assert(corners[Cube::RUB] == Cube::RDB << 4 | XZY);
    assert(corners[Cube::RDF] == Cube::RUF << 4 | XZY);
    assert(corners[Cube::LDF] == Cube::LDF << 4);
    assert(corners[Cube::LDB] == Cube::LDB << 4);
    assert(corners[Cube::RDB] == Cube::RDF << 4 | XZY);
    
    assert(edges[Cube::RU] == Cube::RB << 4);
    assert(edges[Cube::UF] == Cube::UF << 4);
    assert(edges[Cube::LU] == Cube::LU << 4);
    assert(edges[Cube::UB] == Cube::UB << 4);
    assert(edges[Cube::RF] == Cube::RU << 4);
    assert(edges[Cube::LF] == Cube::LF << 4);
    assert(edges[Cube::LB] == Cube::LB << 4);
    assert(edges[Cube::RB] == Cube::RD << 4);
    assert(edges[Cube::RD] == Cube::RF << 4);
    assert(edges[Cube::DF] == Cube::DF << 4);
    assert(edges[Cube::LD] == Cube::LD << 4);
    assert(edges[Cube::DB] == Cube::DB << 4);
}
