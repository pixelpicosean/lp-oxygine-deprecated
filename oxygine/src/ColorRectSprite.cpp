#include "ColorRectSprite.h"
#include "core/Renderer.h"
#include "RenderState.h"
#include "STDRenderer.h"
#include "Serialize.h"
#include "utils/stringUtils.h"
namespace oxygine
{
    void ColorRectSprite::copyFrom(const ColorRectSprite& src, cloneOptions opt)
    {
        _Sprite::copyFrom(src, opt);
    }

    ColorRectSprite::ColorRectSprite()
    {
    }

    ColorRectSprite::~ColorRectSprite()
    {

    }

    void ColorRectSprite::doRender(const RenderState& rs)
    {
        _vstyle._apply(rs);


        rs.renderer->setTexture(Renderer::white, 0);
        rs.renderer->draw(&rs, getColor(), RectF(0, 0, 1, 1), getDestRect());
    }
}
