namespace astar {


template< size_t N, size_t M >
const typename AStar2D< N, M >::coord_t
AStar2D< N, M >::SHIFT[ DIRECTION ] = {
    {  0,  0 },
    {  0,  1 },
    {  1,  0 },
    {  0, -1 },
    { -1,  0 },
    {  1,  1 },
    {  1, -1 },
    { -1, -1 },
    { -1,  1 }
};



template< size_t N, size_t M >
inline AStar2D< N, M >::AStar2D(
    const penalty_t& penalty,
    const risk_t& risk
) :
    risk( risk ),
    penalty( penalty )
{
    static const coord_t ZERO = { 0, 0 };
    mPathPoint = std::make_pair( ZERO, ZERO );
}




template< size_t N, size_t M >
inline AStar2D< N, M >::~AStar2D() {
}




template< size_t N, size_t M >
inline void AStar2D< N, M >::path( const coord_t& from, const coord_t& to ) {

    // запоминаем начальную и конечную точки маршрута
    mPathPoint = std::make_pair( from, to );

    std::priority_queue< Node >  pq[ 2 ];
    size_t index = 0;

    // инициализируем вспомогательные карты
    for (size_t y = 0; y < M; ++y) {
        for (size_t x = 0; x < N; ++x) {
            const size_t i = x + N * y;
            mDirection[ i ] = 0;
            open[ i ] = 0;
            close[ i ] = false;
        }
    }

    Node  nFirst( from, 0, 0 );
    nFirst.update( to );
    pq[ index ].push( nFirst );
    open[ from.x + N * from.y ] = nFirst.priority;


    while ( !pq[ index ].empty() ) {

        // текущий узел с максимальным приоритетом из списка 'open'
        const auto& top = pq[ index ].top();
        Node  na( top.coord,  top.level,  top.priority );

        const coord_t& coord = na.coord;

        // @test
        std::cout << coord.x << " " << coord.y << std::endl;
        
        pq[ index ].pop();
        open[ coord.x + N * coord.y ] = 0;
        close[ coord.x + N * coord.y ] = true;

        if (coord == to) {
            // собираем найденный путь
            mPathDirection.clear();
            mPathCoord.clear();
            coord_t c = coord;
            while (c != from) {
                const auto k = mDirection[ c.x + N * c.y ];
                mPathDirection.push_back( k );
                // # mPathCoord соберём при вызове pathCoord().
                c -= SHIFT[ k ];
            }
            break;
        }


        // перемещаемся во всех допустимых направлениях
        for (size_t k = 1; k < DIRECTION; ++k) {
            const coord_t shift = coord + SHIFT[ k ];

            // границы поля
            if ( ( (shift.x < 0) || (shift.x > (N - 1))
                || (shift.y < 0) || (shift.y > (M - 1))
            ) ) {
                continue;
            }

            // проходимость клетки
            if (penalty.content[ shift.x ][ shift.y ] ==
                  std::numeric_limits< unsigned char >::max())
            {
                continue;
            }

            // пройденные клетки
            if ( close[ shift.x + N * shift.y ] ) {
                continue;
            }

            Node  nb( shift, na.level, na.priority );
            nb.next( k );
            nb.update( to );

            const size_t si = shift.x + N * shift.y;

            // добавляем узел к списку 'open', если он ещё не там
            if (open[ si ] == 0) {
                open[ si ] = nb.priority;
                // отмечаем направление
                mDirection[ si ] = static_cast< unsigned char >( k );
                // добавляем узел в очередь
                pq[ index ].push( nb );
                continue;
            }
            
            // выбираем лучший вариант
            if (open[ si ] > nb.priority) {
                open[ si ] = nb.priority;
                // отмечаем направление
                mDirection[ si ] = static_cast< unsigned char >( k );

                // заменям узел
                const auto& top = pq[ index ].top();
                while (top.coord != shift) {
                    pq[ 1 - index ].push( top );
                    pq[ index ].pop();
                }
                pq[ index ].pop();
                    
                // выравниваем очереди, выбираем лучший узел
                if (pq[ index ].size() > pq[ 1 - index ].size()) {
                    index = 1 - index;
                }
                while ( !pq[ index ].empty() ) {
                    pq[ 1 - index ].push( pq[ index ].top() );
                    pq[ index ].pop();
                }
                index = 1 - index;

                // добавляем узел в очередь
                pq[ index ].push( nb );
                continue;
            }

        } // for (size_t k = 1; k < DIRECTION; ++k)

    } // while ( !pq[ index ].empty() )


    // @test
    const std::size_t countClose = std::count_if(
        close,  close + N * M,  [] ( bool v ) -> bool {
            return v;
    } );
    const std::size_t countOpen = std::count_if(
        open,  open + N * M,  [] ( int v ) -> bool {
            return (v != 0);
    } );
    const std::size_t countDirection = std::count_if(
        mDirection,  mDirection + N * M,  [] ( unsigned char v ) -> bool {
            return (v != 0);
    } );
}




template< size_t N, size_t M >
inline typename AStar2D< N, M >::pathCoord_t const&
AStar2D< N, M >::pathCoord() const {

    if ( mPathCoord.empty() ) {
        coord_t coord = mPathPoint.first;
        for (auto itr = mPathDirection.cbegin();
             itr != mPathDirection.cend();
             ++itr
        ) {
            mPathCoord.push_back( coord );
            coord += SHIFT[ *itr ];
        }
    }

    return mPathCoord;
}


} // astar
