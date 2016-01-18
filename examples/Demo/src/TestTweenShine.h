#pragma once
#include "test.h"
#include "TextField.h"
#include "utils/stringUtils.h"

class TweenShine: public Tween
{
public:

    TweenShine()
    {
    }

    void _loopDone(Actor& actor, const UpdateState& us) OVERRIDE
    {
        for (int i = 0; i < 5; ++i)
        {
            Vector2 pos;
            pos.x = scalar::randFloat(0, actor.getWidth());
            pos.y = scalar::randFloat(0, actor.getHeight());

            if (!actor.isOn(pos))
                continue;

            spSprite sprite = new Sprite;
            sprite->setResAnim(resources.getResAnim("snow"));
            sprite->setAnchor(0.5f, 0.5f);
            sprite->setPosition(pos);
            //sprite->setAlpha(0);
            sprite->setScale(0.5f);
            actor.addChild(sprite);
            //break;
        }
    }

    static spTween create(int duration, int loops)
    {
        spTween t = new TweenShine;
        t->setDuration(duration);
        t->setLoops(loops);
        return t;
    }
};


class TestTweenShine: public Test
{
public:
    spSprite sprite;
    TestTweenShine()
    {
        sprite = new Sprite;
        sprite->setResAnim(resources.getResAnim("flower"));
        sprite->addTo(content);
        //sprite->setAnchor(0.5f, 0.5f);
        sprite->setPosition(content->getSize() / 2 - sprite->getSize() / 2);

        addButton("shine", "shine");
    }

    void clicked(string id)
    {
    }
};