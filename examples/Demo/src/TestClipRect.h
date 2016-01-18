#pragma once
#include "test.h"
#include "ClipRectActor.h"
class TestClipRect: public Test
{
public:
    TestClipRect()
    {
        spClipRectActor clp = createClipRect(250, 250, 4.0f);
        clp->addTo(content);
        clp->setPosition(content->getSize() / 2 - clp->getSize() / 2);

        spClipRectActor childClp = createClipRect(100, 100, 2.0f);
        childClp->setPosition(-40.0f, -40.0f);
        childClp->addTo(clp);

        spSprite spr = new Sprite;
        spr->setResAnim(resources.getResAnim("batterfly"));
        spr->setX(200.0f);
        spr->addTo(clp);
    }

    spClipRectActor createClipRect(int w, int h, float sc)
    {
        spClipRectActor clp = new ClipRectActor;
        clp->setSize((float)w, (float)h);


        spSprite spr = new Sprite;
        spr->setPosition(w / 2.0f, h / 2.0f);
        spr->setResAnim(resources.getResAnim("batterfly"));
        spr->addTo(clp);
        spr->setAnchor(0.5f, 0.5f);
        spr->setScale(sc);

        return clp;
    }

    void onMouseDown(Event* event)
    {
        spActor actor = safeSpCast<Actor>(event->currentTarget);

        int new_priority = actor->getParent()->getLastChild()->getPriority() + 1;
        actor->setPriority(new_priority);
    }

    void onMouseUp(Event* event)
    {
        spSprite actor = safeSpCast<Sprite>(event->currentTarget);
        actor->setColor(Color::White);
    }
};
