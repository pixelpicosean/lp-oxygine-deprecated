#pragma once
#include "test.h"
#include "Draggable.h"
class DraggableSprite: public Sprite
{
public:
    DraggableSprite()
    {
        drag.init(this);
    }

    Draggable drag;
};

class DragTest: public Test
{
public:

    spSprite sprites[3];
    spActor contacts;
    int priority;

    DragTest()
    {
        priority = 0;

        Vector2 pos[3];
        pos[0] = Vector2(425, 420);
        pos[1] = Vector2(600, 225);
        pos[2] = Vector2(305, 170);

        for (int i = 0; i < 3; ++i)
        {
            spSprite sprite = new DraggableSprite;
            sprite->setPosition(pos[i]);
            sprite->setResAnim(resources.getResAnim("batterfly"));
            sprite->addTo(content);

            float angle = scalar::randFloat(0, (float)MATH_PI * 2);
            sprite->setRotation(angle);
            sprite->setScale(scalar::randFloat(1.0f, 1.5f));
            sprite->setAnchor(0.5f, 0.5f);

            sprite->addEventListener(TouchEvent::TOUCH_DOWN, CLOSURE(this, &DragTest::onMouseDown));
            sprite->addEventListener(TouchEvent::TOUCH_UP, CLOSURE(this, &DragTest::onMouseUp));

            sprites[i] = sprite;
        }

        contacts = new Actor;
        contacts->addTo(content);
        contacts->setPriority(10000);
        contacts->setInputChildrenEnabled(false);
    }

    void doUpdate(const UpdateState& us)
    {
        //check intersections between sprites and visualize contact points
        for (int i = 0; i < 3; ++i)
        {
            spSprite a = sprites[i];

            for (int n = 0; n < 3; ++n)
            {
                spSprite b = sprites[n];
                if (a == b)
                    continue;

                Vector2 contact;
                if (testIntersection(a, b, 0, &contact))
                {
                    spSprite c = new Sprite;
                    c->setAnchor(0.5f, 0.5f);
                    c->setResAnim(resources.getResAnim("snow"));
                    Vector2 pos = convert_local2global(a, content, contact);
                    c->setPosition(pos);
                    c->addTo(contacts);
                }
            }
        }
    }

    void onMouseDown(Event* event)
    {
        spActor actor = safeSpCast<Actor>(event->currentTarget);

        //show clicked sprite on top
        actor->setPriority(priority++);
    }

    void onMouseUp(Event* event)
    {
        spSprite actor = safeSpCast<Sprite>(event->currentTarget);

        actor->setColor(Color::White);
    }
};


class Drag2Test: public Test
{
public:
    spSprite basket;
    spSprite ball;
    spSprite dragging;
    spTextField txt;

    timeMS timeLeft;
    const PointerState* touchedBy;
    Draggable drag;

    Drag2Test(): touchedBy(0), timeLeft(0)
    {
        basket = new Sprite;
        basket->setName("basket");
        basket->setResAnim(resources.getResAnim("batterfly"));
        basket->addTo(content);
        basket->setAnchor(0.5f, 0.5f);
        basket->setX(content->getWidth() * 3 / 4);
        basket->setY(content->getHeight() / 2);

        ball = new Sprite;
        ball->setName("ball");
        ball->setResAnim(resources.getResAnim("batterfly"));
        ball->addTo(content);
        ball->setAnchor(0.5f, 0.5f);
        ball->setX(content->getWidth() * 1 / 4);
        ball->setY(content->getHeight() / 2);

        ball->addEventListener(TouchEvent::TOUCH_DOWN, CLOSURE(this,  &Drag2Test::ballTouchDown));
        ball->addEventListener(TouchEvent::TOUCH_UP, CLOSURE(this,  &Drag2Test::ballTouchUp));
        content->addEventListener(TouchEvent::TOUCH_UP, CLOSURE(this, &Drag2Test::touchUp));

        txt = new TextField;
        txt->addTo(content);
        txt->setVAlign(TextStyle::VALIGN_MIDDLE);
        txt->setHAlign(TextStyle::HALIGN_MIDDLE);
        txt->setPosition(getSize() / 2);
    }


    void ballTouchUp(Event* event)
    {
        touchedBy = 0;
    }

    void touchUp(Event* event)
    {
        if (!dragging)
            return;
        if (event->currentTarget.get() != content)
            return;

        dragging->setColor(Color::White);
        dragging = 0;
    }


    void ballTouchDown(Event* ev)
    {
        TouchEvent* te = safeCast<TouchEvent*>(ev);
        touchedBy = te->getPointer();
        timeLeft = 500;
    }

    void doUpdate(const UpdateState& us)
    {
        if (!touchedBy)
        {
            txt->setText("Drag left object and drop on right object");
            return;
        }

        if (!timeLeft)
            return;

        timeLeft -= us.dt;
        if (timeLeft <= 0)
        {
            txt->setText("Now drop it on right object");

            timeLeft = 0;
            dragging = ball->clone();

            dragging->setName("dragging");
            dragging->addTo(ball->getParent());
            dragging->setColor(Color::Red);
            dragging->setAnchor(0, 0);
            dragging->setInputEnabled(false);
            drag.start(touchedBy, dragging.get(), dragging->getSize() / 2);
        }
    }
private:
};