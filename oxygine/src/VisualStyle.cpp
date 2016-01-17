#include "VisualStyle.h"
#include "Actor.h"
#include <sstream>
#include "RenderState.h"
#include "Serialize.h"
#include "utils/stringUtils.h"

namespace oxygine
{
    VisualStyle::VisualStyle(): _color(255, 255, 255, 255), _blend(Renderer::getPremultipliedAlphaRender() ? blend_premultiplied_alpha : blend_alpha)
    {

    }

    void VStyleActor::copyFrom(const VStyleActor& src, cloneOptions opt)
    {
        _Actor::copyFrom(src, opt);
        _vstyle = src._vstyle;
    }

    void VisualStyle::_apply(const RenderState& rs)
    {
        //rs.renderer->setMaterial(&_material);
        rs.renderer->setBlendMode(_blend);
        //rs.renderer->setTexture()
    }

    void VisualStyle::setColor(const Color& color)
    {
        _color = color;
    }
    void VisualStyle::setBlendMode(blend_mode mode)
    {
        _blend = mode;
    }

    std::string VisualStyle::dump() const
    {
        VisualStyle def;

        std::stringstream stream;
        if (_color != def.getColor())
        {
            stream << "color=(" << (int)_color.r << ", " << (int)_color.g << ", " << (int)_color.b << ", " << (int)_color.a << ")";
        }

        if (_blend != def.getBlendMode())
        {
            stream << "blend=" << (int)_blend;
        }


        return stream.str();
    }

    const Color& VStyleActor::getColor() const
    {
        return _vstyle.getColor();
    }

    void VStyleActor::setColor(const Color& color)
    {
        _vstyle.setColor(color);
    }
}
