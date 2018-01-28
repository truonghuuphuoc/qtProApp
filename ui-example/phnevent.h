#ifndef PHNEVENT_H
#define PHNEVENT_H


class phnEvent
{
public:
    int Zone;
    int Target;
    int Value;
    int Sequence;

public:
    phnEvent(int zone, int target, int value, int sequence);

};

#endif // PHNEVENT_H
