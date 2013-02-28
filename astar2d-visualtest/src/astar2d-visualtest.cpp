#include "../include/StdAfx.h"
#include "../include/configure.h"
#include <astar2d.h>
#include "../include/io/TextVisual.h"



/**
* Тестирование для проекта 'typelib'.
*/
int main( int argc, char** argv ) {

    using namespace astar;

    setlocale( LC_ALL, "Russian" );
    // Для разделителя '.' вместо ','
    setlocale( LC_NUMERIC, "C" );



    static const size_t N = 10;
    static const size_t M = 5;
    typedef AStar2D< N, M >  Search;
    
    Search::penalty_t  penalty;
    std::srand( 12345 );
    for (size_t q = 0; q < N * M / 3; ++q) {
        const auto x = std::rand() % N;
        const auto y = std::rand() % M;
        penalty.content[ x ][ y ] =
            std::numeric_limits< unsigned char >::max();
            //0;
    }

    Search::risk_t  risk;
    Search  search( penalty, risk );
    const Search::coord_t from = { 0,      0     };
    const Search::coord_t to   = { N - 1,  M - 1 };
    search.path( from, to );


    // показываем картинку
    TextVisual visi;
    visi << search;


    std::cout << std::endl << "^" << std::endl;
    visi.wait();

    return 0;

} // main()
