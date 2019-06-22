// Copyright Albert Alma Ltd.


#include "Ghost.h"

EColor AGhost::GetBubbleColor_Implementation()
{
    return m_eColor;
}

void AGhost::Disable_Implementation()
{
    Destroy();
}

void AGhost::SetBubbleColor_Implementation(EColor Color)
{
    m_eColor = Color;
}
