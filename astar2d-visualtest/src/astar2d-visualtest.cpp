#include "../include/StdAfx.h"
#include "../include/configure.h"
#include <astar2d.h>



/**
* Тестирование для проекта 'typelib'.
*/
int main( int argc, char** argv ) {

    using namespace astar;

    setlocale( LC_ALL, "Russian" );
    // Для разделителя '.' вместо ','
    setlocale( LC_NUMERIC, "C" );



    static const size_t N = 50;
    static const size_t M = 30;
    typedef AStar2D< N, M >  Search;
    
    Search::risk_t     risk;
    std::srand( 12345 );
    for (size_t q = 0; q < N * M / 3; ++q) {
        const auto x = std::rand() % (N - 1);
        const auto y = std::rand() % (M - 1);
        risk.content[ x ][ y ] = std::rand() % 255;
    }

    Search::penalty_t  penalty;
    Search             search( risk, penalty );
    const Search::coord_t from = { 0,      0     };
    const Search::coord_t to   = { N - 1,  M - 1 };
    const auto result = search.path( from, to );


    // @todo Показывать картинку.



    std::cout << std::endl << "^" << std::endl;
    std::cin.ignore();

    return 0;

} // main()
