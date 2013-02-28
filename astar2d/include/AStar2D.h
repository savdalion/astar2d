#pragma once

#include <bm.h>
#include <queue>


/**
* ����� ���� �� ��������� A*.
*/
namespace astar {


template< size_t N, size_t M >
class AStar2D {
public:
    struct penalty_t {
        unsigned char  content[ N ][ M ];

        inline penalty_t() {
            std::memset( content,  0,  N * M );
        }
    };


    struct risk_t {
        unsigned char  content[ N ][ M ];

        inline risk_t() {
            std::memset( content,  0,  N * M );
        }
    };


    struct coord_t {
        int x, y;

        inline bool operator==( const coord_t& b ) const {
            return (x == b.x) && (y == b.y);
        }

        inline bool operator!=( const coord_t& b ) const {
            return (x != b.x) || (y != b.y);
        }

        inline coord_t operator+( const coord_t& b ) const {
            const coord_t c = { x + b.x,  y + b.y };
            return c;
        }

        inline coord_t operator-( const coord_t& b ) const {
            const coord_t c = { x - b.x,  y - b.y };
            return c;
        }

        inline coord_t& operator+=( const coord_t& b ) {
            x += b.x;
            y += b.y;
            return *this;
        }

        inline coord_t& operator-=( const coord_t& b ) {
            x -= b.x;
            y -= b.y;
            return *this;
        }

        inline bool operator<( const coord_t& b ) const {
            return ((x + N * y) < (b.x + N * b.y));
        }
    };


    typedef std::vector< unsigned char >  pathDirection_t;
    typedef std::vector< coord_t >  pathCoord_t;


    /**
    * ����������� ��������.
    *   ��������� ����� - �� �������� � typelib::StaticMapContent3D
    *     8   1   5
    *     4   0   2
    *     7   3   6
    */
    static const size_t DIRECTION = 9;
    static const coord_t SHIFT[ DIRECTION ];




    /**
    * ��������������� ����� ��� ���������� ����.
    */
    struct Node {
        /**
        * ������� ����������.
        */
        coord_t coord;

        /**
        * ��� ���������� ���������� �� ����� ����.
        */
        int level;

        /**
        * = level + estimate
        * ��� ������ - ��� ������.
        */
        int priority;

    
        inline Node( const coord_t& coord, int level, int priority ) :
            coord( coord ),
            level( level ),
            priority( priority )
        {
        }
    

        inline void update( const coord_t& c ) {
            priority = level + 10 * estimate( c );
        }


        inline void next( size_t direction ) {
            assert( (direction != 0)
                && "����������������� �����������. ��� ��������." );
            level += (direction > 4) ? 14 : 10;
        }
        

        /**
        * @return ������ ���������� �� ����.
        */
        inline int estimate( const coord_t& c ) const {
            const coord_t d = { c.x - coord.x,  c.y - coord.y };

            /* ��������� ����������
            return static_cast< int >(
                std::sqrt( d.x * d.x + d.y * d.y )
            );
            */

            // ���������� ����������
            return (std::abs( d.x ) + std::abs( d.y ));
            
            // ���������� ��������
            //return std::max( std::abs( d.x ), std::abs( d.y ) );
        }


        inline bool operator<( const Node& b ) const {
            return (priority > b.priority);
        }

    }; // class Node




    const penalty_t  penalty;
    const risk_t     risk;




    AStar2D( const penalty_t&, const risk_t& );




    ~AStar2D();




    /**
    * @return ���� � ���� ������, ��� ����������� ����������� ��������
    *         �� ����� 'from' �� 'to'.
    *
    * # ������ ��������� - ���� �� ����������.
    */
    void path( const coord_t& from,  const coord_t& to );




    /**
    * @return ����, ����������� � path( from, to ).
    *
    * # ������ ��������� - ���� �� �������� ��� �� ����������.
    */
    inline pathDirection_t const&  pathDirection() const {
        return mPathDirection;
    }


    pathCoord_t const&  pathCoord() const;




    /**
    * @return ��������� � �������� ����� ��������, ����������� ���
    *         ������ path( from, to ).
    */
    inline std::pair< coord_t, coord_t > const&  pathPoint() const {
        return mPathPoint;
    }




    /**
    * @return �����, ����������� ��� ������ path( from, to ).
    */
    inline unsigned char direction( int x, int y ) const {
        return mDirection[ x + N * y ];
    }




private:
    /**
    * ��������� / �������� ����� � ����, ���������� ��� ��������� ������
    * path( from, to ).
    */
    std::pair< coord_t, coord_t >  mPathPoint;
    pathDirection_t  mPathDirection;
    mutable pathCoord_t      mPathCoord;

    /**
    * ��������������� �����.
    */
    unsigned char  mDirection[ N * M ];
    int            open[ N * M ];
    bool           close[ N * M ];
};



} // astar








#include "Astar2D.inl"
