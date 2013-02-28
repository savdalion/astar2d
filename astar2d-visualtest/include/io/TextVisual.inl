inline TextVisual::TextVisual() {
}




inline TextVisual::~TextVisual() {
}




template< size_t N, size_t M >
inline TextVisual const& TextVisual::operator<<(
    const typename astar::AStar2D< N, M >&  a
) const {

    // карта штрафов
    //std::cout << "penalties\n" << a.penalty << std::endl;

    // карта рисков
    //std::cout << "\nrisks\n" << a.risk << std::endl;

    // найденный путь
    std::cout << "\npath\n";
    const auto pathPoint = a.pathPoint();
    const auto& pathCoord = a.pathCoord();
    for (int y = M - 1; y >= 0; --y) {
        for (int x = 0; x < N; ++x) {
            const astar::AStar2D< N, M >::coord_t  coord = { x, y };
            if (coord == pathPoint.first) {
                std::cout << "A ";
                continue;
            }
            if (coord == pathPoint.second) {
                std::cout << "B ";
                continue;
            }

            const auto penalty = a.penalty.content[ x ][ y ];
            //const auto risk = a.risk.content[ x ][ y ];
            std::stringstream ss;
            //ss << ( (penalty == std::numeric_limits< unsigned char >::max())
            (penalty == std::numeric_limits< unsigned char >::max())
                ? ss << static_cast< unsigned char >( '#' )
                : ss << static_cast< unsigned char >( '.' );
            const auto ftr =
                std::find( pathCoord.cbegin(), pathCoord.cend(), coord );
            (ftr == pathCoord.cend())
                ? std::cout << ss.str()
                : std::cout << '*';
            std::cout << " ";

        } // for (size_t x = 0; x < N; ++x)

        std::cout << std::endl;

    } // for (size_t y = 0; y < M; ++y)

    return *this;
}




template< size_t N, size_t M >
inline TextVisual const& TextVisual::operator<<(
    const typename astar::AStar2D< N, M >::penalty_t&  penalty
) const {

    for (size_t y = 0; y < M; ++y) {
        for (size_t x = 0; x < N; ++x) {
            const auto penalty = a.penalty.content[ x ][ y ];
            std::stringstream ss;
            ss << ( (penalty == std::numeric_limits< unsigned char >::max())
                ? '#'
                : static_cast< unsigned int >( penalty )
            );
            std::cout << ss.str() << " ";
        }
        std::cout << std::endl;
    }

    return *this;
}




template< size_t N, size_t M >
inline TextVisual const& TextVisual::operator<<(
    const typename astar::AStar2D< N, M >::risk_t&  risk
) const {

    for (size_t y = 0; y < M; ++y) {
        for (size_t x = 0; x < N; ++x) {
            const auto risk = a.risk.content[ x ][ y ];
            std::stringstream ss;
            ss << static_cast< unsigned int >( risk );
            std::cout << ss.str() << " ";
        }
        std::cout << std::endl;
    }

    return *this;
}






inline void TextVisual::wait() const {
    std::cin.ignore();
}
