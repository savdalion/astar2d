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
    struct risk_t {
        unsigned char  content[ N ][ M ];

        inline risk_t() {
            std::memset( content,  0,  N * M );
        }
    };


    typedef risk_t  penalty_t;


    typedef std::vector< unsigned char >  path_t;


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




    AStar2D( const risk_t&, const penalty_t& );




    ~AStar2D();




    /**
    * @return ���� � ���� ������, ��� ����������� ����������� ��������
    *         �� ����� 'from' �� 'to'.
    *
    * # ������ ��������� - ���� �� ������.
    */
    path_t path( const coord_t& from,  const coord_t& to ) const;




private:
    risk_t     risk;
    penalty_t  penalty;
};



} // astar








#include "Astar2D.inl"
