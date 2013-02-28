#pragma once

#include "../configure.h"
#include <astar2d.h>


/**
* ������������ ����������� � ���� ������.
*/
class TextVisual {
public:
    TextVisual();




    virtual ~TextVisual();




    /**
    * �������������.
    */
    template< size_t N, size_t M >
    TextVisual const& operator<<(
        const typename astar::AStar2D< N, M >&
    ) const;

    template< size_t N, size_t M >
    TextVisual const& operator<<(
        const typename astar::AStar2D< N, M >::penalty_t&
    ) const;

    template< size_t N, size_t M >
    TextVisual const& operator<<(
        const typename astar::AStar2D< N, M >::risk_t&
    ) const;




    /**
    * ������� �������� ���� ������������ (����� - �������).
    */
    void wait() const;
};








#include "TextVisual.inl"
